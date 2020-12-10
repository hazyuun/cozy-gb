#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

#define MBC1_RAM_ENABLE(a) ((a >= 0x0000) && (a <= 0x1FFF))
#define MBC1_ROM_BANK(a) ((a >= 0x2000) && (a <= 0x3FFF))
#define MBC1_RAM_BANK(a) ((a >= 0x4000) && (a <= 0x5FFF))
#define MBC1_MODE_SELECT(a) ((a >= 0x6000) && (a <= 0x7FFF))

#define MBC1(type) ((type >= 1) && (type <= 3))

class ROM_header {

public:
  uint8_t m_header[0x150];

  ROM_header(unsigned char *raw, size_t size);
  std::string getTitle();
  uint8_t getType();
};

class Cartridge {
public:
  inline virtual uint8_t getType() const { return 0; };
  virtual ~Cartridge();
};

class MBC1_Cartridge : public Cartridge {
  uint8_t m_rom[2 * 1024 * 1024];
  uint8_t m_ROM_bank = 1;
  uint8_t m_RAM_bank = 0;
  uint8_t m_mode = 1;
  uint8_t m_RAM_enable = 1;

  uint8_t m_RAM[32 * 1024];

public:
  inline uint8_t getType() const { return 0x1; };
  MBC1_Cartridge(unsigned char *raw, size_t size);
  ~MBC1_Cartridge();
  inline uint8_t read(uint16_t addr) const { return m_rom[addr]; };

  inline uint8_t getMode() const { return m_mode; };
  inline uint8_t getRAMEnable() const { return m_RAM_enable; };
  inline uint8_t getROMBank() const { return m_ROM_bank; };
  inline uint8_t getRAMBank() const { return m_RAM_bank; };

  inline void setMode(uint8_t value) { m_mode = value; };
  inline void setRAMEnable(uint8_t value) { m_RAM_enable = value; };
  inline void setROMBank(uint8_t value) { m_ROM_bank = value; };
  inline void setRAMBank(uint8_t value) { m_RAM_bank = value; };

  inline uint8_t readFromCurrentBank(uint16_t addr) {
    // printf("Accessing ROM bank : %d \n",m_ROM_bank);
    return read((m_ROM_bank * 0x4000) + addr);
  }
  inline uint8_t readFromRAM(uint16_t addr) {
    // printf("Accessing RAM bank : %d \n",m_RAM_bank);

    return m_RAM[(m_RAM_bank * 0x2000) + addr];
  }
  inline void writeToRAM(uint16_t addr, uint8_t value) {
    // printf("Writing to RAM bank : %d \n",m_RAM_bank);
    if (!m_RAM_enable)
      return;
    m_RAM[(m_RAM_bank * 0x2000) + addr] = value;
  }
};
