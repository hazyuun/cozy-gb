#include <HMI.h>
#include <PPU.h>
#include <cstring>
#include <iostream>
#include <mem.h>
#include <time.h>

GB::Mem::Mem(GB::Cartridge *cart, GB::PPU *ppu, GB::HMI *hmi) {
  m_ppu = ppu;
  m_cartridge = cart;
  m_hmi = hmi;
  write(0xFF00, 0xCF);
  write(0xFF05, 0x00);
  write(0xFF06, 0x00);
  write(0xFF07, 0x00);
  write(0xFF10, 0x80);
  write(0xFF11, 0xBF);
  write(0xFF12, 0xF3);
  write(0xFF14, 0xBF);
  write(0xFF16, 0x3F);
  write(0xFF17, 0x00);
  write(0xFF19, 0xBF);
  write(0xFF1A, 0x7F);
  write(0xFF1B, 0xFF);
  write(0xFF1C, 0x9F);
  write(0xFF1E, 0xBF);
  write(0xFF20, 0xFF);
  write(0xFF21, 0x00);
  write(0xFF22, 0x00);
  write(0xFF23, 0xBF);
  write(0xFF24, 0x77);
  write(0xFF25, 0xF3);
  write(0xFF26, 0xF1);
  write(0xFF40, 0x91);
  write(0xFF42, 0x00);
  write(0xFF43, 0x00);
  write(0xFF44, 0x90);
  write(0xFF45, 0x00);
  write(0xFF47, 0xFC);
  write(0xFF48, 0xFF);
  write(0xFF49, 0xFF);
  write(0xFF4A, 0x00);
  write(0xFF4B, 0x00);
  write(0xFF0F, 0x00);
  write(0xFFFF, 0x00);
  memset(m_vram, 0, 8 * 1024 * sizeof(uint8_t));
  std::cout << "[MEM] ready !" << std::endl;
}
void GB::Mem::setup(GB::Cartridge *cart, GB::PPU *ppu, GB::HMI *hmi) {
  m_ppu = ppu;
  m_cartridge = cart;
  m_hmi = hmi;
}

void GB::Mem::load(unsigned char *data, uint64_t size, uint16_t addr) {
  for (uint16_t pos = addr; pos < addr + size; pos++) {
    write(pos, *(data + pos - addr));
  }
}

uint8_t GB::Mem::read(uint16_t addr) {
  if (ROM0(addr)) {
    if (m_cartridge->is_MBC1()) {
      return m_cartridge->read_rom0(addr);
    }
    return m_cartridge->direct_read(addr);

  } else if (ROM1(addr)) {
    if (m_cartridge->is_MBC1())
      return m_cartridge->read_rom1((addr - ROM1_OFFSET) & 0x3FFF);
    return m_cartridge->direct_read(addr);
  } else if (VRAM(addr) && m_ppu->get_mode() != 3) {
    return m_vram[addr - VRAM_OFFSET];
  } else if (SRAM(addr)) {
    if (m_cartridge->is_MBC1())
      return m_cartridge->read_ram(addr - SRAM_OFFSET);
  } else if (WRAM(addr)) {
    return m_wram[addr - WRAM_OFFSET];
  } else if (ECHO(addr)) {
    return m_wram[addr - ECHO_OFFSET];
  } else if (OAM(addr) && m_ppu->get_mode() != 2 && m_ppu->get_mode() != 3) {
    if (addr < 0xFEA0)
      return m_oam[addr - OAM_OFFSET];
  } else if (IO(addr)) {
    switch (addr) {
    case 0xFF0F:
      return m_intf;
    case 0xFF04:
      return (uint8_t)rand();
    case 0xFF40:
      return m_ppu->state.control;
    case 0xFF41:
      return m_ppu->read_STAT();
    case 0xFF42:
      return m_ppu->state.scroll_y;
    case 0xFF43:
      return m_ppu->state.scroll_x;
    case 0xFF44:
      return m_ppu->line;
    case 0xFF45:
      return m_ppu->LYC;
    case 0xFF46:
      return DMA;
    case 0xFF47:
      return m_ppu->state.palette;
    case 0xFF48:
      return m_ppu->OBP0;
    case 0xFF49:
      return m_ppu->OBP1;
    case 0xFF4A:
      return m_ppu->state.wy;
    case 0xFF4B:
      return m_ppu->state.wx;
    case 0xFF00: {
      uint8_t r = m_hmi->get_joypad_reg();
      r &= 0xF0;
      if ((r & 0x30) == 0x20) {
        r |= ((~m_hmi->keys) & 0xF);
      } else if ((r & 0x30) == 0x10) {
        r |= ((~m_hmi->keys) >> 4);
      }
      return r;
    }
    default:
      return 0x00;
    }
  } else if (HRAM(addr)) {
    return m_hram[addr - HRAM_OFFSET];
  } else
    return 0x00;
  return 0xFF;
}
void GB::Mem::write(uint16_t addr, uint8_t value) {
  if (ROM0(addr) || ROM1(addr)) {
    if (m_cartridge->is_MBC1()) {
      m_cartridge->write_ctrl(addr, value);
    }
  } else if (VRAM(addr)) {
    m_vram[addr - VRAM_OFFSET] = value;
  } else if (SRAM(addr)) {
    if (m_cartridge->is_MBC1())
      m_cartridge->write_ram(addr - SRAM_OFFSET, value);
  } else if (WRAM(addr)) {
    m_wram[addr - WRAM_OFFSET] = value;
  } else if (ECHO(addr)) {
    m_wram[addr - ECHO_OFFSET] = value;
  } else if (OAM(addr)) {
    if (addr < 0xFEA0)
      m_oam[addr - OAM_OFFSET] = value;
  } else if (IO(addr)) {
    switch (addr) {
    case 0xFF00:
      m_hmi->set_joypad_reg(value & 0x30);
      break;
    case 0xFF0F:
      m_intf = value;
      break;
    case 0xFF40:
      m_ppu->state.control = value;
      break;
    case 0xFF41:
      m_ppu->update_STAT(value);
      break;

    case 0xFF42:
      m_ppu->state.scroll_y = value;
      break;

    case 0xFF43:
      m_ppu->state.scroll_x = value;
      break;

    case 0xFF44:
      m_ppu->line = 0;
      break;

    case 0xFF45:
      m_ppu->LYC = value;
      break;

    case 0xFF46:
      OAM_DMA(value);
      break;

    case 0xFF47:
      m_ppu->state.palette = value;
      break;

    case 0xFF48:
      m_ppu->OBP0 = value;
      break;

    case 0xFF49:
      m_ppu->OBP1 = value;
      break;
    case 0xFF4A:
      m_ppu->state.wy = value;
      break;
    case 0xFF4B:
      m_ppu->state.wx = value;
      break;
    default:
      return;
    }
  } else if (HRAM(addr)) {
    m_hram[addr - HRAM_OFFSET] = value;
  } else
    return;
}

void GB::Mem::OAM_DMA(uint8_t value) {
  DMA = value;
  for (uint8_t i = 0; i < 159; i++) {
    m_oam[i] = read((value << 8) + i);
  }
}

void GB::Mem::log(uint16_t addr) {}

GB::Mem::~Mem() {}
