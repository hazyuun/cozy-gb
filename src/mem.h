/*
 *  File: mem.h
 *  Description : TODO
 * */

#pragma once
#include <cstdint>
class Mem{
    private:
    unsigned char memory[8*1024]; /* 8 KiB */
    public:
    Mem();
    void load(unsigned char* data, uint64_t size, uint16_t addr);
    unsigned char read(uint16_t addr); 
    void log(uint16_t addr);
    ~Mem();
};

