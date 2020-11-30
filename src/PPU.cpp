
#include "PPU.h"
#include <iostream>

PPU::PPU(){
     STAT.mode = PPU_HBLANK;
     std::cout<<"[PPU] ready !"<<std::endl;
}

void PPU::step(){
     clock += cpu.get_cycle_count();

     switch(STAT.mode){
     case PPU_HBLANK:
          if(clock >= 204){
               clock = 0;
               if(++line == 143){
                    STAT.mode = PPU_VBLANK;
                    if(!PPU_CTRL_DY_ENABLE) break;

                    if(mem.read(INT_ENABLE) & INT_VBLANK)
                         INT_RAISE(INT_VBLANK);
                    if((mem.read(INT_ENABLE) & INT_STAT) && STAT.VBlank_enable)
                         INT_RAISE(INT_STAT);

                    lcd.clear();
                    lcd.update();


               }else STAT.mode = PPU_OAM;
          }
          break;
     case PPU_VBLANK:
		STAT.coincid_flag = (line == LYC);
		if((mem.read(INT_ENABLE) & INT_STAT) && STAT.coincid_enable && STAT.coincid_flag) {
			INT_RAISE(INT_STAT);
		}
          if(clock >= 456){
               clock = 0;
               if(++line > 153){
                    STAT.mode = PPU_OAM;
                    if((mem.read(INT_ENABLE) & INT_STAT) && STAT.OAM_enable)
                         INT_RAISE(INT_STAT);
                    line = 0;
               }
          }
          break;
     case PPU_OAM:
          if(clock >= 80){
               clock = 0;
               STAT.mode = PPU_VRAM;
          }
          break;
     case PPU_VRAM:
          if(clock >= 172){
               clock = 0;
               STAT.mode  = PPU_HBLANK;
               if((mem.read(INT_ENABLE) & INT_STAT) && STAT.HBlank_enable)
                    INT_RAISE(INT_STAT);

               if(PPU_CTRL_BG_ENABLE) render_bg();
               if(PPU_CTRL_SP_ENABLE) render_sp();
          }
          break;
     }

}
void PPU::render_bg(){
     int map_offset      = ((PPU_CTRL_BG_TILEMAP) ? 0x9C00 : 0x9800)
                         + (((line + state.scroll_y) & 0xF8) << 2);

     int line_offset     = state.scroll_x >> 3;

     int tile            = mem.read(map_offset + line_offset);

     int x               = state.scroll_x & 0x07;
     int y               = (line + state.scroll_y) & 0x07;

     int canvas_offset   = line * 160 + state.scroll_x;
     short color;

     for(uint8_t i = 0; i < 160; i++){
          uint16_t addr = PPU_CTRL_BG_TILESET ? 0x8000 : 0x9000;

          if(PPU_CTRL_BG_TILESET) addr += 16 * ((uint8_t)tile);
          else addr += 16 * ((int8_t)tile);

          addr += 2*y;

          uint8_t B1 = mem.read(addr);
          uint8_t B2 = mem.read(addr + 1);
          uint8_t b1 = ((B1 & (1 << (7 - x))) >> (7 - x));
          uint8_t b2 = ((B2 & (1 << (7 - x))) >> (7 - x));
          color      = (b2 << 1) | b1;
          color = (state.palette & (3 << (2*color))) >> (2*color);
          lcd.framebuffer[canvas_offset++] = color;

          if(++x == 8){
               x = 0;
               line_offset = (line_offset + 1) & 31;
               tile = mem.read(map_offset + line_offset);
          }
     }
}
void PPU::render_sp(){
     for(uint8_t i = 0; i < 40; i++){
          struct OAM_entry obj = {
               mem.read(OAM_OFFSET + 4*i + 0),
               mem.read(OAM_OFFSET + 4*i + 1),
               mem.read(OAM_OFFSET + 4*i + 2),
               mem.read(OAM_OFFSET + 4*i + 3),
          };
          obj.y -= 16;
          obj.x -= 8;

          uint8_t height = PPU_CTRL_SP_SIZE ? 16 : 8;
          if((line < (obj.y + height)) && (line >= obj.y)){
               int row = line - obj.y;
               if((obj.flags & (1 << 6)))
                    row = 7- row;
               row *= 2;


               uint16_t addr = VRAM_OFFSET + 16*obj.tile + row;

               uint8_t B1 = mem.read(addr) ;
               uint8_t B2 = mem.read(addr + 1) ;

               short canvas_offset = (line * 160 + obj.x);

               for (int pixel = 0; pixel < 8; pixel++){
                    if(  ((obj.x + pixel) >= 0)
                    &&   ((obj.x + pixel) < 160)
                    &&   ((!(obj.flags & (1 << 7)))||(!lcd.framebuffer[canvas_offset]))
                    ){
                         int temp = (obj.flags & (1 << 5))?(7-pixel):pixel;
                         uint8_t b1     = ((B1 & (1 << (7 - temp))) >> (7 - temp));
                         uint8_t b2     = ((B2 & (1 << (7 - temp))) >> (7 - temp));
                         short color    = (b2 << 1) | b1;

                         if(color){
                              uint8_t pa = (obj.flags & (1 << 4)) ? OBP1 : OBP0;
                              color = (pa & (3 << (2*color))) >> (2*color);
                              lcd.framebuffer[canvas_offset] = color;
                         }
                         ++canvas_offset;
                    }

               }

          }

     }
}
void PPU::render_wn(){

}

void PPU::update_STAT(uint8_t value){
     STAT.coincid_enable = (value & (1 << 6));
     STAT.OAM_enable     = (value & (1 << 5));
     STAT.VBlank_enable  = (value & (1 << 4));
     STAT.HBlank_enable  = (value & (1 << 3));
}
uint8_t PPU::read_STAT(){
     uint8_t result = 0x80;
     result |= (uint8_t)STAT.mode;
     result |= (uint8_t)STAT.coincid_flag << 2;
     result |= (uint8_t)STAT.HBlank_enable << 3;
     result |= (uint8_t)STAT.VBlank_enable << 4;
     result |= (uint8_t)STAT.OAM_enable << 5;
     result |= (uint8_t)STAT.coincid_enable << 6;
     return result;
}
PPU::~PPU(){

}
