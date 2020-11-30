#include "Z80.h"
#include "mem.h"
#include "PPU.h"
#include "HMI.h"
#include <iostream>
#include <fstream>

#define I_LIKE_RAIN true

Mem mem;
Z80 cpu;
PPU ppu;
LCD lcd = LCD(2*160, 2*144, "LCD");
unsigned char* ROM;
bool debug;

int main(int argc, char** argv){

    if(argc != 2){
    	std::cout<<"NO ROM !"<<std::endl;
    	return 1;
    }
    if(argc >= 3) debug = argv[2] == "--debug";
    else debug = false;
    std::ifstream file(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
    uint64_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    char* buffer = new char[size];
    file.read(buffer, size);
    file.close();
    mem.load((unsigned char*) buffer, size, 0x0000);

    std::cout<<"[ROM] loaded "<<size<<" bytes"<<std::endl;
    delete[] buffer;
    long long k = 0;
    while(I_LIKE_RAIN && !lcd.should_close()){
        //if(k++ % 1500 != 0) continue;
        cpu.cycle();
        ppu.step();

    }

    return 0;
}
