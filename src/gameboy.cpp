#include <HMI.h>
#include <PPU.h>
#include <Z80.h>
#include <gameboy.h>
#include <mem.h>

#include <chrono>

GB::Gameboy::Gameboy(const char *rom_file) {

  m_cpu = new GB::Z80(NULL);
  m_ppu = new GB::PPU(NULL, NULL, NULL);
  m_hmi = new GB::HMI(2 * 160, 2 * 144, "LCD", NULL);
  m_cartridge = new GB::Cartridge(rom_file);
  m_mem = new GB::Mem(m_cartridge, m_ppu, m_hmi);

  m_cpu->setup(m_mem);
  m_ppu->setup(m_mem, m_cpu, m_hmi);
  m_hmi->setup(m_mem);

  loop();
}

void GB::Gameboy::loop() {
  size_t cycles = 0;

  while (!m_hmi->should_close()) {
    auto t0 = std::chrono::high_resolution_clock::now();
    m_cpu->step();
    cycles += m_cpu->get_cycle_count();
    if (cycles >= 17476) {
      cycles = 0;
      while (std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::high_resolution_clock::now() - t0)
                 .count() < 2)
        ;
    }
    m_ppu->step();
  }
}

GB::Gameboy::~Gameboy() {
  delete m_cpu;
  delete m_ppu;
  delete m_hmi;
  delete m_cartridge;
  delete m_mem;
}
