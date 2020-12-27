#include <Z80.h>
#include <iomanip>
#include <iostream>
#include <mem.h>

using namespace GB;

Z80::Z80(GB::Mem *mem) {
  registers.AF = 0x01B0;
  registers.BC = 0x0013;
  registers.DE = 0x00D8;
  registers.HL = 0x014D;
  registers.SP = 0xFFFE;
  registers.PC = 0x0100;
  cycles = 144;
  m_mem = mem;
  std::cout << "[CPU] ready !" << std::endl;
}
void Z80::setup(GB::Mem *mem) { m_mem = mem; }

void Z80::handle_int(uint8_t interrupt, uint16_t isr) {
  IME = false;
  INT_ACK(interrupt);
  i_0xcd(isr);
  cycles += 8;
  HALT = false;
}

void Z80::step() {
  /* Handle interrupts */
  if (IME && m_mem->read(INT_ENABLE) && m_mem->read(INT_FLAGS)) {
    if (INT_TEST(INT_VBLANK)) {
      handle_int(INT_VBLANK, INT_VBLANK_ISR);
      return;
    } else if (INT_TEST(INT_STAT)) {
      handle_int(INT_STAT, INT_STAT_ISR);
      return;
    }

    else if (INT_TEST(INT_TIMER)) {
      handle_int(INT_TIMER, INT_TIMER_ISR);
      return;
    }

    else if (INT_TEST(INT_SERIAL)) {
      handle_int(INT_SERIAL, INT_SERIAL_ISR);
      return;
    } else if (INT_TEST(INT_JOYPAD)) {
      handle_int(INT_JOYPAD, INT_JOYPAD_ISR);
      return;
    }
  }
  if (IME && HALT)
    return;

  /* Fetch next opcode and execute it */
  uint16_t opcode =
      m_mem->read(registers.PC) << 8 | m_mem->read(registers.PC + 1);

  Z80::inst_t inst;

  if (((opcode & 0xFF00) >> 8) != 0xCB)
    inst = insts[(opcode & 0xFF00) >> 8];
  else {
    inst = CB_insts[(opcode & 0xFF)];
  }
  uint32_t inst_hex;
  uint16_t inst_arg;
  switch (inst.size) {
  case 1:
    registers.PC++;
    inst_hex = (opcode >> 8);
    inst_arg = 0x0;
    break;
  case 2:
    registers.PC += 2;
    inst_hex = opcode;
    inst_arg = inst_hex & 0x00FF;
    break;
  case 3:

    inst_hex = (opcode << 8) | m_mem->read(registers.PC + 2);
    inst_arg = ((inst_hex & 0x00FF) << 8) | ((inst_hex & 0xFF00) >> 8);
    registers.PC += 3;
    break;
  }

  if (!inst.function) {
    std::cout << "\nUnknown opcode ! " << std::endl;
    return;
  }

  (this->*inst.function)(inst_arg);
  cycles = inst.cycles;

}

void Z80::print_registers() {
  std::cout << "\n*** Registers ***\n";
  fprintf(stdout, "A = %x \t F = %x\n", registers.A, registers.F);
  fprintf(stdout, "B = %x \t C = %x\n", registers.B, registers.C);
  fprintf(stdout, "D = %x \t E = %x\n", registers.D, registers.E);
  fprintf(stdout, "H = %x \t L = %x\n", registers.H, registers.L);
  fprintf(stdout, "SP = %x\n", registers.SP);
  fprintf(stdout, "PC = %x\n", registers.PC);
  fprintf(stdout, "Z N H C\n%d %d %d %d\n\n",
          ((registers.F & 0x80) == 0x80) ? 1 : 0,
          ((registers.F & 0x40) == 0x40) ? 1 : 0,
          ((registers.F & 0x20) == 0x20) ? 1 : 0,
          ((registers.F & 0x10) == 0x10) ? 1 : 0);
}
Z80::~Z80() {}
