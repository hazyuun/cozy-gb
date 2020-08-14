/*
 *  File : PPU.h
 *  Description : TODO
 * */
#pragma once
#include "mem.h"
#include "Z80.h"
#include "LCD.h"


extern Mem mem;
extern Z80 cpu;
extern LCD lcd;

class PPU{
     struct {
          uint8_t   control;
          uint8_t   scroll_y;
          uint8_t   scroll_x;
          uint8_t   scanline;
          uint8_t   palette;
     } state;

     enum PPU_MODE{
          PPU_HBLANK,
          PPU_VBLANK,
          PPU_OAM,
          PPU_VRAM
     };
     
     long clock;
     uint8_t line = 0;

     enum PPU_MODE mode;
     
     short framebuffer[256 * 256];

public:
     PPU();
     void step();
     ~PPU();
     friend class Mem;
};