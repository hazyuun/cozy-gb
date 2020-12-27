#pragma once

#include <cstddef>

namespace GB {
class Z80;
class PPU;
class Mem;
class HMI;
class Cartridge;

class Gameboy {
  GB::Z80 *m_cpu;
  GB::PPU *m_ppu;
  GB::Mem *m_mem;
  GB::HMI *m_hmi;
  GB::Cartridge *m_cartridge;

  void loop();

public:
  Gameboy(const char *rom_file);
  ~Gameboy();

  friend class Z80;
  friend class PPU;
  friend class Mem;
  friend class HMI;
  friend class Cartridge;
};

}