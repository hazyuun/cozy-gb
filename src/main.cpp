#include "Z80.h"
#include "mem.h"
#include <iostream>
#include <fstream>

#define I_LIKE_RAIN true

Mem mem;
Z80 cpu;

int main(int argc, char** argv){
    if(argc != 2)
        return 1;
    
    std::ifstream file(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
    uint64_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    char* buffer = new char[size];
    file.read(buffer, size);
    file.close();
    mem.load((unsigned char*) buffer, size, 0x0000);

    std::cout<<"[ROM] loaded "<<size<<" bytes"<<std::endl;
    int k = 0;
//    while(k<length)
//        std::cout<<"0x"<<std::hex<<(unsigned char*)buffer[k++]<<" ";
    while(I_LIKE_RAIN){
        std::cin.get();
        cpu.cycle();
    }
    return 0;
}

