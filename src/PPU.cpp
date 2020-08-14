
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
               mode = PPU_HBLANK;
               lcd.framebuffer[0] = 3;
               

               for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 8; j++){
                         lcd.framebuffer[i + 160*j] = (i+j)%3;
                    }
               }
               
          }
          break;
     }
     fprintf(stdout, "ctrl : %0004X \n", state.control);
}

PPU::~PPU(){

}
