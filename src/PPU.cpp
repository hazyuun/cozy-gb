
#include "PPU.h"
#include <iostream>

PPU::PPU(){
     mode = PPU_HBLANK;
     std::cout<<"[PPU] ready !"<<std::endl;
}

void PPU::step(){
     clock += cpu.get_cycle_count();
     switch(mode){
     case PPU_HBLANK: 
          if(clock >= 204){
               clock = 0;
               if(++line == 143){
                    mode = PPU_VBLANK;
                    /* Raise V-BLANK interrupt */
                    /* TODO: do it properly instead of this ugly hacky way */
                    if(mem.read(0xFFFF) & 0x01) mem.write(0xFF0F, mem.read(0xFF0F) | 0x01);
                    lcd.clear();
                    lcd.update();
               }else mode = PPU_OAM;
          }
          break;
     case PPU_VBLANK: 
     
          if(clock >= 456){
               clock = 0;
               if(++line > 153){
                    mode = PPU_OAM;
                    line = 0;
               }
          }
          break;
     case PPU_OAM: 
          if(clock >= 80){
               clock = 0;
               mode = PPU_VRAM;;
          }
          break;
     case PPU_VRAM: 
          if(clock >= 172){
               clock = 0;
               mode  = PPU_HBLANK;
               
               int map_offset      = (PPU_CTRL_BG_TILEMAP) ? 0x9C00 : 0x9800
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
                    color      = (b1 << 1) | b2;

                    lcd.framebuffer[canvas_offset++] = color;

                    if(++x == 8){
                         x = 0;
                         line_offset = (line_offset + 1) & 31;
                         tile = mem.read(map_offset + line_offset);
                    }
               }

          }
          break;
     }
     
}

PPU::~PPU(){

}
