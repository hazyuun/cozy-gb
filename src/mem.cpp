/*
 *  File: mem.cpp
 *  Description : TODO
 * */

#include "mem.h"
#include "PPU.h"
#include <iostream>
#include <time.h>
extern PPU ppu;
extern Cartridge *cart;
Mem::Mem() {
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
  std::cout << "[MEM] ready !" << std::endl;
}
void Mem::load(unsigned char *data, uint64_t size, uint16_t addr) {
  for (uint16_t pos = addr; pos < addr + size; pos++) {
    *(memory + pos) = *(data + pos - addr);
  }
}

void Mem::setCartType(uint8_t type) { cart_type = type; }

unsigned char Mem::read(uint16_t addr) {
  if (addr >= 0xA000 && addr <= 0xBFFF && cart_type) {
    return dynamic_cast<MBC1_Cartridge *>(cart)->readFromRAM(addr - 0xA000);
  }
  if (ROM0(addr) && cart_type) {
    return dynamic_cast<MBC1_Cartridge *>(cart)->read(addr);
  }
  if (ROM1(addr) && cart_type) {
    return dynamic_cast<MBC1_Cartridge *>(cart)->readFromCurrentBank(addr -
                                                                     0x4000);
  }

  if (addr >= 0xFEA0 && addr <= 0xFEFF)
    return 0xFF;
  if (addr == 0xFF04)
    return (uint8_t)rand();
  if (addr == 0xFF40)
    return ppu.state.control;
  if (addr == 0xFF41)
    return ppu.read_STAT();
  if (addr == 0xFF42)
    return ppu.state.scroll_y;
  if (addr == 0xFF43)
    return ppu.state.scroll_x;
  if (addr == 0xFF44)
    return ppu.line;
  if (addr == 0xFF45)
    return ppu.LYC;
  if (addr == 0xFF46)
    return DMA;
  if (addr == 0xFF47)
    return 0xFF;
  if (addr == 0xFF48)
    return 0xFF;
  if (addr == 0xFF49)
    return 0xFF;
  if (addr == 0xFF00) {
    uint8_t r = memory[addr];
    r &= 0xF0;
    switch ((r & 0x30)) {
    case 0x20:
      r |= ((~lcd.keys) & 0xF);
      break;
    case 0x10:
      r |= ((~lcd.keys) >> 4);
      break;
    }
    return r;
  }

  return memory[addr];
}
void Mem::write(uint16_t addr, unsigned char value) {
  if (cart_type && addr >= 0xA000 && addr <= 0xBFFF)
    dynamic_cast<MBC1_Cartridge *>(cart)->writeToRAM(addr - 0xA000, value);
  if (ROM0(addr) || ROM1(addr)) {
    if (cart_type) {
      if (cart_type == 2 || cart_type == 3) {
        if (MBC1_RAM_ENABLE(addr)) {
          dynamic_cast<MBC1_Cartridge *>(cart)->setRAMEnable(
              ((value & 0x0F) == 0x0A ? 1 : 0));
        }

        if (MBC1_MODE_SELECT(addr)) {
          uint8_t x = !(value & 1);
          dynamic_cast<MBC1_Cartridge *>(cart)->setMode(x);
          if (x)
            dynamic_cast<MBC1_Cartridge *>(cart)->setRAMBank(0);
          printf("\n\nMode change : %d",
                 dynamic_cast<MBC1_Cartridge *>(cart)->getMode());
        }
      }
      if (MBC1_ROM_BANK(addr)) {
        MBC1_Cartridge *mbc1_cart = dynamic_cast<MBC1_Cartridge *>(cart);

        uint8_t v = value & 0x1f;
        uint8_t rbnk = mbc1_cart->getROMBank();
        rbnk &= 224;
        rbnk |= v;
        if (!rbnk)
          rbnk = 1;
        mbc1_cart->setROMBank(rbnk);
      }

      if (MBC1_RAM_BANK(addr)) {
        MBC1_Cartridge *mbc1_cart = dynamic_cast<MBC1_Cartridge *>(cart);
        if (mbc1_cart->getMode()) {
          mbc1_cart->setRAMBank(value & 3);
        } else {
          uint8_t old = mbc1_cart->getROMBank();
          uint8_t n = old & 31;
          n |= (value & 224);
          if (!n)
            n = 1;
          mbc1_cart->setROMBank(n);
        }
      }
      return;
    } else
      return;
  }

  if (addr == 0xFF04)
    return;
  if (addr >= 0xFEA0 && addr <= 0xFEFF)
    return;
  if (addr == 0xFF40)
    ppu.state.control = value;
  else if (addr == 0xFF41)
    ppu.update_STAT(value);
  else if (addr == 0xFF42)
    ppu.state.scroll_y = value;
  else if (addr == 0xFF43)
    ppu.state.scroll_x = value;
  else if (addr == 0xFF44)
    ppu.line *= 0;
  else if (addr == 0xFF45)
    ppu.LYC = value;
  else if (addr == 0xFF46)
    OAM_DMA(value);
  else if (addr == 0xFF47)
    ppu.state.palette = value;
  else if (addr == 0xFF48)
    ppu.OBP0 = value;
  else if (addr == 0xFF49)
    ppu.OBP1 = value;
  else if (addr == 0xFF00)
    memory[addr] = (value & 0x30);
  else if (addr == 0xFF04)
    return;

  // else if(addr == 0xFF80) return;
  // else if(addr == 0xFF00) return;
  else
    memory[addr] = value;
}

void Mem::OAM_DMA(uint8_t value) {
  DMA = value;
  for (uint8_t i = 0; i < 160; i++)
    mem.write(OAM_OFFSET + i, mem.read((value << 8) + i));
}

void Mem::log(uint16_t addr) {}

Mem::~Mem() {}
