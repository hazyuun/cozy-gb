#pragma once
#include <cstdint>

#define PPU_CTRL_BG_ENABLE  (state.control & (1 << 0))
#define PPU_CTRL_SP_ENABLE  (state.control & (1 << 1))
#define PPU_CTRL_SP_SIZE    (state.control & (1 << 2))
#define PPU_CTRL_BG_TILEMAP (state.control & (1 << 3))
#define PPU_CTRL_BG_TILESET (state.control & (1 << 4))
#define PPU_CTRL_WN_ENABLE  (state.control & (1 << 5))
#define PPU_CTRL_WN_TILEMAP (state.control & (1 << 6))
#define PPU_CTRL_DY_ENABLE  (state.control & (1 << 7))

#define HBLANK_CYCLES 207
#define OAM_CYCLES    83
#define VRAM_CYCLES   175
#define VBLANK_CYCLES 456

#define OAM_FLAG_PRI_MASK         (1 << 7)
#define OAM_FLAG_X_FLIP_MASK      (1 << 6)
#define OAM_FLAG_Y_FLIP_MASK      (1 << 5)
#define OAM_FLAG_PALETTE_MASK     (1 << 4)

namespace GB {
class Mem;
class Z80;
class HMI;

class PPU {
  Mem *m_mem;
  Z80 *m_cpu;
  HMI *m_hmi;

  
  /* I don't know why I created this struct */
  /* TODO: remove this struct */
  struct {
    uint8_t control;
    uint8_t scroll_y;
    uint8_t scroll_x;
    uint8_t scanline;
    uint8_t palette;
    uint8_t wx;
    uint8_t wy;
  } state; 

  enum PPU_MODE { PPU_HBLANK, PPU_VBLANK, PPU_OAM, PPU_VRAM };

  struct OAM_entry {
    uint8_t y;
    uint8_t x;
    uint8_t tile;
    uint8_t flags;
  };

  uint8_t OBP0;
  uint8_t OBP1;

  long clock = 0;
  uint8_t line = 0;
  uint8_t LYC = 144;

  struct {
    bool coincid_enable;
    bool OAM_enable;
    bool VBlank_enable;
    bool HBlank_enable;
    bool coincid_flag;
    enum PPU_MODE mode;
  } STAT;

  short framebuffer[256 * 256];

  /* Window internal line counter */
  int wc = 0;

public:
  PPU(Mem *mem, Z80 *cpu, HMI *hmi);
  void setup(Mem *mem, Z80 *cpu, HMI *hmi);

  void step();
  void render_bg();
  void render_sp();
  void render_wn();

  void update_STAT(uint8_t);
  uint8_t read_STAT();
  
  inline void set_mode(enum PPU_MODE mode){
    STAT.mode = mode;
  }
  inline enum PPU_MODE get_mode() const{
    return STAT.mode;
  }
  
  ~PPU();
  
  friend class Mem;
};
}
