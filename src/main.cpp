#include "Z80.h"
#include "mem.h"
#include "PPU.h"
#include "HMI.h"
#include "ROM.h"
#include <iostream>
#include <fstream>

#define I_LIKE_RAIN true

Mem mem;
Z80 cpu;
PPU ppu;
LCD lcd = LCD(2*160, 2*144, "LCD");
Cartridge* cart;
//unsigned char* ROM;


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
    //mem.load((unsigned char*) buffer, size, 0x0000);
    ROM_header header = ROM_header((uint8_t *)buffer, size);
    
    std::cout<< "[ROM] Title : " << header.getTitle()<<"\n";
    uint8_t mbc_type = header.getType();
    printf("%x", mbc_type);
    switch(mbc_type){
        case 0x0: std::cout<< "[ROM] MBC : None \n";
                mem.load((unsigned char*) buffer, size, 0x0000);
                break;
        case 0x1:
        case 0x2:
        case 0x3:
                std::cout<< "[ROM] MBC : 1 \n";
                cart = new MBC1_Cartridge((uint8_t *)buffer, size); 
                mem.setCartType(mbc_type);
                break;
        default: std::cout<< "[ROM] Unsupported MBC \n";
                return 1;
    }
    


    std::cout<<"[ROM] loaded "<<size<<" bytes"<<std::endl;
    delete[] buffer;

    long long k = 0;
    while(I_LIKE_RAIN && !lcd.should_close()){
        //if(k++ % 1500 != 0) continue;
        printf("\n mode %d", dynamic_cast<MBC1_Cartridge *>(cart)->getMode());
        cpu.cycle();
        ppu.step();

    }

    return 0;
}
