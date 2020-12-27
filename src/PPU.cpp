
#include <HMI.h>
#include <PPU.h>
#include <Z80.h>
#include <iostream>
#include <mem.h>

GB::PPU::PPU(Mem *mem, Z80 *cpu, HMI *hmi) {
  m_mem = mem;
  m_cpu = cpu;
  m_hmi = hmi;
  STAT.mode = PPU_HBLANK;
  std::cout << "[PPU] ready !" << std::endl;
}

void GB::PPU::setup(Mem *mem, Z80 *cpu, HMI *hmi) {
  m_mem = mem;
  m_cpu = cpu;
  m_hmi = hmi;
}

void GB::PPU::step() {
  clock += m_cpu->get_cycle_count();

  switch (STAT.mode) {
  case PPU_HBLANK:
    if (clock >= HBLANK_CYCLES) {
      clock -= HBLANK_CYCLES;
      line = (line + 1) % 154;

      STAT.coincid_flag = LYC == line;
      if (STAT.coincid_enable && STAT.coincid_flag)
        INT_RAISE(INT_STAT);
      else
        INT_ACK(INT_STAT);

      if (line == 144) {
        STAT.mode = PPU_VBLANK;

        INT_RAISE(INT_VBLANK);
        if (STAT.VBlank_enable)
          INT_RAISE(INT_STAT);

        m_hmi->clear();
        m_hmi->update();

        wc = 0;
      } else {
        STAT.mode = PPU_OAM;
        if (STAT.OAM_enable)
          INT_RAISE(INT_STAT);
      }
    }
    break;
  case PPU_OAM:
    if (clock >= OAM_CYCLES) {
      clock -= OAM_CYCLES;
      STAT.mode = PPU_VRAM;
    }

    break;
  case PPU_VRAM:
    if (clock >= VRAM_CYCLES) {
      clock -= VRAM_CYCLES;
      STAT.mode = PPU_HBLANK;

      if (STAT.HBlank_enable)
        INT_RAISE(INT_STAT);

      if (PPU_CTRL_BG_ENABLE)
        render_bg();
      if (PPU_CTRL_WN_ENABLE)
        render_wn();
      if (PPU_CTRL_SP_ENABLE)
        render_sp();
    }
    break;
  case PPU_VBLANK:
    if (clock >= VBLANK_CYCLES) {
      clock -= VBLANK_CYCLES;

      line = (line + 1) % 154;

      STAT.coincid_flag = LYC == line;
      if (STAT.coincid_enable && STAT.coincid_flag)
        INT_RAISE(INT_STAT);
      else
        INT_ACK(INT_STAT);

      if (!line) {
        STAT.mode = PPU_OAM;
        if (STAT.OAM_enable)
          INT_RAISE(INT_STAT);
      }
    }
    break;
  }
}

void GB::PPU::render_bg() {

  int tilemap = ((PPU_CTRL_BG_TILEMAP) ? 0x9C00 : 0x9800);
  uint8_t palette = state.palette;

  for (uint8_t x = 0; x < 160; x++) {

    int _x = state.scroll_x + x;
    _x -= (_x >= 256) ? 256 : 0;
    int tile_x = floor(_x / 8);
    int pixel_x = _x % 8;

    int _y = state.scroll_y + line;
    _y -= (_y >= 256) ? 256 : 0;
    int tile_y = floor(_y / 8);
    int pixel_y = _y % 8;

    uint16_t tile_address = tilemap + (tile_y * 32) + tile_x;

    uint8_t tile = m_mem->read(tile_address);

    uint16_t bg_offset = (PPU_CTRL_BG_TILESET) ? 0x8000 : 0x9000;
    if (PPU_CTRL_BG_TILESET)
      bg_offset += 16 * ((uint8_t)tile);
    else
      bg_offset += 16 * ((int8_t)tile);

    bg_offset += 2 * pixel_y;

    uint8_t B1 = m_mem->read(bg_offset);
    uint8_t B2 = m_mem->read(bg_offset + 1);
    uint8_t b1 = ((B1 & (1 << (7 - pixel_x))) >> (7 - pixel_x));
    uint8_t b2 = ((B2 & (1 << (7 - pixel_x))) >> (7 - pixel_x));
    short color = (b2 << 1) | b1;
    color = (state.palette & (3 << (2 * color))) >> (2 * color);
    m_hmi->framebuffer[line * 160 + x] = color;
  }
}

void GB::PPU::render_sp() {
  for (uint8_t i = 0; i < 40; i++) {
    struct OAM_entry obj = {
        m_mem->read(OAM_OFFSET + 4 * i + 0),
        m_mem->read(OAM_OFFSET + 4 * i + 1),
        m_mem->read(OAM_OFFSET + 4 * i + 2),
        m_mem->read(OAM_OFFSET + 4 * i + 3),
    };
    obj.y -= 16;
    obj.x -= 8;

    uint8_t height = PPU_CTRL_SP_SIZE ? 16 : 8;
    if ((line < (obj.y + height)) && (line >= obj.y)) {
      int row = line - obj.y;
      if ((obj.flags & (1 << 6)))
        row = height - 1 - row;
      row *= 2;

      uint16_t tile = obj.tile;
      if (height == 16)
        tile &= 0xFE;
      uint16_t addr = VRAM_OFFSET + 16 * tile + row;

      uint8_t B1 = m_mem->read(addr);
      uint8_t B2 = m_mem->read(addr + 1);

      short canvas_offset = (line * 160 + obj.x);

      for (int pixel = 0; pixel < 8; pixel++) {
        bool visible = (obj.x + pixel) >= 0;
        visible &= ((obj.x + pixel) < 160);

        if (!visible)
          continue;

        int temp = (obj.flags & (1 << 5)) ? (7 - pixel) : pixel;
        uint8_t b1 = ((B1 & (1 << (7 - temp))) >> (7 - temp));
        uint8_t b2 = ((B2 & (1 << (7 - temp))) >> (7 - temp));
        short color = (b2 << 1) | b1;

        if (color && !((obj.flags & OAM_FLAG_PRI_MASK) &&
                       (m_hmi->framebuffer[canvas_offset]))) {
          uint8_t pa = (obj.flags & OAM_FLAG_PALETTE_MASK) ? OBP1 : OBP0;
          color = (pa & (3 << (2 * color))) >> (2 * color);
          m_hmi->framebuffer[canvas_offset] = color;
        }
        ++canvas_offset;
      }
    }
  }
}

void GB::PPU::render_wn() {
  int tilemap = ((PPU_CTRL_WN_TILEMAP) ? 0x9C00 : 0x9800);
  uint8_t palette = state.palette;

  if (line < state.wy)
    return;

  int _y = wc++;

  for (uint8_t x = 0; x < 160; x++) {
    if (x < state.wx - 7)
      continue;
    int _x = x - state.wx + 7;
    int tile_x = floor(_x / 8);
    int pixel_x = _x % 8;

    int tile_y = floor(_y / 8);
    int pixel_y = _y % 8;

    uint16_t tile_address = tilemap + (tile_y * 32) + tile_x;

    uint8_t tile = m_mem->read(tile_address);

    uint16_t bg_offset = (PPU_CTRL_BG_TILESET) ? 0x8000 : 0x9000;
    if (PPU_CTRL_BG_TILESET)
      bg_offset += 16 * ((uint8_t)tile);
    else
      bg_offset += 16 * ((int8_t)tile);

    bg_offset += 2 * pixel_y;

    uint8_t B1 = m_mem->read(bg_offset);
    uint8_t B2 = m_mem->read(bg_offset + 1);
    uint8_t b1 = ((B1 & (1 << (7 - pixel_x))) >> (7 - pixel_x));
    uint8_t b2 = ((B2 & (1 << (7 - pixel_x))) >> (7 - pixel_x));
    short color = (b2 << 1) | b1;
    color = (state.palette & (3 << (2 * color))) >> (2 * color);
    m_hmi->framebuffer[line * 160 + x] = color;
  }
}

void GB::PPU::update_STAT(uint8_t value) {
  STAT.coincid_enable = (value & (1 << 6));
  STAT.OAM_enable = (value & (1 << 5));
  STAT.VBlank_enable = (value & (1 << 4));
  STAT.HBlank_enable = (value & (1 << 3));
}

uint8_t GB::PPU::read_STAT() {
  uint8_t result = 0x80;
  result |= (uint8_t)STAT.mode;
  result |= ((uint8_t)STAT.coincid_flag) << 2;
  result |= ((uint8_t)STAT.HBlank_enable) << 3;
  result |= ((uint8_t)STAT.VBlank_enable) << 4;
  result |= ((uint8_t)STAT.OAM_enable) << 5;
  result |= ((uint8_t)STAT.coincid_enable) << 6;
  return result;
}

GB::PPU::~PPU() {}
