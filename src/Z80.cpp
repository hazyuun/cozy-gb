/*
 *  File : Z80.cpp
 *  Description : TODO
 * */
#include <iostream>
#include <iomanip>
#include "Z80.h"
#include "HMI.h"
#include "mem.h"

extern Mem mem;
extern LCD lcd;
extern bool debug;

Z80::Z80(){
    registers.AF = 0x01B0;
    registers.BC = 0x0013;
    registers.DE = 0x00D8;
    registers.HL = 0x014D;
    registers.SP = 0xFFFE;
    registers.PC = 0x0100;
    cycles = 144;
    std::cout<<"[CPU] ready !"<<std::endl;
}

void Z80::cycle(){

    if(IME && mem.read(INT_ENABLE) && mem.read(INT_FLAGS)){

        if(INT_TEST(INT_VBLANK)){
            IME = false;
            INT_ACK(INT_VBLANK);
            i_0xcd(INT_VBLANK_ISR);
		  cycles += 8;

        }

        if(INT_TEST(INT_STAT)){
            IME = false;
            INT_ACK(INT_STAT);
            i_0xcd(INT_STAT_ISR);
		  cycles += 8;

        }

        if(INT_TEST(INT_TIMER)){
            IME = false;
            INT_ACK(INT_TIMER);
            i_0xcd(INT_TIMER_ISR);
		  cycles += 8;

        }

        if(INT_TEST(INT_SERIAL)){
            IME = false;
            INT_ACK(INT_SERIAL);
            i_0xcd(INT_SERIAL_ISR);
		  cycles += 8;

        }

        if(INT_TEST(INT_JOYPAD)){
            IME = false;
            INT_ACK(INT_JOYPAD);
            i_0xcd(INT_JOYPAD_ISR);
		  cycles += 8;

        }
        HALT = false;
    }
    if(HALT) return;

    if(debug) std::cout<<std::setw(8)<<"\n0x"<<std::hex<<registers.PC<<"\t";
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
        //fprintf(stdout, "\t");
        break;
    case 2:
        registers.PC += 2;
        inst_hex = opcode;
        inst_arg = inst_hex & 0x00FF;
        //fprintf(stdout, "(%x) = %x\t",inst_arg, mem.read(inst_arg));
        break;
    case 3:

    	inst_hex = (opcode<<8)|mem.read(registers.PC+2);
    	inst_arg = ((inst_hex&0x00FF)<<8)|((inst_hex&0xFF00)>>8);
    	registers.PC += 3;
        //fprintf(stdout, "\t");
        break;

    }

    if(debug){
        std::cout<<std::setw(8)<<"0x"<<std::hex<<inst_hex<<"\t\t";
        if		(inst.size != 1) 	fprintf(stdout, inst._asm, inst_arg);
        else 						fprintf(stdout, inst._asm);
    }
    if(!inst.function){
    	std::cout<<"\nUnknown opcode ! "<<std::endl;
        debug = true;
    	return;
    }

    (this->*inst.function)(inst_arg);


    /* WARNING ! messy stuff ahead ! but it is temporary */
    cycles += inst.cycles;

    if(debug){

        std::cout<<"\n*** Memory ***\n";
        for(uint16_t a= 0x8000; a < (0x8010); a++){
            if((a & 0xF) == 0) printf("\n[ %0004X ] ", a);
            printf(" %02X", mem.read(a));
        }

        std::cout<<"\n*** Registers ***\n";
        fprintf(stdout, "A = %x \t F = %x\n", registers.A, registers.F);
        fprintf(stdout, "B = %x \t C = %x\n", registers.B, registers.C);
        fprintf(stdout, "D = %x \t E = %x\n", registers.D, registers.E);
        fprintf(stdout, "H = %x \t L = %x\n", registers.H, registers.L);
        fprintf(stdout, "SP = %x\n", registers.SP);
        fprintf(stdout, "PC = %x\n", registers.PC);
        fprintf(stdout, "Z N H C\n%d %d %d %d\n\n",    ((registers.F & 0x80) == 0x80)?1:0,
                                                    ((registers.F & 0x40) == 0x40)?1:0,
                                                    ((registers.F & 0x20) == 0x20)?1:0,
                                                    ((registers.F & 0x10) == 0x10)?1:0);

        //std::cin.get();
    }

#if 1
    if (mem.read(0xff02) == (unsigned char)0x81) {
        unsigned char c = mem.read(0xff01);
        printf("%c", c);
        mem.write(0xff02, 0x0);
    }
#endif
}
Z80::~Z80(){

}
