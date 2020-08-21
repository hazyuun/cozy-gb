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

#define PPU_CTRL_BG_ENABLE    (state.control & (1 << 0))
#define PPU_CTRL_SP_ENABLE    (state.control & (1 << 1))
#define PPU_CTRL_SP_SIZE      (state.control & (1 << 2))
#define PPU_CTRL_BG_TILEMAP   (state.control & (1 << 3))
#define PPU_CTRL_BG_TILESET   (state.control & (1 << 4))
#define PPU_CTRL_WN_ENABLE    (state.control & (1 << 5))
#define PPU_CTRL_WN_TILEMAP   (state.control & (1 << 6))
#define PPU_CTRL_DY_ENABLE    (state.control & (1 << 7))

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