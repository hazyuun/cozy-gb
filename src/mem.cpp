/*
 *  File: mem.cpp
 *  Description : TODO
 * */

#include "mem.h"
#include "PPU.h"
#include <iostream>

extern PPU ppu;

Mem::Mem(){
    write(0xFF00, 0xCF);
    write(0xFF05, 0x0); 
    write(0xFF06, 0x0); 
    write(0xFF07, 0x0); 
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
    std::cout<<"[MEM] ready !"<<std::endl;
}
void Mem::load(unsigned char* data, uint64_t size, uint16_t addr){
    for(uint16_t pos = addr; pos < size; pos++){
        *(memory + pos) = *(data + pos - addr);
    }
}



unsigned char Mem::read(uint16_t addr){
    /*
        0xFF40	LCD and GPU control	Read/write
        0xFF42	Scroll-Y	Read/write
        0xFF43	Scroll-X	Read/write
        0xFF44	Current scan line	Read only
        0xFF47	Background palette	Write only
    */
    if(addr == 0xFF40) return ppu.state.control;
    if(addr == 0xFF42) return ppu.state.scroll_y;
    if(addr == 0xFF43) return ppu.state.scroll_x;
    if(addr == 0xFF44) return ppu.line;
    if(addr == 0xFF47) return 0xFF;
    
    return memory[addr];
} 
void Mem::write(uint16_t addr, unsigned char value){
    
    if(VRAM(addr)) fprintf(stdout, "VRAM accessed ! [0x%0004X] \n", addr);
    if(addr == 0xFF40) ppu.state.control = value;
    else if(addr == 0xFF42) ppu.state.scroll_y = value;
    else if(addr == 0xFF43) ppu.state.scroll_x = value;
    else if(addr == 0xFF44) ppu.line *= 1;
    else if(addr == 0xFF47) ppu.state.palette = value;
    
    else memory[addr] = value;
}
void Mem::log(uint16_t addr){
    
}

Mem::~Mem(){

}
