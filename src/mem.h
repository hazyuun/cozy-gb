/*
 *  File: mem.h
 *  Description : TODO
 * */

#pragma once
#include <cstdint>
#include "ROM.h"

#define ROM0_OFFSET    0x0000
#define ROM1_OFFSET    0x4000
#define VRAM_OFFSET    0x8000
#define SRAM_OFFSET    0xA000
#define WRAM_OFFSET    0xC000
#define ECHO_OFFSET    0xE000
#define OAM_OFFSET     0xFE00
#define IO_OFFSET      0xFF00
#define HRAM_OFFSET    0xFF80

#define ROM0(address)   ((address >= ROM0_OFFSET) && (address < ROM1_OFFSET))
#define ROM1(address)   ((address >= ROM1_OFFSET) && (address < VRAM_OFFSET))
#define VRAM(address)   ((address >= VRAM_OFFSET) && (address < SRAM_OFFSET))
#define SRAM(address)   ((address >= SRAM_OFFSET) && (address < WRAM_OFFSET))
#define WRAM(address)   ((address >= WRAM_OFFSET) && (address < ECHO_OFFSET))
#define ECHO(address)   ((address >= ECHO_OFFSET) && (address < OAM_OFFSET))
#define OAM(address)    ((address >= OAM_OFFSET) && (address < IO_OFFSET))
#define IO(address)     ((address >= IO_OFFSET) && (address < HRAM_OFFSET))
#define HRAM(address)   ((address >= HRAM_OFFSET))

#define INT_VBLANK_ISR	0x40
#define INT_STAT_ISR	0x48
#define INT_TIMER_ISR	0x50
#define INT_SERIAL_ISR	0x58
#define INT_JOYPAD_ISR	0x60

#define INT_ENABLE		0xFFFF
#define INT_FLAGS		0xFF0F

#define INT_VBLANK	(1 << 0)
#define INT_STAT	(1 << 1)
#define INT_TIMER	(1 << 2)
#define INT_SERIAL	(1 << 3)
#define INT_JOYPAD	(1 << 4)


#define INT_RAISE(i)    mem.write(INT_FLAGS, mem.read(INT_FLAGS) | i)
#define INT_ACK(i)      mem.write(INT_FLAGS, mem.read(INT_FLAGS) & (~i))
#define INT_TEST(i)     ((mem.read(INT_ENABLE) & i)&&(mem.read(INT_FLAGS) & i))

class Mem{
    private:
    unsigned char memory[64*1024];
    uint8_t DMA;
    uint8_t cart_type;
    public:
    Mem();
    void load(unsigned char* data, uint64_t size, uint16_t addr);
    void setCartType(uint8_t type);
    
    unsigned char read(uint16_t addr);
    void write(uint16_t addr, unsigned char value);

    void OAM_DMA(uint8_t);

    void log(uint16_t addr);
    ~Mem();
};
