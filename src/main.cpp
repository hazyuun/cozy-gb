#include "Z80.h"
#include "mem.h"
#include "LCD.h"
#include <iostream>
#include <fstream>

#define I_LIKE_RAIN true

Mem mem;
Z80 cpu;
unsigned char* ROM;
int main(int argc, char** argv){
    LCD lcd = LCD(200, 200, "LCD");
    while(lcd.should_close()){
        lcd.clear();
        lcd.update();
    }
    
    return 0;
    if(argc != 2){
    	std::cout<<"NO ROM !"<<std::endl;
    	return 1;
    }
    std::ifstream file(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
    uint64_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    char* buffer = new char[size];
    file.read(buffer, size);
    file.close();
    mem.load((unsigned char*) buffer, size, 0x0000);

    std::cout<<"[ROM] loaded "<<size<<" bytes"<<std::endl;
    
    while(I_LIKE_RAIN){    
        cpu.cycle();
    }
    return 0;
}

