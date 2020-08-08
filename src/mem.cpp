/*
 *  File: mem.cpp
 *  Description : TODO
 * */

#include "mem.h"
#include <iostream>

Mem::Mem(){
    //write(0xFF44, 0x90);
    std::cout<<"[MEM] ready !"<<std::endl;
}
void Mem::load(unsigned char* data, uint64_t size, uint16_t addr){
    for(uint16_t pos = addr; pos < size; pos++){
        *(memory + pos) = *(data + pos - addr);
    }
}



unsigned char Mem::read(uint16_t addr){
    return memory[addr];
} 
void Mem::write(uint16_t addr, unsigned char value){
    memory[addr] = value;
}
void Mem::log(uint16_t addr){
    
}

Mem::~Mem(){

}
