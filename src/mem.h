/*
 *  File: mem.h
 *  Description : TODO
 * */

#pragma once
#include <cstdint>
class Mem{
    private:
    unsigned char memory[64*1024];
    public:
    Mem();
    void load(unsigned char* data, uint64_t size, uint16_t addr);
    unsigned char read(uint16_t addr); 
    void write(uint16_t addr, unsigned char value);

    void log(uint16_t addr);
    ~Mem();
};

