#include "Z80.h"
#include "mem.h"

extern Mem mem;

/* 8-bit load instructions */

void Z80::i_0x2(uint16_t args){
	mem.write(registers.BC, registers.A);
}
void Z80::i_0x6(uint16_t args){
	registers.B = args & 0xFF;
}
void Z80::i_0xa(uint16_t args){
	registers.A = mem.read(registers.BC);
}
void Z80::i_0xe(uint16_t args){
	registers.C = args & 0xFF;
}
void Z80::i_0x12(uint16_t args){
	mem.write(registers.DE, registers.A);
}
void Z80::i_0x16(uint16_t args){
	registers.D = args & 0xFF;
}
void Z80::i_0x1a(uint16_t args){
	registers.A = mem.read(registers.DE);
}
void Z80::i_0x1e(uint16_t args){
	registers.E = args & 0xFF;
}
void Z80::i_0x22(uint16_t args){
	mem.write(registers.HL, registers.A);
	registers.HL++;
}
void Z80::i_0x26(uint16_t args){
	registers.H = args & 0xFF;
}
void Z80::i_0x2a(uint16_t args){
	registers.A = mem.read(registers.HL);
	registers.HL++;
}
void Z80::i_0x2e(uint16_t args){
	registers.L = args & 0xFF;
}
void Z80::i_0x32(uint16_t args){
	mem.write(registers.HL, registers.A);
	registers.HL--;
}
void Z80::i_0x36(uint16_t args){
	mem.write(registers.HL, args&0xFF);
}
void Z80::i_0x3a(uint16_t args){
	registers.A = mem.read(registers.HL);
	registers.HL--;
}
void Z80::i_0x3e(uint16_t args){
	registers.A = args & 0xFF;
}
void Z80::i_0x40(uint16_t args){
	registers.B = registers.B;
}
void Z80::i_0x41(uint16_t args){
	registers.B = registers.C;
}
void Z80::i_0x42(uint16_t args){
	registers.B = registers.D;
}
void Z80::i_0x43(uint16_t args){
	registers.B = registers.E;
}
void Z80::i_0x44(uint16_t args){
	registers.B = registers.H;
}
void Z80::i_0x45(uint16_t args){
	registers.B = registers.L;
}
void Z80::i_0x46(uint16_t args){
	registers.B = mem.read(registers.HL);
}
void Z80::i_0x47(uint16_t args){
	registers.B = registers.A;
}
void Z80::i_0x48(uint16_t args){
	registers.C = registers.B;
}
void Z80::i_0x49(uint16_t args){
	registers.C = registers.C;
}
void Z80::i_0x4a(uint16_t args){
	registers.C = registers.D;
}
void Z80::i_0x4b(uint16_t args){
	registers.C = registers.E;
}
void Z80::i_0x4c(uint16_t args){
	registers.C = registers.H;
}
void Z80::i_0x4d(uint16_t args){
	registers.C = registers.L;
}
void Z80::i_0x4e(uint16_t args){
	registers.C = mem.read(registers.HL);
}
void Z80::i_0x4f(uint16_t args){
	registers.C = registers.A;
}
void Z80::i_0x50(uint16_t args){
	registers.D = registers.B;
}
void Z80::i_0x51(uint16_t args){
	registers.D = registers.C;
}
void Z80::i_0x52(uint16_t args){
	registers.D = registers.D;
}
void Z80::i_0x53(uint16_t args){
	registers.D = registers.E;
}
void Z80::i_0x54(uint16_t args){
	registers.D = registers.H;
}
void Z80::i_0x55(uint16_t args){
	registers.D = registers.L;
}
void Z80::i_0x56(uint16_t args){
	registers.D = mem.read(registers.HL);
}
void Z80::i_0x57(uint16_t args){
	registers.D = registers.A;
}
void Z80::i_0x58(uint16_t args){
	registers.E = registers.B;
}
void Z80::i_0x59(uint16_t args){
	registers.E = registers.C;
}
void Z80::i_0x5a(uint16_t args){
	registers.E = registers.D;
}
void Z80::i_0x5b(uint16_t args){
	registers.E = registers.E;
}
void Z80::i_0x5c(uint16_t args){
	registers.E = registers.H;
}
void Z80::i_0x5d(uint16_t args){
	registers.E = registers.L;
}
void Z80::i_0x5e(uint16_t args){
	registers.E = mem.read(registers.HL);
}
void Z80::i_0x5f(uint16_t args){
	registers.E = registers.A;
}
void Z80::i_0x60(uint16_t args){
	registers.H = registers.B;
}
void Z80::i_0x61(uint16_t args){
	registers.H = registers.C;
}
void Z80::i_0x62(uint16_t args){
	registers.H = registers.D;
}
void Z80::i_0x63(uint16_t args){
	registers.H = registers.E;
}
void Z80::i_0x64(uint16_t args){
	registers.H = registers.H;
}
void Z80::i_0x65(uint16_t args){
	registers.H = registers.L;
}
void Z80::i_0x66(uint16_t args){
	registers.H = mem.read(registers.HL);
}
void Z80::i_0x67(uint16_t args){
	registers.H = registers.A;
}
void Z80::i_0x68(uint16_t args){
	registers.L = registers.B;
}
void Z80::i_0x69(uint16_t args){
	registers.L = registers.C;
}
void Z80::i_0x6a(uint16_t args){
	registers.L = registers.D;
}
void Z80::i_0x6b(uint16_t args){
	registers.L = registers.E;
}
void Z80::i_0x6c(uint16_t args){
	registers.L = registers.H;
}
void Z80::i_0x6d(uint16_t args){
	registers.L = registers.L;
}
void Z80::i_0x6e(uint16_t args){
	registers.L = mem.read(registers.HL);
}
void Z80::i_0x6f(uint16_t args){
	registers.L = registers.A;
}
void Z80::i_0x70(uint16_t args){
	mem.write(registers.HL, registers.B);
}
void Z80::i_0x71(uint16_t args){
	mem.write(registers.HL, registers.C);
}
void Z80::i_0x72(uint16_t args){
	mem.write(registers.HL, registers.D);
}
void Z80::i_0x73(uint16_t args){
	mem.write(registers.HL, registers.E);
}
void Z80::i_0x74(uint16_t args){
	mem.write(registers.HL, registers.H);
}
void Z80::i_0x75(uint16_t args){
	mem.write(registers.HL, registers.L);
}
void Z80::i_0x77(uint16_t args){
	mem.write(registers.HL, registers.A);
}
void Z80::i_0x78(uint16_t args){
	registers.A = registers.B;
}
void Z80::i_0x79(uint16_t args){
	registers.A = registers.C;
}
void Z80::i_0x7a(uint16_t args){
	registers.A = registers.D;
}
void Z80::i_0x7b(uint16_t args){
	registers.A = registers.E;
}
void Z80::i_0x7c(uint16_t args){
	registers.A = registers.H;
}
void Z80::i_0x7d(uint16_t args){
	registers.A = registers.L;
}
void Z80::i_0x7e(uint16_t args){
	registers.A = mem.read(registers.HL);
}
void Z80::i_0x7f(uint16_t args){
	registers.A = registers.A;
}
void Z80::i_0xe0(uint16_t args){
	mem.write(0xFF00 + (args&0xFF),registers.A);
}
void Z80::i_0xe2(uint16_t args){
	mem.write(0xFF00+registers.C, registers.A);
}
void Z80::i_0xea(uint16_t args){
	mem.write((args&0xFFFF), registers.A);
}
void Z80::i_0xf0(uint16_t args){
	registers.A = mem.read(0xFF00 + (args&0xFF));
}
void Z80::i_0xf2(uint16_t args){
	registers.A = mem.read(0xFF00+registers.C);
}
void Z80::i_0xfa(uint16_t args){
	registers.A = args & 0xFFFF;
}

/* 16-bit load instructions */
void Z80::i_0x1(uint16_t args){
	registers.BC = args & 0xFFFF;
}
void Z80::i_0x8(uint16_t args){
	mem.write(args & 0xFFFF, registers.SP & 0x0F);
	mem.write((args+1) & 0xFFFF, registers.SP & 0xF0);
}

void Z80::i_0x11(uint16_t args){
	registers.DE = args & 0xFFFF;
}
void Z80::i_0x21(uint16_t args){
	registers.HL = args & 0xFFFF;
}
void Z80::i_0x31(uint16_t args){
	registers.SP = args & 0xFFFF;
}

void Z80::i_0xf8(uint16_t args){
	uint16_t result = registers.SP + ((int16_t)args & 0xFF);
	bool C = (registers.SP&0xFF) && (((int16_t)args & 0xFF)&0xF00);
	bool H = (((registers.SP&0xf) + (((int16_t)args & 0xFF)&0xf))&0xF0);
	registers.HL = result;
	registers.F &= 0b00111111;
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
}
void Z80::i_0xf9(uint16_t args){
	registers.SP = registers.HL;
}

void Z80::i_0xc5(uint16_t args){
	registers.SP--;
	mem.write(registers.SP--, registers.BC&0xF0);
	mem.write(registers.SP--, registers.BC&0x0F);
}
void Z80::i_0xd5(uint16_t args){
	registers.SP--;
	mem.write(registers.SP--, registers.DE&0xF0);
	mem.write(registers.SP--, registers.DE&0x0F);
}
void Z80::i_0xe5(uint16_t args){
	registers.SP--;
	mem.write(registers.SP--, registers.HL&0xF0);
	mem.write(registers.SP--, registers.HL&0x0F);
}
void Z80::i_0xf5(uint16_t args){
	registers.SP--;
	mem.write(registers.SP--, registers.AF&0xF0);
	mem.write(registers.SP--, registers.AF&0x0F);
}

void Z80::i_0xc1(uint16_t args){
	registers.B = mem.read(registers.SP++);
	registers.C = mem.read(registers.SP++);
}
void Z80::i_0xd1(uint16_t args){
	registers.D = mem.read(registers.SP++);
	registers.E = mem.read(registers.SP++);
}
void Z80::i_0xe1(uint16_t args){
	registers.H = mem.read(registers.SP++);
	registers.L = mem.read(registers.SP++);
}
void Z80::i_0xf1(uint16_t args){
	registers.A = mem.read(registers.SP++);
	registers.F = mem.read(registers.SP++);
}

/* 8-bit arithmetic / logical instructions */

#define carry(a,b) (((a&0x80) && (b&0x80)) == 128)
#define hcarry(a,b) ((((a&0xf) + (b&0xf))&0x10) == 16)

void Z80::_ADD(uint8_t n){
	int8_t result = registers.A + n;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F &= 0b10111111;
	bool C = carry(registers.A, n);
	bool H = hcarry(registers.A, n);
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	registers.A = result;
}
void Z80::_ADC(uint8_t n){
	int8_t result = registers.A + n + ((registers.F & 0x10)>>4);
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F &= 0b10111111;
	bool C = carry(registers.A, n);
	bool H = hcarry(registers.A, n);
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	registers.A = result;
}

void Z80::_SUB(uint8_t n){
	int8_t result = registers.A - n;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F |= 0b01000000;
	bool C = (n > registers.A);
	bool H = ((n&0xF) > (registers.A&0xF));
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	registers.A = result;
}
void Z80::_SDC(uint8_t n){
	int8_t result = registers.A - (n + (registers.F & 0x80)?1:0);
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F |= 0b01000000;
	bool C = ((n + (registers.F & 0x80)?1:0) > registers.A);
	bool H = (((n + (registers.F & 0x80)?1:0)&0xF) > (registers.A&0xF));
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	registers.A = result;
}

void Z80::_AND(uint8_t n){
	int8_t result = registers.A & n;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F &= 0b10101111;
	registers.F |= 0b00100000;
	registers.A = result;
}

void Z80::_OR(uint8_t n){
	int8_t result = registers.A | n;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F &= 0b10001111;
	registers.A = result;
}

void Z80::_XOR(uint8_t n){
	int8_t result = registers.A ^ n;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F &= 0b10001111;
	registers.A = result;
}

void Z80::_CP(uint8_t n){
	int8_t result = registers.A - n;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F |= 0b01000000;
	bool C = (n > registers.A);
	bool H = ((n&0xF) > (registers.A&0xF));
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
}

void Z80::_INC(uint8_t* n){
	int8_t result = *n + 1;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F &= 0b10111111;
	bool C = carry(*n, 1);
	bool H = hcarry(*n, 1);
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	*n = result;
}
void Z80::_DEC(uint8_t* n){
	int8_t result = *n - 1;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F |= 0b01000000;
	bool C = (1 > *n);
	bool H = ((1&0xF) > (*n&0xF));
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	*n = result;
}

void Z80::i_0x4(uint16_t args){
	_INC(&registers.B);
}
void Z80::i_0x5(uint16_t args){
	_DEC(&registers.B);
}
void Z80::i_0xc(uint16_t args){
	_INC(&registers.C);
}
void Z80::i_0xd(uint16_t args){
	_DEC(&registers.C);
}

void Z80::i_0x14(uint16_t args){
	_INC(&registers.D);
}
void Z80::i_0x15(uint16_t args){
	_DEC(&registers.D);
}
void Z80::i_0x1c(uint16_t args){
	_INC(&registers.E);
}
void Z80::i_0x1d(uint16_t args){
	_DEC(&registers.E);
}

void Z80::i_0x24(uint16_t args){
	_INC(&registers.H);
}
void Z80::i_0x25(uint16_t args){
	_DEC(&registers.H);
}
void Z80::i_0x27(uint16_t args){
	if(registers.F & 0x40 == 0x40) {
		if(registers.F & 0x10 == 0x10) {
			registers.A -= 0x60;
			registers.F |= 0x10;
		}
		if(registers.F & 0x20 == 0x20)
			registers.A -= 0x6;
	}else{
		if((registers.F & 0x10 == 0x10) || registers.A > 0x99) {
			registers.A += 0x60;
			registers.F |= 0x10;
		}
		if (((registers.A & 0xF)>0x9) || (registers.F & 0x20 == 0x20))
			registers.A += 0x6;
	}

	if(!registers.A) registers.F &= 0b01111111; else registers.F |= 0b10000000;
	registers.F &= 0b110111111;
}
void Z80::i_0x2c(uint16_t args){
	_INC(&registers.L);
}
void Z80::i_0x2d(uint16_t args){
	_DEC(&registers.L);
}
void Z80::i_0x2f(uint16_t args){
	registers.F |= 0b01100000;
	registers.A = ~registers.A;
}

void Z80::i_0x34(uint16_t args){
	int8_t result = mem.read(registers.HL) + 1;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F &= 0b10111111;
	bool C = carry(mem.read(registers.HL), 1);
	bool H = hcarry(mem.read(registers.HL), 1);
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	mem.write(registers.HL,result);
}
void Z80::i_0x35(uint16_t args){
	int8_t result = mem.read(registers.HL) - 1;
	if(!result) registers.F |= 0b10000000;
	else registers.F &= 0b01111111;
	registers.F |= 0b01000000;
	bool C = (1 > mem.read(registers.HL));
	bool H = ((1&0xF) > (mem.read(registers.HL)&0xF));
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	mem.write(registers.HL, result);
}
void Z80::i_0x37(uint16_t args){
	registers.F &= 0b10011111;
	registers.F |= 0b00010000;

}
void Z80::i_0x3c(uint16_t args){
	_INC(&registers.A);
}
void Z80::i_0x3d(uint16_t args){
	_DEC(&registers.A);
}
void Z80::i_0x3f(uint16_t args){
	if(registers.F & 0x10 == 0x10)
		registers.F &= 0b11101111;
	else
		registers.F |= 0b00010000;
	registers.F &= 0b10011111;
}


void Z80::i_0x80(uint16_t args){
	_ADD(registers.B);
}
void Z80::i_0x81(uint16_t args){
	_ADD(registers.C);
}
void Z80::i_0x82(uint16_t args){
	_ADD(registers.D);
}
void Z80::i_0x83(uint16_t args){
	_ADD(registers.E);
}
void Z80::i_0x84(uint16_t args){
	_ADD(registers.H);
}
void Z80::i_0x85(uint16_t args){
	_ADD(registers.L);
}
void Z80::i_0x86(uint16_t args){
	_ADD(mem.read(registers.HL));
}
void Z80::i_0x87(uint16_t args){
	_ADD(registers.A);
}

void Z80::i_0x88(uint16_t args){
	_ADC(registers.B);
}
void Z80::i_0x89(uint16_t args){
	_ADC(registers.C);
}
void Z80::i_0x8a(uint16_t args){
	_ADC(registers.D);
}
void Z80::i_0x8b(uint16_t args){
	_ADC(registers.E);
}
void Z80::i_0x8c(uint16_t args){
	_ADC(registers.H);
}
void Z80::i_0x8d(uint16_t args){
	_ADC(registers.L);
}
void Z80::i_0x8e(uint16_t args){
	_ADC(mem.read(registers.HL));
}
void Z80::i_0x8f(uint16_t args){
	_ADC(registers.A);
}


void Z80::i_0x90(uint16_t args){
	_SUB(registers.B);
}
void Z80::i_0x91(uint16_t args){
	_SUB(registers.C);
}
void Z80::i_0x92(uint16_t args){
	_SUB(registers.D);
}
void Z80::i_0x93(uint16_t args){
	_SUB(registers.E);
}
void Z80::i_0x94(uint16_t args){
	_SUB(registers.H);
}
void Z80::i_0x95(uint16_t args){
	_SUB(registers.L);
}
void Z80::i_0x96(uint16_t args){
	_SUB(mem.read(registers.HL));
}
void Z80::i_0x97(uint16_t args){
	_SUB(registers.A);
}
void Z80::i_0x98(uint16_t args){
	_SDC(registers.B);
}
void Z80::i_0x99(uint16_t args){
	_SDC(registers.C);
}
void Z80::i_0x9a(uint16_t args){
	_SDC(registers.D);
}
void Z80::i_0x9b(uint16_t args){
	_SDC(registers.E);
}
void Z80::i_0x9c(uint16_t args){
	_SDC(registers.H);
}
void Z80::i_0x9d(uint16_t args){
	_SDC(registers.L);
}
void Z80::i_0x9e(uint16_t args){
	_SDC(mem.read(registers.HL));
}
void Z80::i_0x9f(uint16_t args){
	_SDC(registers.A);
}

void Z80::i_0xa0(uint16_t args){
	_AND(registers.B);
}
void Z80::i_0xa1(uint16_t args){
	_AND(registers.C);
}
void Z80::i_0xa2(uint16_t args){
	_AND(registers.D);
}
void Z80::i_0xa3(uint16_t args){
	_AND(registers.E);
}
void Z80::i_0xa4(uint16_t args){
	_AND(registers.H);
}
void Z80::i_0xa5(uint16_t args){
	_AND(registers.L);
}
void Z80::i_0xa6(uint16_t args){
	_AND(mem.read(registers.HL));
}
void Z80::i_0xa7(uint16_t args){
	_AND(registers.A);
}
void Z80::i_0xa8(uint16_t args){
	_XOR(registers.B);
}
void Z80::i_0xa9(uint16_t args){
	_XOR(registers.C);
}
void Z80::i_0xaa(uint16_t args){
	_XOR(registers.D);
}
void Z80::i_0xab(uint16_t args){
	_XOR(registers.E);
}
void Z80::i_0xac(uint16_t args){
	_XOR(registers.H);
}
void Z80::i_0xad(uint16_t args){
	_XOR(registers.L);
}
void Z80::i_0xae(uint16_t args){
	_XOR(mem.read(registers.HL));
}
void Z80::i_0xaf(uint16_t args){
	_XOR(registers.A);
}




void Z80::i_0xb0(uint16_t args){
	_OR(registers.B);
}
void Z80::i_0xb1(uint16_t args){
	_OR(registers.C);
}
void Z80::i_0xb2(uint16_t args){
	_OR(registers.D);
}
void Z80::i_0xb3(uint16_t args){
	_OR(registers.E);
}
void Z80::i_0xb4(uint16_t args){
	_OR(registers.H);
}
void Z80::i_0xb5(uint16_t args){
	_OR(registers.L);
}
void Z80::i_0xb6(uint16_t args){
	_OR(mem.read(registers.HL));
}
void Z80::i_0xb7(uint16_t args){
	_OR(registers.A);
}
void Z80::i_0xb8(uint16_t args){
	_CP(registers.B);
}
void Z80::i_0xb9(uint16_t args){
	_CP(registers.C);
}
void Z80::i_0xba(uint16_t args){
	_CP(registers.D);
}
void Z80::i_0xbb(uint16_t args){
	_CP(registers.E);
}
void Z80::i_0xbc(uint16_t args){
	_CP(registers.H);
}
void Z80::i_0xbd(uint16_t args){
	_CP(registers.L);
}
void Z80::i_0xbe(uint16_t args){
	_CP(mem.read(registers.HL));
}
void Z80::i_0xbf(uint16_t args){
	_CP(registers.A);
}


void Z80::i_0xc6(uint16_t args){
	_ADD((args&0xFF));
}
void Z80::i_0xce(uint16_t args){
	_ADC((args&0xFF));
}
void Z80::i_0xd6(uint16_t args){
	_SUB((args&0xFF));
}
void Z80::i_0xde(uint16_t args){
	_SDC((args&0xFF));
}
void Z80::i_0xe6(uint16_t args){
	_AND((args&0xFF));
}
void Z80::i_0xee(uint16_t args){
	_XOR((args&0xFF));
}
void Z80::i_0xf6(uint16_t args){
	_OR((args&0xFF));
}
void Z80::i_0xfe(uint16_t args){
	_CP((args&0xFF));
}


/* 16-bit arithmetic / logical instructions */

#define carry16(a,b) (a&0xFF) && (b&0xF00)
#define hcarry16(a,b) (((a&0xf) + (b&0xf))&0xF0)

void Z80::_ADD16(uint16_t* r, uint16_t n){
	uint16_t result = *r + ((int16_t)args & 0xFF);
	bool C = carry16(*r, n);
	bool H = carry16(*r, n);
	registers.F &= 0b10111111;
	if(H) registers.F |= 0b00100000; else registers.F &= 0b11011111;
	if(C) registers.F |= 0b00010000; else registers.F &= 0b11101111;
	*r = result;
}

void Z80::i_0x3(uint16_t args){
	registers.BC++;
}
void Z80::i_0x9(uint16_t args){
	_ADD16(&registers.HL, registers.BC);
}
void Z80::i_0xb(uint16_t args){
	registers.BC--;
}

void Z80::i_0x13(uint16_t args){
	registers.DE++;
}
void Z80::i_0x19(uint16_t args){
	_ADD16(&registers.HL, registers.DE);
}
void Z80::i_0x1b(uint16_t args){
	registers.DE--;
}

void Z80::i_0x23(uint16_t args){
	registers.HL++;
}
void Z80::i_0x29(uint16_t args){
	_ADD16(&registers.HL, registers.HL);
}
void Z80::i_0x2b(uint16_t args){
	registers.HL--;
}

void Z80::i_0x33(uint16_t args){
	registers.SP++;
}
void Z80::i_0x39(uint16_t args){
	_ADD16(&registers.HL, registers.SP);
}
void Z80::i_0x3b(uint16_t args){
	registers.SP--;
}

void Z80::i_0xe8(uint16_t args){
	registers.F &= 0b01111111;
	_ADD16(&registers.HL, args);
}


/* 8-bit shift, rotate and bit instructions */

void Z80::i_0x7(uint16_t args){
	if(registers.A & 0x80 == 0x80) registers.F |= 0x10;
	else registers.F &= 0b11101111;
	registers.F &= 0b10011111;
	uint8_t result = registers.A << 1;
	if(result == 0) registers.F |= 0x80;
	else registers.F &= 0b01111111;
	registers.A = result;
}
void Z80::i_0xf(uint16_t args){
	if(registers.A & 0x1 == 0x1) registers.F |= 0x10;
	else registers.F &= 0b11101111;
	registers.F &= 0b10011111;
	uint8_t result = registers.A >> 1;
	if(result == 0) registers.F |= 0x80;
	else registers.F &= 0b01111111;
	registers.A = result;
}
void Z80::i_0x17(uint16_t args){
	uint8_t old_c = registers.F & 0x10;
	if(registers.A & 0x80 == 0x80) registers.F |= 0x10;
	else registers.F &= 0b11101111;
	registers.F &= 0b10011111;
	uint8_t result = (registers.A << 1)|(old_c >> 4);
	if(result == 0) registers.F |= 0x80;
	else registers.F &= 0b01111111;
	registers.A = result;
}
void Z80::i_0x1f(uint16_t args){
	uint8_t old_c = registers.F & 0x10;
	if(registers.A & 0x1 == 0x1) registers.F |= 0x10;
	else registers.F &= 0b11101111;
	registers.F &= 0b10011111;
	uint8_t result = (registers.A >> 1)|(old_c << 3);
	if(result == 0) registers.F |= 0x80;
	else registers.F &= 0b01111111;
	registers.A = result;
}


/* Misc / control instructions */

void Z80::i_0x0(uint16_t args){
	return;
}
void Z80::i_0x10(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0x76(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xcb(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xf3(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xfb(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}

/* Jumps / calls */

void Z80::i_0x18(uint16_t args){
	registers.PC += (args & 0xFF);
}

void Z80::i_0x20(uint16_t args){
	if((registers.F & 0x80) == 0x0)
		i_0x18(args);
}

void Z80::i_0x28(uint16_t args){
	if((registers.F & 0x80) == 0x80)
		i_0x18(args);
}

void Z80::i_0x30(uint16_t args){
	if((registers.F & 0x10) == 0x0)
		i_0x18(args);
}

void Z80::i_0x38(uint16_t args){
	if((registers.F & 0x10) == 0x10)
		i_0x18(args);
}









void Z80::i_0xc0(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xc2(uint16_t args){
	if((registers.F & 0x80) == 0x0)
		i_0xc3(args);
}
void Z80::i_0xc3(uint16_t args){
	registers.PC = ((args & 0xFF)<<8)|((args & 0xFF00)>>8);
}
void Z80::i_0xc4(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}


void Z80::i_0xc7(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xc8(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xc9(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xca(uint16_t args){
	if((registers.F & 0x80) == 0x80)
		i_0xc3(args);
}
void Z80::i_0xcc(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xcd(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xcf(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}




void Z80::i_0xd0(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xd2(uint16_t args){
	if((registers.F & 0x10) == 0x0)
		i_0xc3(args);
}
void Z80::i_0xd3(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xd4(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}


void Z80::i_0xd7(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xd8(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xd9(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xda(uint16_t args){
	if((registers.F & 0x10) == 0x10)
		i_0xc3(args);
}
void Z80::i_0xdb(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xdc(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xdd(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xdf(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}


void Z80::i_0xe3(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xe4(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}


void Z80::i_0xe7(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xe9(uint16_t args){
	registers.PC = mem.read(registers.HL);
}



void Z80::i_0xeb(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xec(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xed(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xef(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}




void Z80::i_0xf4(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}

void Z80::i_0xf7(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xfc(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xfd(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
void Z80::i_0xff(uint16_t args){std::cout<<"\nNOT IMPLEMENTED YET\n";}
