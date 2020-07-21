/*
 *  File : Z80.cpp
 *  Description : TODO
 * */
#include <iostream>
#include <iomanip>
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

    Z80::inst_t inst;
    
    
    if(((opcode & 0xFF00)>>8) != 0xCB)
        inst = insts[(opcode & 0xFF00)>>8];
    else{
        inst = CB_insts[(opcode & 0xFF)];
    }
    uint32_t inst_hex;
    uint16_t inst_arg;
    switch(inst.size){
    case 1:
        registers.PC++;
        inst_hex = (opcode>>8);
        inst_arg = 0x0;
        break;
    case 2:
        registers.PC += 2;
        inst_hex = opcode;
        inst_arg = inst_hex & 0x00FF;
        break;
    case 3:

    	inst_hex = (opcode<<8)|mem.read(registers.PC+2);
    	inst_arg = ((inst_hex&0x00FF)<<8)|((inst_hex&0xFF00)>>8);
    	registers.PC += 3;
        break;
    }

    std::cout<<std::setw(8)<<"0x"<<std::hex<<registers.PC<<"\t"
             <<std::setw(8)<<"0x"<<std::hex<<inst_hex<<"\t\t";
    if		(inst.size != 1) 	fprintf(stdout, inst._asm, inst_arg);
    else 						fprintf(stdout, inst._asm);

    if(!inst.function){
    	std::cout<<"\nUnknown opcode ! "<<std::endl;
    	return;
    }

    (this->*inst.function)(inst_arg);
}
Z80::~Z80(){

}
