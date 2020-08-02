/*
 *  File : Z80.h
 *  Description : TODO
 * */

#pragma once
#include <cstdint>
#include <cstddef>
#include <iostream>
extern unsigned char* ROM;
class Z80{
    private:
    struct registers{
        struct {
		    union {
			    struct {
				    uint8_t F;
				    uint8_t A;
			    };
			    uint16_t AF;
		    };
	    };

        struct {
		    union {
			    struct {
				    uint8_t C;
				    uint8_t B;
			    };
			    uint16_t BC;
		    };
	    };
        struct {
		    union {
			    struct {
				    uint8_t E;
				    uint8_t D;
			    };
			    uint16_t DE;
		    };
	    };

        struct {
		    union {
			    struct {
				    uint8_t L;
				    uint8_t H;
			    };
			    uint16_t HL;
		    };
	    };
	    uint16_t SP;
	    uint16_t PC;
    } registers;
    bool HALT = false;
    bool STOP = false;
    bool IME = false;
    typedef struct {
        uint8_t opcode;
        char*   _asm;
        uint8_t cycles;
        uint8_t alt_cycles;
        uint8_t size;
        void(Z80::*function)(uint16_t);
    } inst_t;

    void _ADD(uint8_t n);
    void _ADC(uint8_t n);
    void _SDC(uint8_t n);
    void _SUB(uint8_t n);
    void _AND(uint8_t n);
    void _OR(uint8_t n);
    void _XOR(uint8_t n);
    void _CP(uint8_t n);
    void _INC(uint8_t* n);
    void _DEC(uint8_t* n);

    void _ADD16(uint16_t* r, uint16_t n);

	void i_0x0(uint16_t args);
	void i_0x1(uint16_t args);
	void i_0x2(uint16_t args);
	void i_0x3(uint16_t args);
	void i_0x4(uint16_t args);
	void i_0x5(uint16_t args);
	void i_0x6(uint16_t args);
	void i_0x7(uint16_t args);
	void i_0x8(uint16_t args);
	void i_0x9(uint16_t args);
	void i_0xa(uint16_t args);
	void i_0xb(uint16_t args);
	void i_0xc(uint16_t args);
	void i_0xd(uint16_t args);
	void i_0xe(uint16_t args);
	void i_0xf(uint16_t args);
	void i_0x10(uint16_t args);
	void i_0x11(uint16_t args);
	void i_0x12(uint16_t args);
	void i_0x13(uint16_t args);
	void i_0x14(uint16_t args);
	void i_0x15(uint16_t args);
	void i_0x16(uint16_t args);
	void i_0x17(uint16_t args);
	void i_0x18(uint16_t args);
	void i_0x19(uint16_t args);
	void i_0x1a(uint16_t args);
	void i_0x1b(uint16_t args);
	void i_0x1c(uint16_t args);
	void i_0x1d(uint16_t args);
	void i_0x1e(uint16_t args);
	void i_0x1f(uint16_t args);
	void i_0x20(uint16_t args);
	void i_0x21(uint16_t args);
	void i_0x22(uint16_t args);
	void i_0x23(uint16_t args);
	void i_0x24(uint16_t args);
	void i_0x25(uint16_t args);
	void i_0x26(uint16_t args);
	void i_0x27(uint16_t args);
	void i_0x28(uint16_t args);
	void i_0x29(uint16_t args);
	void i_0x2a(uint16_t args);
	void i_0x2b(uint16_t args);
	void i_0x2c(uint16_t args);
	void i_0x2d(uint16_t args);
	void i_0x2e(uint16_t args);
	void i_0x2f(uint16_t args);
	void i_0x30(uint16_t args);
	void i_0x31(uint16_t args);
	void i_0x32(uint16_t args);
	void i_0x33(uint16_t args);
	void i_0x34(uint16_t args);
	void i_0x35(uint16_t args);
	void i_0x36(uint16_t args);
	void i_0x37(uint16_t args);
	void i_0x38(uint16_t args);
	void i_0x39(uint16_t args);
	void i_0x3a(uint16_t args);
	void i_0x3b(uint16_t args);
	void i_0x3c(uint16_t args);
	void i_0x3d(uint16_t args);
	void i_0x3e(uint16_t args);
	void i_0x3f(uint16_t args);
	void i_0x40(uint16_t args);
	void i_0x41(uint16_t args);
	void i_0x42(uint16_t args);
	void i_0x43(uint16_t args);
	void i_0x44(uint16_t args);
	void i_0x45(uint16_t args);
	void i_0x46(uint16_t args);
	void i_0x47(uint16_t args);
	void i_0x48(uint16_t args);
	void i_0x49(uint16_t args);
	void i_0x4a(uint16_t args);
	void i_0x4b(uint16_t args);
	void i_0x4c(uint16_t args);
	void i_0x4d(uint16_t args);
	void i_0x4e(uint16_t args);
	void i_0x4f(uint16_t args);
	void i_0x50(uint16_t args);
	void i_0x51(uint16_t args);
	void i_0x52(uint16_t args);
	void i_0x53(uint16_t args);
	void i_0x54(uint16_t args);
	void i_0x55(uint16_t args);
	void i_0x56(uint16_t args);
	void i_0x57(uint16_t args);
	void i_0x58(uint16_t args);
	void i_0x59(uint16_t args);
	void i_0x5a(uint16_t args);
	void i_0x5b(uint16_t args);
	void i_0x5c(uint16_t args);
	void i_0x5d(uint16_t args);
	void i_0x5e(uint16_t args);
	void i_0x5f(uint16_t args);
	void i_0x60(uint16_t args);
	void i_0x61(uint16_t args);
	void i_0x62(uint16_t args);
	void i_0x63(uint16_t args);
	void i_0x64(uint16_t args);
	void i_0x65(uint16_t args);
	void i_0x66(uint16_t args);
	void i_0x67(uint16_t args);
	void i_0x68(uint16_t args);
	void i_0x69(uint16_t args);
	void i_0x6a(uint16_t args);
	void i_0x6b(uint16_t args);
	void i_0x6c(uint16_t args);
	void i_0x6d(uint16_t args);
	void i_0x6e(uint16_t args);
	void i_0x6f(uint16_t args);
	void i_0x70(uint16_t args);
	void i_0x71(uint16_t args);
	void i_0x72(uint16_t args);
	void i_0x73(uint16_t args);
	void i_0x74(uint16_t args);
	void i_0x75(uint16_t args);
	void i_0x76(uint16_t args);
	void i_0x77(uint16_t args);
	void i_0x78(uint16_t args);
	void i_0x79(uint16_t args);
	void i_0x7a(uint16_t args);
	void i_0x7b(uint16_t args);
	void i_0x7c(uint16_t args);
	void i_0x7d(uint16_t args);
	void i_0x7e(uint16_t args);
	void i_0x7f(uint16_t args);
	void i_0x80(uint16_t args);
	void i_0x81(uint16_t args);
	void i_0x82(uint16_t args);
	void i_0x83(uint16_t args);
	void i_0x84(uint16_t args);
	void i_0x85(uint16_t args);
	void i_0x86(uint16_t args);
	void i_0x87(uint16_t args);
	void i_0x88(uint16_t args);
	void i_0x89(uint16_t args);
	void i_0x8a(uint16_t args);
	void i_0x8b(uint16_t args);
	void i_0x8c(uint16_t args);
	void i_0x8d(uint16_t args);
	void i_0x8e(uint16_t args);
	void i_0x8f(uint16_t args);
	void i_0x90(uint16_t args);
	void i_0x91(uint16_t args);
	void i_0x92(uint16_t args);
	void i_0x93(uint16_t args);
	void i_0x94(uint16_t args);
	void i_0x95(uint16_t args);
	void i_0x96(uint16_t args);
	void i_0x97(uint16_t args);
	void i_0x98(uint16_t args);
	void i_0x99(uint16_t args);
	void i_0x9a(uint16_t args);
	void i_0x9b(uint16_t args);
	void i_0x9c(uint16_t args);
	void i_0x9d(uint16_t args);
	void i_0x9e(uint16_t args);
	void i_0x9f(uint16_t args);
	void i_0xa0(uint16_t args);
	void i_0xa1(uint16_t args);
	void i_0xa2(uint16_t args);
	void i_0xa3(uint16_t args);
	void i_0xa4(uint16_t args);
	void i_0xa5(uint16_t args);
	void i_0xa6(uint16_t args);
	void i_0xa7(uint16_t args);
	void i_0xa8(uint16_t args);
	void i_0xa9(uint16_t args);
	void i_0xaa(uint16_t args);
	void i_0xab(uint16_t args);
	void i_0xac(uint16_t args);
	void i_0xad(uint16_t args);
	void i_0xae(uint16_t args);
	void i_0xaf(uint16_t args);
	void i_0xb0(uint16_t args);
	void i_0xb1(uint16_t args);
	void i_0xb2(uint16_t args);
	void i_0xb3(uint16_t args);
	void i_0xb4(uint16_t args);
	void i_0xb5(uint16_t args);
	void i_0xb6(uint16_t args);
	void i_0xb7(uint16_t args);
	void i_0xb8(uint16_t args);
	void i_0xb9(uint16_t args);
	void i_0xba(uint16_t args);
	void i_0xbb(uint16_t args);
	void i_0xbc(uint16_t args);
	void i_0xbd(uint16_t args);
	void i_0xbe(uint16_t args);
	void i_0xbf(uint16_t args);
	void i_0xc0(uint16_t args);
	void i_0xc1(uint16_t args);
	void i_0xc2(uint16_t args);
	void i_0xc3(uint16_t args);
	void i_0xc4(uint16_t args);
	void i_0xc5(uint16_t args);
	void i_0xc6(uint16_t args);
	void i_0xc7(uint16_t args);
	void i_0xc8(uint16_t args);
	void i_0xc9(uint16_t args);
	void i_0xca(uint16_t args);
	void i_0xcb(uint16_t args);
	void i_0xcc(uint16_t args);
	void i_0xcd(uint16_t args);
	void i_0xce(uint16_t args);
	void i_0xcf(uint16_t args);
	void i_0xd0(uint16_t args);
	void i_0xd1(uint16_t args);
	void i_0xd2(uint16_t args);
	void i_0xd3(uint16_t args);
	void i_0xd4(uint16_t args);
	void i_0xd5(uint16_t args);
	void i_0xd6(uint16_t args);
	void i_0xd7(uint16_t args);
	void i_0xd8(uint16_t args);
	void i_0xd9(uint16_t args);
	void i_0xda(uint16_t args);
	void i_0xdb(uint16_t args);
	void i_0xdc(uint16_t args);
	void i_0xdd(uint16_t args);
	void i_0xde(uint16_t args);
	void i_0xdf(uint16_t args);
	void i_0xe0(uint16_t args);
	void i_0xe1(uint16_t args);
	void i_0xe2(uint16_t args);
	void i_0xe3(uint16_t args);
	void i_0xe4(uint16_t args);
	void i_0xe5(uint16_t args);
	void i_0xe6(uint16_t args);
	void i_0xe7(uint16_t args);
	void i_0xe8(uint16_t args);
	void i_0xe9(uint16_t args);
	void i_0xea(uint16_t args);
	void i_0xeb(uint16_t args);
	void i_0xec(uint16_t args);
	void i_0xed(uint16_t args);
	void i_0xee(uint16_t args);
	void i_0xef(uint16_t args);
	void i_0xf0(uint16_t args);
	void i_0xf1(uint16_t args);
	void i_0xf2(uint16_t args);
	void i_0xf3(uint16_t args);
	void i_0xf4(uint16_t args);
	void i_0xf5(uint16_t args);
	void i_0xf6(uint16_t args);
	void i_0xf7(uint16_t args);
	void i_0xf8(uint16_t args);
	void i_0xf9(uint16_t args);
	void i_0xfa(uint16_t args);
	void i_0xfb(uint16_t args);
	void i_0xfc(uint16_t args);
	void i_0xfd(uint16_t args);
	void i_0xfe(uint16_t args);
	void i_0xff(uint16_t args);


    inst_t  insts[256]={
		{0x0, "NOP ",4,0,1, 			&i_0x0},
		{0x1, "LD BC, $%4x",12,0,3, 	      &i_0x1},
		{0x2, "LD (BC), A",8,0,1, 		&i_0x2},
		{0x3, "INC BC",8,0,1, 			&i_0x3},
		{0x4, "INC B",4,0,1, 			&i_0x4},
		{0x5, "DEC B",4,0,1, 			&i_0x5},
		{0x6, "LD B, $%2x",8,0,2, 		&i_0x6},
		{0x7, "RLCA ",4,0,1, 			&i_0x7},
		{0x8, "LD (%4x), SP",20,0,3,  	&i_0x8},
		{0x9, "ADD HL, BC",8,0,1, 		&i_0x9},
		{0xa, "LD A, (BC)",8,0,1, 		&i_0xa},
		{0xb, "DEC BC",8,0,1, 			&i_0xb},
		{0xc, "INC C",4,0,1, 			&i_0xc},
		{0xd, "DEC C",4,0,1, 			&i_0xd},
		{0xe, "LD C, $%2x",8,0,2, 		&i_0xe},
		{0xf, "RRCA ",4,0,1, 			&i_0xf},
		{0x10, "STOP 0",4,0,1, 			&i_0x10},
		{0x11, "LD DE, $%4x",12,0,3,  	&i_0x11},
		{0x12, "LD (DE), A",8,0,1, 		&i_0x12},
		{0x13, "INC DE",8,0,1, 			&i_0x13},
		{0x14, "INC D",4,0,1, 			&i_0x14},
		{0x15, "DEC D",4,0,1, 			&i_0x15},
		{0x16, "LD D, $%2x",8,0,2, 		&i_0x16},
		{0x17, "RLA ",4,0,1, 			&i_0x17},
		{0x18, "JR <%2x>",12,0,2, 		&i_0x18},
		{0x19, "ADD HL, DE",8,0,1, 		&i_0x19},
		{0x1a, "LD A, (DE)",8,0,1, 		&i_0x1a},
		{0x1b, "DEC DE",8,0,1, 			&i_0x1b},
		{0x1c, "INC E",4,0,1, 			&i_0x1c},
		{0x1d, "DEC E",4,0,1, 			&i_0x1d},
		{0x1e, "LD E, $%2x",8,0,2, 		&i_0x1e},
		{0x1f, "RRA ",4,0,1, 			&i_0x1f},
		{0x20, "JR NZ, <%2x>",12,8,2, 	&i_0x20},
		{0x21, "LD HL, $%4x",12,0,3, 	      &i_0x21},
		{0x22, "LD (HL+), A",8,0,1, 	      &i_0x22},
		{0x23, "INC HL",8,0,1, 			&i_0x23},
		{0x24, "INC H",4,0,1, 			&i_0x24},
		{0x25, "DEC H",4,0,1, 			&i_0x25},
		{0x26, "LD H, $%2x",8,0,2, 		&i_0x26},
		{0x27, "DAA ",4,0,1, 			&i_0x27},
		{0x28, "JR Z, <%2x>",12,8,2, 	      &i_0x28},
		{0x29, "ADD HL, HL",8,0,1, 		&i_0x29},
		{0x2a, "LD A, (HL+)",8,0,1, 	      &i_0x2a},
		{0x2b, "DEC HL",8,0,1, 			&i_0x2b},
		{0x2c, "INC L",4,0,1, 			&i_0x2c},
		{0x2d, "DEC L",4,0,1, 			&i_0x2d},
		{0x2e, "LD L, $%2x",8,0,2, 		&i_0x2e},
		{0x2f, "CPL ",4,0,1, 			&i_0x2f},
		{0x30, "JR NC, <%2x>",12,8,2, 	&i_0x30},
		{0x31, "LD SP, $%4x",12,0,3, 	      &i_0x31},
		{0x32, "LD (HL-), A",8,0,1, 	      &i_0x32},
		{0x33, "INC SP",8,0,1, 			&i_0x33},
		{0x34, "INC (HL)",12,0,1, 		&i_0x34},
		{0x35, "DEC (HL)",12,0,1, 		&i_0x35},
		{0x36, "LD (HL), $%2x",12,0,2, 	&i_0x36},
		{0x37, "SCF ",4,0,1, 			&i_0x37},
		{0x38, "JR C, <%2x>",12,8,2, 	      &i_0x38},
		{0x39, "ADD HL, SP",8,0,1, 		&i_0x39},
		{0x3a, "LD A, (HL-)",8,0,1, 	      &i_0x3a},
		{0x3b, "DEC SP",8,0,1, 			&i_0x3b},
		{0x3c, "INC A",4,0,1, 			&i_0x3c},
		{0x3d, "DEC A",4,0,1, 			&i_0x3d},
		{0x3e, "LD A, $%2x",8,0,2, 		&i_0x3e},
		{0x3f, "CCF ",4,0,1, 			&i_0x3f},
		{0x41, "LD B, C",4,0,1, 		&i_0x41},
		{0x40, "LD B, B",4,0,1, 		&i_0x40},
		{0x42, "LD B, D",4,0,1, 		&i_0x42},
		{0x43, "LD B, E",4,0,1, 		&i_0x43},
		{0x44, "LD B, H",4,0,1, 		&i_0x44},
		{0x45, "LD B, L",4,0,1, 		&i_0x45},
		{0x46, "LD B, (HL)",8,0,1, 		&i_0x46},
		{0x47, "LD B, A",4,0,1, 		&i_0x47},
		{0x48, "LD C, B",4,0,1, 		&i_0x48},
		{0x49, "LD C, C",4,0,1, 		&i_0x49},
		{0x4a, "LD C, D",4,0,1, 		&i_0x4a},
		{0x4b, "LD C, E",4,0,1, 		&i_0x4b},
		{0x4c, "LD C, H",4,0,1, 		&i_0x4c},
		{0x4d, "LD C, L",4,0,1, 		&i_0x4d},
		{0x4e, "LD C, (HL)",8,0,1, 		&i_0x4e},
		{0x4f, "LD C, A",4,0,1, 		&i_0x4f},
		{0x50, "LD D, B",4,0,1, 		&i_0x50},
		{0x51, "LD D, C",4,0,1, 		&i_0x51},
		{0x52, "LD D, D",4,0,1, 		&i_0x52},
		{0x53, "LD D, E",4,0,1, 		&i_0x53},
		{0x54, "LD D, H",4,0,1, 		&i_0x54},
		{0x55, "LD D, L",4,0,1, 		&i_0x55},
		{0x56, "LD D, (HL)",8,0,1, 		&i_0x56},
		{0x57, "LD D, A",4,0,1, 		&i_0x57},
		{0x58, "LD E, B",4,0,1, 		&i_0x58},
		{0x59, "LD E, C",4,0,1, 		&i_0x59},
		{0x5a, "LD E, D",4,0,1, 		&i_0x5a},
		{0x5b, "LD E, E",4,0,1, 		&i_0x5b},
		{0x5c, "LD E, H",4,0,1, 		&i_0x5c},
		{0x5d, "LD E, L",4,0,1, 		&i_0x5d},
		{0x5e, "LD E, (HL)",8,0,1, 		&i_0x5e},
		{0x5f, "LD E, A",4,0,1, 		&i_0x5f},
		{0x60, "LD H, B",4,0,1, 		&i_0x60},
		{0x61, "LD H, C",4,0,1, 		&i_0x61},
		{0x62, "LD H, D",4,0,1, 		&i_0x62},
		{0x63, "LD H, E",4,0,1, 		&i_0x63},
		{0x64, "LD H, H",4,0,1, 		&i_0x64},
		{0x65, "LD H, L",4,0,1, 		&i_0x65},
		{0x66, "LD H, (HL)",8,0,1, 		&i_0x66},
		{0x67, "LD H, A",4,0,1, 		&i_0x67},
		{0x68, "LD L, B",4,0,1, 		&i_0x68},
		{0x69, "LD L, C",4,0,1, 		&i_0x69},
		{0x6a, "LD L, D",4,0,1, 		&i_0x6a},
		{0x6b, "LD L, E",4,0,1, 		&i_0x6b},
		{0x6c, "LD L, H",4,0,1, 		&i_0x6c},
		{0x6d, "LD L, L",4,0,1, 		&i_0x6d},
		{0x6e, "LD L, (HL)",8,0,1, 		&i_0x6e},
		{0x6f, "LD L, A",4,0,1, 		&i_0x6f},
		{0x70, "LD (HL), B",8,0,1, 		&i_0x70},
		{0x71, "LD (HL), C",8,0,1, 		&i_0x71},
		{0x72, "LD (HL), D",8,0,1, 		&i_0x72},
		{0x73, "LD (HL), E",8,0,1, 		&i_0x73},
		{0x74, "LD (HL), H",8,0,1, 		&i_0x74},
		{0x75, "LD (HL), L",8,0,1, 		&i_0x75},
		{0x76, "HALT ",4,0,1, 			&i_0x76},
		{0x77, "LD (HL), A",8,0,1, 		&i_0x77},
		{0x78, "LD A, B",4,0,1, 		&i_0x78},
		{0x79, "LD A, C",4,0,1,             &i_0x79},
		{0x7a, "LD A, D",4,0,1,             &i_0x7a},
		{0x7b, "LD A, E",4,0,1,             &i_0x7b},
		{0x7c, "LD A, H",4,0,1,             &i_0x7c},
		{0x7d, "LD A, L",4,0,1,             &i_0x7d},
		{0x7e, "LD A, (HL)",8,0,1,          &i_0x7e},
		{0x7f, "LD A, A",4,0,1,             &i_0x7f},
		{0x80, "ADD A, B",4,0,1,            &i_0x80},
		{0x81, "ADD A, C",4,0,1,            &i_0x81},
		{0x82, "ADD A, D",4,0,1,            &i_0x82},
		{0x83, "ADD A, E",4,0,1,            &i_0x83},
		{0x84, "ADD A, H",4,0,1,            &i_0x84},
		{0x85, "ADD A, L",4,0,1,            &i_0x85},
		{0x86, "ADD A, (HL)",8,0,1,         &i_0x86},
		{0x87, "ADD A, A",4,0,1,            &i_0x87},
		{0x88, "ADC A, B",4,0,1,            &i_0x88},
		{0x89, "ADC A, C",4,0,1,            &i_0x89},
		{0x8a, "ADC A, D",4,0,1,            &i_0x8a},
		{0x8b, "ADC A, E",4,0,1,            &i_0x8b},
		{0x8c, "ADC A, H",4,0,1,            &i_0x8c},
		{0x8d, "ADC A, L",4,0,1,            &i_0x8d},
		{0x8e, "ADC A, (HL)",8,0,1,         &i_0x8e},
		{0x8f, "ADC A, A",4,0,1,            &i_0x8f},
		{0x90, "SUB B",4,0,1,               &i_0x90},
		{0x91, "SUB C",4,0,1,               &i_0x91},
		{0x92, "SUB D",4,0,1,               &i_0x92},
		{0x93, "SUB E",4,0,1,               &i_0x93},
		{0x94, "SUB H",4,0,1,               &i_0x94},
		{0x95, "SUB L",4,0,1,               &i_0x95},
		{0x96, "SUB (HL)",8,0,1,            &i_0x96},
		{0x97, "SUB A",4,0,1,               &i_0x97},
		{0x98, "SBC A, B",4,0,1,            &i_0x98},
		{0x99, "SBC A, C",4,0,1,            &i_0x99},
		{0x9a, "SBC A, D",4,0,1,            &i_0x9a},
		{0x9b, "SBC A, E",4,0,1,            &i_0x9b},
		{0x9c, "SBC A, H",4,0,1,            &i_0x9c},
		{0x9d, "SBC A, L",4,0,1,            &i_0x9d},
		{0x9e, "SBC A, (HL)",8,0,1,         &i_0x9e},
		{0x9f, "SBC A, A",4,0,1,            &i_0x9f},
		{0xa0, "AND B",4,0,1,               &i_0xa0},
		{0xa1, "AND C",4,0,1,               &i_0xa1},
		{0xa2, "AND D",4,0,1,               &i_0xa2},
		{0xa3, "AND E",4,0,1,               &i_0xa3},
		{0xa4, "AND H",4,0,1,               &i_0xa4},
		{0xa5, "AND L",4,0,1,               &i_0xa5},
		{0xa6, "AND (HL)",8,0,1,            &i_0xa6},
		{0xa7, "AND A",4,0,1,               &i_0xa7},
		{0xa8, "XOR B",4,0,1,               &i_0xa8},
		{0xa9, "XOR C",4,0,1,               &i_0xa9},
		{0xaa, "XOR D",4,0,1,               &i_0xaa},
		{0xab, "XOR E",4,0,1,               &i_0xab},
		{0xac, "XOR H",4,0,1,               &i_0xac},
		{0xad, "XOR L",4,0,1,               &i_0xad},
		{0xae, "XOR (HL)",8,0,1,            &i_0xae},
		{0xaf, "XOR A",4,0,1,               &i_0xaf},
		{0xb0, "OR B",4,0,1,                &i_0xb0},
		{0xb1, "OR C",4,0,1,                &i_0xb1},
		{0xb2, "OR D",4,0,1,                &i_0xb2},
		{0xb3, "OR E",4,0,1,                &i_0xb3},
		{0xb4, "OR H",4,0,1,                &i_0xb4},
		{0xb5, "OR L",4,0,1,                &i_0xb5},
		{0xb6, "OR (HL)",8,0,1,             &i_0xb6},
		{0xb7, "OR A",4,0,1,                &i_0xb7},
		{0xb8, "CP B",4,0,1,                &i_0xb8},
		{0xb9, "CP C",4,0,1,                &i_0xb9},
		{0xba, "CP D",4,0,1,                &i_0xba},
		{0xbb, "CP E",4,0,1,                &i_0xbb},
		{0xbc, "CP H",4,0,1,                &i_0xbc},
		{0xbd, "CP L",4,0,1,                &i_0xbd},
		{0xbe, "CP (HL)",8,0,1,             &i_0xbe},
		{0xbf, "CP A",4,0,1,                &i_0xbf},
		{0xc0, "RET NZ",20,8,1,             &i_0xc0},
		{0xc1, "POP BC",12,0,1,             &i_0xc1},
		{0xc2, "JP NZ, (%4x)",16,12,3,      &i_0xc2},
		{0xc3, "JP (%4x)",16,0,3,           &i_0xc3},
		{0xc4, "CALL NZ, (%4x)",24,12,3,    &i_0xc4},
		{0xc5, "PUSH BC",16,0,1,            &i_0xc5},
		{0xc6, "ADD A, $%2x",8,0,2,         &i_0xc6},
		{0xc7, "RST 00H",16,0,1,            &i_0xc7},
		{0xc8, "RET Z",20,8,1,              &i_0xc8},
		{0xc9, "RET ",16,0,1,               &i_0xc9},
		{0xca, "JP Z, (%4x)",16,12,3,       &i_0xca},
		{0xcb, "PREFIX CB",4,0,1,           &i_0xcb},
		{0xcc, "CALL Z, (%4x)",24,12,3,     &i_0xcc},
		{0xcd, "CALL (%4x)",24,0,3,         &i_0xcd},
		{0xce, "ADC A, $%2x",8,0,2,         &i_0xce},
		{0xcf, "RST 08H",16,0,1,            &i_0xcf},
		{0xd0, "RET NC",20,8,1,             &i_0xd0},
		{0xd1, "POP DE",12,0,1,             &i_0xd1},
		{0xd2, "JP NC, (%4x)",16,12,3,      &i_0xd2},
		{0xd3, "",0,0,0,                    &i_0xd3},
		{0xd4, "CALL NC, (%4x)",24,12,3,    &i_0xd4},
		{0xd5, "PUSH DE",16,0,1,            &i_0xd5},
		{0xd6, "SUB $%2x",8,0,2,            &i_0xd6},
		{0xd7, "RST 10H",16,0,1,            &i_0xd7},
		{0xd8, "RET C",20,8,1,              &i_0xd8},
		{0xd9, "RETI ",16,0,1,              &i_0xd9},
		{0xda, "JP C, (%4x)",16,12,3,       &i_0xda},
		{0xdb, "",0,0,0,                    &i_0xdb},
		{0xdc, "CALL C, (%4x)",24,12,3,     &i_0xdc},
		{0xdd, "",0,0,0,                    &i_0xdd},
		{0xde, "SBC A, $%2x",8,0,2,         &i_0xde},
		{0xdf, "RST 18H",16,0,1,            &i_0xdf},
		{0xe0, "LDH (%2x), A",12,0,2,       &i_0xe0},
		{0xe1, "POP HL",12,0,1,             &i_0xe1},
		{0xe2, "LD (C), A",8,0,1,           &i_0xe2},
		{0xe3, "",0,0,0,                    &i_0xe3},
		{0xe4, "",0,0,0,                    &i_0xe4},
		{0xe5, "PUSH HL",16,0,1,            &i_0xe5},
		{0xe6, "AND $%2x",8,0,2,            &i_0xe6},
		{0xe7, "RST 20H",16,0,1,            &i_0xe7},
		{0xe8, "ADD SP, <%2x>",16,0,2,      &i_0xe8},
		{0xe9, "JP (HL)",4,0,1,             &i_0xe9},
		{0xea, "LD (%4x), A",16,0,3,        &i_0xea},
		{0xeb, "",0,0,0,                    &i_0xeb},
		{0xec, "",0,0,0,                    &i_0xec},
		{0xed, "",0,0,0,                    &i_0xed},
		{0xee, "XOR $%2x",8,0,2,            &i_0xee},
		{0xef, "RST 28H",16,0,1,            &i_0xef},
		{0xf0, "LDH A, (%2x)",12,0,2,       &i_0xf0},
		{0xf1, "POP AF",12,0,1,             &i_0xf1},
		{0xf2, "LD A, (C)",8,0,1,           &i_0xf2},
		{0xf3, "DI ",4,0,1,                 &i_0xf3},
		{0xf4, "",0,0,0,                    &i_0xf4},
		{0xf5, "PUSH AF",16,0,1,            &i_0xf5},
		{0xf6, "OR $%2x",8,0,2,             &i_0xf6},
		{0xf7, "RST 30H",16,0,1,            &i_0xf7},
		{0xf8, "LD HL, SP+r8",12,0,2,       &i_0xf8},
		{0xf9, "LD SP, HL",8,0,1,           &i_0xf9},
		{0xfa, "LD A, (%4x)",16,0,3,        &i_0xfa},
		{0xfb, "EI ",4,0,1,                 &i_0xfb},
		{0xfc, "",0,0,0,                    &i_0xfc},
		{0xfd, "",0,0,0,                    &i_0xfd},
		{0xfe, "CP $%2x",8,0,2,             &i_0xfe},
		{0xff, "RST 38H",16,0,1,            &i_0xff},
    };
    inst_t  CB_insts[256]={
	    {0x0, "RLC B",8,0,2, NULL}, 
		{0x1, "RLC C",8,0,2, NULL}, 
		{0x2, "RLC D",8,0,2, NULL}, 
		{0x3, "RLC E",8,0,2, NULL}, 
		{0x4, "RLC H",8,0,2, NULL}, 
		{0x5, "RLC L",8,0,2, NULL}, 
		{0x6, "RLC (HL)",16,0,2, NULL}, 
		{0x7, "RLC A",8,0,2, NULL}, 
		{0x8, "RRC B",8,0,2, NULL}, 
		{0x9, "RRC C",8,0,2, NULL}, 
		{0xa, "RRC D",8,0,2, NULL}, 
		{0xb, "RRC E",8,0,2, NULL}, 
		{0xc, "RRC H",8,0,2, NULL}, 
		{0xd, "RRC L",8,0,2, NULL}, 
		{0xe, "RRC (HL)",16,0,2, NULL}, 
		{0xf, "RRC A",8,0,2, NULL}, 
		{0x10, "RL B",8,0,2, NULL}, 
		{0x11, "RL C",8,0,2, NULL}, 
		{0x12, "RL D",8,0,2, NULL}, 
		{0x13, "RL E",8,0,2, NULL}, 
		{0x14, "RL H",8,0,2, NULL}, 
		{0x15, "RL L",8,0,2, NULL}, 
		{0x16, "RL (HL)",16,0,2, NULL}, 
		{0x17, "RL A",8,0,2, NULL}, 
		{0x18, "RR B",8,0,2, NULL}, 
		{0x19, "RR C",8,0,2, NULL}, 
		{0x1a, "RR D",8,0,2, NULL}, 
		{0x1b, "RR E",8,0,2, NULL}, 
		{0x1c, "RR H",8,0,2, NULL}, 
		{0x1d, "RR L",8,0,2, NULL}, 
		{0x1e, "RR (HL)",16,0,2, NULL}, 
		{0x1f, "RR A",8,0,2, NULL}, 
		{0x20, "SLA B",8,0,2, NULL}, 
		{0x21, "SLA C",8,0,2, NULL}, 
		{0x22, "SLA D",8,0,2, NULL}, 
		{0x23, "SLA E",8,0,2, NULL}, 
		{0x24, "SLA H",8,0,2, NULL}, 
		{0x25, "SLA L",8,0,2, NULL}, 
		{0x26, "SLA (HL)",16,0,2, NULL}, 
		{0x27, "SLA A",8,0,2, NULL}, 
		{0x28, "SRA B",8,0,2, NULL}, 
		{0x29, "SRA C",8,0,2, NULL}, 
		{0x2a, "SRA D",8,0,2, NULL}, 
		{0x2b, "SRA E",8,0,2, NULL}, 
		{0x2c, "SRA H",8,0,2, NULL}, 
		{0x2d, "SRA L",8,0,2, NULL}, 
		{0x2e, "SRA (HL)",16,0,2, NULL}, 
		{0x2f, "SRA A",8,0,2, NULL}, 
		{0x30, "SWAP B",8,0,2, NULL}, 
		{0x31, "SWAP C",8,0,2, NULL}, 
		{0x32, "SWAP D",8,0,2, NULL}, 
		{0x33, "SWAP E",8,0,2, NULL}, 
		{0x34, "SWAP H",8,0,2, NULL}, 
		{0x35, "SWAP L",8,0,2, NULL}, 
		{0x36, "SWAP (HL)",16,0,2, NULL}, 
		{0x37, "SWAP A",8,0,2, NULL}, 
		{0x38, "SRL B",8,0,2, NULL}, 
		{0x39, "SRL C",8,0,2, NULL}, 
		{0x3a, "SRL D",8,0,2, NULL}, 
		{0x3b, "SRL E",8,0,2, NULL}, 
		{0x3c, "SRL H",8,0,2, NULL}, 
		{0x3d, "SRL L",8,0,2, NULL}, 
		{0x3e, "SRL (HL)",16,0,2, NULL}, 
		{0x3f, "SRL A",8,0,2, NULL}, 
		{0x40, "BIT 0, B",8,0,2, NULL}, 
		{0x41, "BIT 0, C",8,0,2, NULL}, 
		{0x42, "BIT 0, D",8,0,2, NULL}, 
		{0x43, "BIT 0, E",8,0,2, NULL}, 
		{0x44, "BIT 0, H",8,0,2, NULL}, 
		{0x45, "BIT 0, L",8,0,2, NULL}, 
		{0x46, "BIT 0, (HL)",16,0,2, NULL}, 
		{0x47, "BIT 0, A",8,0,2, NULL}, 
		{0x48, "BIT 1, B",8,0,2, NULL}, 
		{0x49, "BIT 1, C",8,0,2, NULL}, 
		{0x4a, "BIT 1, D",8,0,2, NULL}, 
		{0x4b, "BIT 1, E",8,0,2, NULL}, 
		{0x4c, "BIT 1, H",8,0,2, NULL}, 
		{0x4d, "BIT 1, L",8,0,2, NULL}, 
		{0x4e, "BIT 1, (HL)",16,0,2, NULL}, 
		{0x4f, "BIT 1, A",8,0,2, NULL}, 
		{0x50, "BIT 2, B",8,0,2, NULL}, 
		{0x51, "BIT 2, C",8,0,2, NULL}, 
		{0x52, "BIT 2, D",8,0,2, NULL}, 
		{0x53, "BIT 2, E",8,0,2, NULL}, 
		{0x54, "BIT 2, H",8,0,2, NULL}, 
		{0x55, "BIT 2, L",8,0,2, NULL}, 
		{0x56, "BIT 2, (HL)",16,0,2, NULL}, 
		{0x57, "BIT 2, A",8,0,2, NULL}, 
		{0x58, "BIT 3, B",8,0,2, NULL}, 
		{0x59, "BIT 3, C",8,0,2, NULL}, 
		{0x5a, "BIT 3, D",8,0,2, NULL}, 
		{0x5b, "BIT 3, E",8,0,2, NULL}, 
		{0x5c, "BIT 3, H",8,0,2, NULL}, 
		{0x5d, "BIT 3, L",8,0,2, NULL}, 
		{0x5e, "BIT 3, (HL)",16,0,2, NULL}, 
		{0x5f, "BIT 3, A",8,0,2, NULL}, 
		{0x60, "BIT 4, B",8,0,2, NULL}, 
		{0x61, "BIT 4, C",8,0,2, NULL}, 
		{0x62, "BIT 4, D",8,0,2, NULL}, 
		{0x63, "BIT 4, E",8,0,2, NULL}, 
		{0x64, "BIT 4, H",8,0,2, NULL}, 
		{0x65, "BIT 4, L",8,0,2, NULL}, 
		{0x66, "BIT 4, (HL)",16,0,2, NULL}, 
		{0x67, "BIT 4, A",8,0,2, NULL}, 
		{0x68, "BIT 5, B",8,0,2, NULL}, 
		{0x69, "BIT 5, C",8,0,2, NULL}, 
		{0x6a, "BIT 5, D",8,0,2, NULL}, 
		{0x6b, "BIT 5, E",8,0,2, NULL}, 
		{0x6c, "BIT 5, H",8,0,2, NULL}, 
		{0x6d, "BIT 5, L",8,0,2, NULL}, 
		{0x6e, "BIT 5, (HL)",16,0,2, NULL}, 
		{0x6f, "BIT 5, A",8,0,2, NULL}, 
		{0x70, "BIT 6, B",8,0,2, NULL}, 
		{0x71, "BIT 6, C",8,0,2, NULL}, 
		{0x72, "BIT 6, D",8,0,2, NULL}, 
		{0x73, "BIT 6, E",8,0,2, NULL}, 
		{0x74, "BIT 6, H",8,0,2, NULL}, 
		{0x75, "BIT 6, L",8,0,2, NULL}, 
		{0x76, "BIT 6, (HL)",16,0,2, NULL}, 
		{0x77, "BIT 6, A",8,0,2, NULL}, 
		{0x78, "BIT 7, B",8,0,2, NULL}, 
		{0x79, "BIT 7, C",8,0,2, NULL}, 
		{0x7a, "BIT 7, D",8,0,2, NULL}, 
		{0x7b, "BIT 7, E",8,0,2, NULL}, 
		{0x7c, "BIT 7, H",8,0,2, NULL}, 
		{0x7d, "BIT 7, L",8,0,2, NULL}, 
		{0x7e, "BIT 7, (HL)",16,0,2, NULL}, 
		{0x7f, "BIT 7, A",8,0,2, NULL}, 
		{0x80, "RES 0, B",8,0,2, NULL}, 
		{0x81, "RES 0, C",8,0,2, NULL}, 
		{0x82, "RES 0, D",8,0,2, NULL}, 
		{0x83, "RES 0, E",8,0,2, NULL}, 
		{0x84, "RES 0, H",8,0,2, NULL}, 
		{0x85, "RES 0, L",8,0,2, NULL}, 
		{0x86, "RES 0, (HL)",16,0,2, NULL}, 
		{0x87, "RES 0, A",8,0,2, NULL}, 
		{0x88, "RES 1, B",8,0,2, NULL}, 
		{0x89, "RES 1, C",8,0,2, NULL}, 
		{0x8a, "RES 1, D",8,0,2, NULL}, 
		{0x8b, "RES 1, E",8,0,2, NULL}, 
		{0x8c, "RES 1, H",8,0,2, NULL}, 
		{0x8d, "RES 1, L",8,0,2, NULL}, 
		{0x8e, "RES 1, (HL)",16,0,2, NULL}, 
		{0x8f, "RES 1, A",8,0,2, NULL}, 
		{0x90, "RES 2, B",8,0,2, NULL}, 
		{0x91, "RES 2, C",8,0,2, NULL}, 
		{0x92, "RES 2, D",8,0,2, NULL}, 
		{0x93, "RES 2, E",8,0,2, NULL}, 
		{0x94, "RES 2, H",8,0,2, NULL}, 
		{0x95, "RES 2, L",8,0,2, NULL}, 
		{0x96, "RES 2, (HL)",16,0,2, NULL}, 
		{0x97, "RES 2, A",8,0,2, NULL}, 
		{0x98, "RES 3, B",8,0,2, NULL}, 
		{0x99, "RES 3, C",8,0,2, NULL}, 
		{0x9a, "RES 3, D",8,0,2, NULL}, 
		{0x9b, "RES 3, E",8,0,2, NULL}, 
		{0x9c, "RES 3, H",8,0,2, NULL}, 
		{0x9d, "RES 3, L",8,0,2, NULL}, 
		{0x9e, "RES 3, (HL)",16,0,2, NULL}, 
		{0x9f, "RES 3, A",8,0,2, NULL}, 
		{0xa0, "RES 4, B",8,0,2, NULL}, 
		{0xa1, "RES 4, C",8,0,2, NULL}, 
		{0xa2, "RES 4, D",8,0,2, NULL}, 
		{0xa3, "RES 4, E",8,0,2, NULL}, 
		{0xa4, "RES 4, H",8,0,2, NULL}, 
		{0xa5, "RES 4, L",8,0,2, NULL}, 
		{0xa6, "RES 4, (HL)",16,0,2, NULL}, 
		{0xa7, "RES 4, A",8,0,2, NULL}, 
		{0xa8, "RES 5, B",8,0,2, NULL}, 
		{0xa9, "RES 5, C",8,0,2, NULL}, 
		{0xaa, "RES 5, D",8,0,2, NULL}, 
		{0xab, "RES 5, E",8,0,2, NULL}, 
		{0xac, "RES 5, H",8,0,2, NULL}, 
		{0xad, "RES 5, L",8,0,2, NULL}, 
		{0xae, "RES 5, (HL)",16,0,2, NULL}, 
		{0xaf, "RES 5, A",8,0,2, NULL}, 
		{0xb0, "RES 6, B",8,0,2, NULL}, 
		{0xb1, "RES 6, C",8,0,2, NULL}, 
		{0xb2, "RES 6, D",8,0,2, NULL}, 
		{0xb3, "RES 6, E",8,0,2, NULL}, 
		{0xb4, "RES 6, H",8,0,2, NULL}, 
		{0xb5, "RES 6, L",8,0,2, NULL}, 
		{0xb6, "RES 6, (HL)",16,0,2, NULL}, 
		{0xb7, "RES 6, A",8,0,2, NULL}, 
		{0xb8, "RES 7, B",8,0,2, NULL}, 
		{0xb9, "RES 7, C",8,0,2, NULL}, 
		{0xba, "RES 7, D",8,0,2, NULL}, 
		{0xbb, "RES 7, E",8,0,2, NULL}, 
		{0xbc, "RES 7, H",8,0,2, NULL}, 
		{0xbd, "RES 7, L",8,0,2, NULL}, 
		{0xbe, "RES 7, (HL)",16,0,2, NULL}, 
		{0xbf, "RES 7, A",8,0,2, NULL}, 
		{0xc0, "SET 0, B",8,0,2, NULL}, 
		{0xc1, "SET 0, C",8,0,2, NULL}, 
		{0xc2, "SET 0, D",8,0,2, NULL}, 
		{0xc3, "SET 0, E",8,0,2, NULL}, 
		{0xc4, "SET 0, H",8,0,2, NULL}, 
		{0xc5, "SET 0, L",8,0,2, NULL}, 
		{0xc6, "SET 0, (HL)",16,0,2, NULL}, 
		{0xc7, "SET 0, A",8,0,2, NULL}, 
		{0xc8, "SET 1, B",8,0,2, NULL}, 
		{0xc9, "SET 1, C",8,0,2, NULL}, 
		{0xca, "SET 1, D",8,0,2, NULL}, 
		{0xcb, "SET 1, E",8,0,2, NULL}, 
		{0xcc, "SET 1, H",8,0,2, NULL}, 
		{0xcd, "SET 1, L",8,0,2, NULL}, 
		{0xce, "SET 1, (HL)",16,0,2, NULL}, 
		{0xcf, "SET 1, A",8,0,2, NULL}, 
		{0xd0, "SET 2, B",8,0,2, NULL}, 
		{0xd1, "SET 2, C",8,0,2, NULL}, 
		{0xd2, "SET 2, D",8,0,2, NULL}, 
		{0xd3, "SET 2, E",8,0,2, NULL}, 
		{0xd4, "SET 2, H",8,0,2, NULL}, 
		{0xd5, "SET 2, L",8,0,2, NULL}, 
		{0xd6, "SET 2, (HL)",16,0,2, NULL}, 
		{0xd7, "SET 2, A",8,0,2, NULL}, 
		{0xd8, "SET 3, B",8,0,2, NULL}, 
		{0xd9, "SET 3, C",8,0,2, NULL}, 
		{0xda, "SET 3, D",8,0,2, NULL}, 
		{0xdb, "SET 3, E",8,0,2, NULL}, 
		{0xdc, "SET 3, H",8,0,2, NULL}, 
		{0xdd, "SET 3, L",8,0,2, NULL}, 
		{0xde, "SET 3, (HL)",16,0,2, NULL}, 
		{0xdf, "SET 3, A",8,0,2, NULL}, 
		{0xe0, "SET 4, B",8,0,2, NULL}, 
		{0xe1, "SET 4, C",8,0,2, NULL}, 
		{0xe2, "SET 4, D",8,0,2, NULL}, 
		{0xe3, "SET 4, E",8,0,2, NULL}, 
		{0xe4, "SET 4, H",8,0,2, NULL}, 
		{0xe5, "SET 4, L",8,0,2, NULL}, 
		{0xe6, "SET 4, (HL)",16,0,2, NULL}, 
		{0xe7, "SET 4, A",8,0,2, NULL}, 
		{0xe8, "SET 5, B",8,0,2, NULL}, 
		{0xe9, "SET 5, C",8,0,2, NULL}, 
		{0xea, "SET 5, D",8,0,2, NULL}, 
		{0xeb, "SET 5, E",8,0,2, NULL}, 
		{0xec, "SET 5, H",8,0,2, NULL}, 
		{0xed, "SET 5, L",8,0,2, NULL}, 
		{0xee, "SET 5, (HL)",16,0,2, NULL}, 
		{0xef, "SET 5, A",8,0,2, NULL}, 
		{0xf0, "SET 6, B",8,0,2, NULL}, 
		{0xf1, "SET 6, C",8,0,2, NULL}, 
		{0xf2, "SET 6, D",8,0,2, NULL}, 
		{0xf3, "SET 6, E",8,0,2, NULL}, 
		{0xf4, "SET 6, H",8,0,2, NULL}, 
		{0xf5, "SET 6, L",8,0,2, NULL}, 
		{0xf6, "SET 6, (HL)",16,0,2, NULL}, 
		{0xf7, "SET 6, A",8,0,2, NULL}, 
		{0xf8, "SET 7, B",8,0,2, NULL}, 
		{0xf9, "SET 7, C",8,0,2, NULL}, 
		{0xfa, "SET 7, D",8,0,2, NULL}, 
		{0xfb, "SET 7, E",8,0,2, NULL}, 
		{0xfc, "SET 7, H",8,0,2, NULL}, 
		{0xfd, "SET 7, L",8,0,2, NULL}, 
		{0xfe, "SET 7, (HL)",16,0,2, NULL}, 
		{0xff, "SET 7, A",8,0,2, NULL},


    };
    
    public:
    Z80();
    /* Emulates one CPU cycle */
    void cycle();
    ~Z80();
};


