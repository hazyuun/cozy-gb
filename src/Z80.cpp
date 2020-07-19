/*
 *  File : Z80.cpp
 *  Description : TODO
 * */
#include <iostream>
#include "Z80.h"
#include "mem.h"
extern Mem mem;

Z80::Z80(){
    registers.AF = 0x0000;
    registers.BC = 0x0000;
    registers.DE = 0x0000;
    registers.HL = 0x0000;
    registers.SP = 0x0000;
    registers.PC = 0x0000;

    std::cout<<"[CPU] ready !"<<std::endl;
}
void Z80::cycle(){
    uint16_t opcode = mem.read(registers.PC) << 8 | mem.read(registers.PC+1);
    //std::cout<<"0x"<<std::hex<<((opcode<<8)|mem.read(registers.PC+2))<<"\t\t";
   
    Z80::inst_t inst;
    
    
    if(((opcode & 0xFF00)>>8) != 0xCB)
        inst = insts[(opcode & 0xFF00)>>8];
    else{
        inst = CB_insts[(opcode & 0xFF)];
    }
    
    switch(inst.size){
    case 1:
        registers.PC++;
        fprintf(stdout, inst._asm);
        break;
    case 2:
        registers.PC += 2;
        fprintf(stdout, inst._asm, (opcode & 0xFF));
        break;
    case 3:
        fprintf(stdout, inst._asm, ((mem.read(registers.PC+2)<<8)|(opcode & 0xFF)));
        registers.PC += 3;
        break;

    }
}
Z80::~Z80(){

}
