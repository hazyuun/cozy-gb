#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

#define MBC1_RAM_ENABLE(a)    ((a >= 0x0000) && (a <= 0x1FFF))
#define MBC1_ROM_BANK(a)      ((a >= 0x2000) && (a <= 0x3FFF))
#define MBC1_RAM_BANK(a)      ((a >= 0x4000) && (a <= 0x5FFF))
#define MBC1_MODE_SELECT(a)   ((a >= 0x6000) && (a <= 0x7FFF))

#define MBC1(type) ((type >= 1) && (type <= 3))

namespace GB {
class Cartridge {
  char m_name[16];
  uint8_t *m_rom;
  uint8_t m_mbc_type;

  /* MBC1 stuff */
  
  /* TODO: memory map this file for faster read/write */
  
  uint8_t m_ram[16*1024];

  uint8_t m_mode = 0;

  uint8_t m_rom_bank_hi = 0x0;
  uint8_t m_rom_bank_lo = 0x1;
  
  uint8_t m_ram_enable = 1;
  uint64_t m_ram_bank = 0;


public:
  Cartridge(const char *rom_file);
  ~Cartridge();

  uint8_t direct_read(uint64_t addr);
  uint8_t read_from_current_bank(uint16_t addr);
  
  
  uint8_t read_rom0(uint16_t addr);
  uint8_t read_rom1(uint16_t addr);
  void write_ctrl(uint16_t addr, uint8_t value);

  inline uint8_t get_mbc_type() const { return m_mbc_type; };

  inline bool is_MBC1() const { return MBC1(m_mbc_type); };

  inline uint8_t get_mode() const { return m_mode; };
  inline uint8_t get_ram_enable() const { return m_ram_enable; };
  inline uint8_t get_ram_bank() const { return m_ram_bank; };

  inline void set_mode(uint8_t value) { m_mode = value; };
  inline void set_ram_enable(uint8_t value) { m_ram_enable = value; };
  inline void set_ram_bank(uint8_t value) { m_ram_bank = value; };

  
  uint8_t read_ram(uint16_t addr);
  void write_ram(uint16_t addr, uint8_t value);
};
}
