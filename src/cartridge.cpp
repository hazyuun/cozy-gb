#include <cartridge.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <sys/io.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

GB::Cartridge::Cartridge(const char *rom_file) {
  std::ifstream file(rom_file, std::ios::in | std::ios::binary | std::ios::ate);
  uint64_t size = file.tellg();
  file.seekg(0, std::ios::beg);
  m_rom = new uint8_t[size];
  char *buffer = new char[size];
  file.read(buffer, size);
  file.close();
  memcpy(m_rom, buffer, size);
  delete[] buffer;
  m_mbc_type = m_rom[0x147];

  memcpy(m_name, m_rom + 0x134, 16);
  if (m_mbc_type && !MBC1(m_mbc_type)) {
    std::cout << "[ROM] Unsupported MBC : ";
    printf("0x%X", m_mbc_type);
    exit(-1);
  }

  std::cout << "[ROM] loaded " << size << " bytes" << std::endl;
  std::cout << "[ROM] Game : " << m_name << std::endl;

  std::ifstream save_file(m_name, std::ios::in | std::ios::binary);
  if(!save_file) {
    std::cout << "[ROM] Can't open the save file" << std::endl;
    return;
  }
  
  buffer = new char[16*1024];
  save_file.read(buffer, 16*1024);
  save_file.close();
  memcpy(m_ram, buffer, 16*1024);


}

GB::Cartridge::~Cartridge() { 
  delete[] m_rom;
}

uint8_t GB::Cartridge::read_rom0(uint16_t addr) {
  if (m_mode) {

    uint64_t rom_bank = (m_rom_bank_hi << 5);
    return direct_read((rom_bank * 0x4000) + addr);
  } else
    return direct_read(addr);
}
uint8_t GB::Cartridge::read_rom1(uint16_t addr) {
  uint64_t rom_bank = (m_rom_bank_hi << 5) | m_rom_bank_lo;
  return direct_read((rom_bank * 0x4000) + addr);
}

void GB::Cartridge::write_ctrl(uint16_t addr, uint8_t value) {
  if (MBC1_RAM_ENABLE(addr)) {
    set_ram_enable((value & 0x0F) == 0x0A);
  }

  else if (MBC1_MODE_SELECT(addr)) {
    m_mode = (value & 0x1);
    if (m_mode)
      m_rom_bank_hi = 0;
  }

  else if (MBC1_ROM_BANK(addr)) {
    uint8_t lo = value & 0x1f;
    if (lo == 0x00 
     || lo == 0x20
     || lo == 0x40
     || lo == 0x60)
     ++ lo;
    if(m_mode){
      m_rom_bank_hi = 0;
      m_rom_bank_lo = lo;
    }else{
      m_rom_bank_lo = lo;
    }
    
  }

  else if (MBC1_RAM_BANK(addr)) {
    if (m_mode) {
      m_ram_bank = value & 0x3;
    } else {
      m_rom_bank_hi = value & 0x3;

    }
  }
}

uint8_t GB::Cartridge::direct_read(uint64_t addr) { return m_rom[addr]; }

uint8_t GB::Cartridge::read_ram(uint16_t addr) {
  if (!m_ram_enable)
    return 0xFF;
  return m_ram[addr + (m_ram_bank * 0x2000)];
}
void GB::Cartridge::write_ram(uint16_t addr, uint8_t value) {
  if (!m_ram_enable)
    return;
  m_ram[addr + (m_ram_bank * 0x2000)] = value;

  std::ofstream save_file(m_name, std::ios::out | std::ios::binary);
  if(!save_file) {
    std::cout << "[ROM] Can't open the save file" << std::endl;
    return;
  }
  
  save_file.write((char*) m_ram, 16 * 1024);
  save_file.close();
}
