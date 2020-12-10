#include "Z80.h"
#include "mem.h"

extern Mem mem;


#define carry(result,dest) (result < dest)
#define hcarry(result,value,dest) (((result ^ value ^ dest) & 0x10) == 0x10);

void Z80::_ADD(uint8_t n){
	uint8_t result = registers.A + n;
	
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK);
	
	bool C = carry(result,registers.A);
	bool H = hcarry(result,n,registers.A);
	
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(C) SET_FLAG(C_FLAG_MASK); else RESET_FLAG(C_FLAG_MASK);;
	registers.A = result;
}

void Z80::_ADC(uint8_t n){
	uint8_t result = registers.A + n + ((registers.F & 0x10)>>4);
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK);
	bool C = (((int)registers.A + (int)n + (int)((registers.F & 0x10)>>4)) > 0xFF);
	bool H = ((registers.A & 0xF) + (n & 0xF) + ((registers.F & 0x10)>>4)) > 0xF;
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(C) SET_FLAG(C_FLAG_MASK); else RESET_FLAG(C_FLAG_MASK);;
	registers.A = result;
}

void Z80::_SUB(uint8_t n){
	int8_t result = registers.A - n;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	SET_FLAG(N_FLAG_MASK);
	bool C = (n > registers.A);
	bool H = ((n&0xF) > (registers.A&0xF));
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(C) SET_FLAG(C_FLAG_MASK); else RESET_FLAG(C_FLAG_MASK);;
	registers.A = result;
}

void Z80::_SDC(uint8_t n){
	int32_t dest 	= static_cast<uint32_t>(registers.A) & 0xFF;
	int32_t sub 	= static_cast<uint32_t>(n) & 0xFF;
	int32_t cflag 	= (C_FLAG_TEST)?1:0;
	
	int32_t result = dest - sub - cflag;
	
	
	SET_FLAG(N_FLAG_MASK);
	
	bool C = result < 0;
	bool H =  ((((result &= 0xFF) ^ n ^ registers.A) & 0x10) == 0x10);
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(C) SET_FLAG(C_FLAG_MASK); else RESET_FLAG(C_FLAG_MASK);;
	registers.A = result;
}

void Z80::_AND(uint8_t n){
	uint8_t result = registers.A & n;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | C_FLAG_MASK);
	SET_FLAG(H_FLAG_MASK);
	registers.A = result;
}

void Z80::_OR(uint8_t n){
	uint8_t result = registers.A | n;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK | C_FLAG_MASK);
	registers.A = result;
}

void Z80::_XOR(uint8_t n){
	uint8_t result = registers.A ^ n;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK | C_FLAG_MASK);
	registers.A = result;
}

void Z80::_CP(uint8_t n){
	uint8_t result = registers.A - n;
	SET_FLAG(N_FLAG_MASK);
	bool C = (n > registers.A);
	bool H = ((n&0xF) > (registers.A&0xF));
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(C) SET_FLAG(C_FLAG_MASK); else RESET_FLAG(C_FLAG_MASK);;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
}

void Z80::_INC(uint8_t* n){
	int8_t result = *n + 1;
	RESET_FLAG(N_FLAG_MASK);
	
	bool H = (((*n >> 3) & 1) != 0 && (((result >> 3) & 1) == 0));
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	*n = result;
}

void Z80::_DEC(uint8_t* n){
	int8_t result = *n - 1;
	SET_FLAG(N_FLAG_MASK);
	
	bool H = (((result ^ 0x01 ^ (*n)) & 0x10) == 0x10);
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	*n = result;
}

#define carry16(result, dest) (result < dest) // (a&0xFF) && (b&0xF00)
#define hcarry16(result,n, dest) (((result ^ dest ^ n) & 0x1000) != 0) //(((a&0xf) + (b&0xf))&0xF0)

void Z80::_ADD16(uint16_t* r, uint16_t n){
	uint16_t result = *r + (n);
	bool C = carry16(result,*r);
	bool H = hcarry16(result,n,*r);
	
	RESET_FLAG(N_FLAG_MASK);
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(C) SET_FLAG(C_FLAG_MASK); else RESET_FLAG(C_FLAG_MASK);;
	
	*r = result;
}
void Z80::_ADD16(uint16_t* r, int8_t n){
	uint16_t result = *r + (n);
	bool C = ((result & 0xFF) < (*r & 0xFF));
	bool H = ((result & 0xF) < (*r & 0xF));
     
	RESET_FLAG(Z_FLAG_MASK | N_FLAG_MASK);
	if(H) SET_FLAG(H_FLAG_MASK); else RESET_FLAG(H_FLAG_MASK);;
	if(C) SET_FLAG(C_FLAG_MASK); else RESET_FLAG(C_FLAG_MASK);;
	
	*r = result;
}
void Z80::_RL(uint8_t* r){
	uint8_t old_c = registers.F & 0x10;
	if(((*r) & 0x80) == 0x0) RESET_FLAG(C_FLAG_MASK);
	else SET_FLAG(C_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK); 
	uint8_t result = (uint8_t)(((*r) << 1)|(old_c ==0x10 ? (uint8_t)0x1 : (uint8_t)0x0));
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	*r = result;
}

void Z80::_RLC(uint8_t* r){
	uint8_t msb = (*r) & 0x80;
	if(msb == 0x80) SET_FLAG(C_FLAG_MASK);
	else RESET_FLAG(C_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK);
	uint8_t result = (*r) << 1;
	if(msb == 0x80) result |= 0x01;
	else result &= 0xFE;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	*r = result;
}

void Z80::_RRC(uint8_t* r){
	uint8_t lsb = (*r) & 0x1;
	if(lsb == 0x1) SET_FLAG(C_FLAG_MASK);
	else RESET_FLAG(C_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK);
	uint8_t result = (*r) >> 1;
	if(lsb == 0x1) result |= 0x80;
	else result &= 0x7F;
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	*r = result;
}

void Z80::_RR(uint8_t* r){
	uint8_t old_c = registers.F & 0x10;
	if(((*r) & 0x1) == 0x1) SET_FLAG(C_FLAG_MASK);
	else RESET_FLAG(C_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK);
	//if((*r & 0x01) == 0x01) ? registers.F |= 0x10: registers.F &= 0b11101111; 
	uint8_t result = ((*r) >> 1)|(old_c << 3);
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	*r = result;
}

void Z80::_SLA(uint8_t* r){
	if((*r & 0x80) == 0x80) SET_FLAG(C_FLAG_MASK);
	else RESET_FLAG(C_FLAG_MASK);
	*r <<= 1;
	RESET_FLAG(N_FLAG_MASK);
	RESET_FLAG(H_FLAG_MASK);
	if(*r == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
}

void Z80::_SRA(uint8_t* r){
	uint8_t result = ((*r) >> 1) | ((*r) & 0x80);
	if(((*r) & 0x01) == 0x01) SET_FLAG(C_FLAG_MASK);
	else RESET_FLAG(C_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK);
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	*r = result;
}

void Z80::_SRL(uint8_t* r){
	uint8_t result = ((*r) >> 1);
	if(((*r) & 0x01) == 0x01) SET_FLAG(C_FLAG_MASK);
	else RESET_FLAG(C_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK);
	if(result == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	*r = result;
}

void Z80::_SWAP(uint8_t& r){
	r = ((r & 0xF) << 4) | ((r & 0xF0) >> 4);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK | C_FLAG_MASK);
	if(r == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
} 

void Z80::_BIT(uint8_t b, uint8_t r){
	RESET_FLAG(N_FLAG_MASK);
	SET_FLAG(H_FLAG_MASK);
	
	if((r & (1 << b)) == 0x0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	
}

void Z80::_RES(uint8_t b, uint8_t* r){
	(*r) &= (~(0x01 << b));
}

void Z80::_SET(uint8_t b, uint8_t* r){
	(*r) |= (0x01 << b);
}

/* 8-bit load instructions */

void Z80::i_0x2(uint16_t args){
	mem.write(registers.BC, registers.A);
}

void Z80::i_0x6(uint16_t args){
	registers.B = (uint8_t)(args);
}

void Z80::i_0xa(uint16_t args){
	registers.A = mem.read(registers.BC);
}

void Z80::i_0xe(uint16_t args){
	registers.C = (uint8_t)(args);
}

void Z80::i_0x12(uint16_t args){
	mem.write(registers.DE, registers.A);
}

void Z80::i_0x16(uint16_t args){
	registers.D = (uint8_t)(args);
}

void Z80::i_0x1a(uint16_t args){
	registers.A = mem.read(registers.DE);
}

void Z80::i_0x1e(uint16_t args){
	registers.E = (uint8_t)(args);
}

void Z80::i_0x22(uint16_t args){
	mem.write(registers.HL, registers.A);
	registers.HL++;
}

void Z80::i_0x26(uint16_t args){
	registers.H = (uint8_t)(args);
}

void Z80::i_0x2a(uint16_t args){
	registers.A = mem.read(registers.HL);
	registers.HL++;
}

void Z80::i_0x2e(uint16_t args){
	registers.L = (uint8_t)(args);
}

void Z80::i_0x32(uint16_t args){
	mem.write(registers.HL, registers.A);
	registers.HL--;
}

void Z80::i_0x36(uint16_t args){
	mem.write(registers.HL, (unsigned char)(args&0xFF));
}

void Z80::i_0x3a(uint16_t args){
	registers.A = mem.read(registers.HL);
	registers.HL--;
}

void Z80::i_0x3e(uint16_t args){
	registers.A = (uint8_t)(args);
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
	mem.write((uint16_t)(0xFF00 + (args&0x00FF)),registers.A);
}

void Z80::i_0xe2(uint16_t args){
	mem.write(0xFF00+registers.C, registers.A);
}

void Z80::i_0xea(uint16_t args){
	mem.write(args, registers.A);
}

void Z80::i_0xf0(uint16_t args){
	registers.A = mem.read(0xFF00 + (args&0x00FF));
}

void Z80::i_0xf2(uint16_t args){
	registers.A = mem.read(0xFF00+registers.C);
}

void Z80::i_0xfa(uint16_t args){
	registers.A = mem.read(args);
}

/* 16-bit load instructions */
void Z80::i_0x1(uint16_t args){
	registers.BC = (args);
}

void Z80::i_0x8(uint16_t args){
	mem.write(args, (unsigned char)((registers.SP & 0x00FF)));
	mem.write(args+1, (unsigned char)((registers.SP & 0xFF00)>>8));
}

void Z80::i_0x11(uint16_t args){
	registers.DE = args;
}

void Z80::i_0x21(uint16_t args){
	registers.HL = args;
}

void Z80::i_0x31(uint16_t args){
	registers.SP = args;
}

void Z80::i_0xf8(uint16_t args){
	uint16_t result = registers.SP;
	_ADD16(&result, static_cast<int8_t>(args & 0xFF));
	registers.HL = result;
}

void Z80::i_0xf9(uint16_t args){
	registers.SP = registers.HL;
}

void Z80::i_0xc5(uint16_t args){
	mem.write(--registers.SP, registers.B);
	mem.write(--registers.SP, registers.C);
}

void Z80::i_0xd5(uint16_t args){
	mem.write(--registers.SP, registers.D);
	mem.write(--registers.SP, registers.E);
}

void Z80::i_0xe5(uint16_t args){
	mem.write(--registers.SP, registers.H);
	mem.write(--registers.SP, registers.L);
}

void Z80::i_0xf5(uint16_t args){
	mem.write(--registers.SP, registers.A);
	mem.write(--registers.SP, registers.F);
}

void Z80::i_0xc1(uint16_t args){
	registers.B = mem.read(registers.SP + 1);
	registers.C = mem.read(registers.SP);
	registers.SP += 2;
}

void Z80::i_0xd1(uint16_t args){
	registers.D = mem.read(registers.SP + 1);
	registers.E = mem.read(registers.SP);
	registers.SP += 2;
}

void Z80::i_0xe1(uint16_t args){
	registers.H = mem.read(registers.SP + 1);
	registers.L = mem.read(registers.SP);
	registers.SP += 2;
}

void Z80::i_0xf1(uint16_t args){
	registers.A = mem.read(registers.SP + 1);
	registers.F = mem.read(registers.SP);
	registers.SP += 2;
	registers.F &= 0xF0;
}

/* 8-bit arithmetic / logical instructions */

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
	if(N_FLAG_TEST) {
		if(C_FLAG_TEST) {
			registers.A -= 0x60;
			SET_FLAG(C_FLAG_MASK);
		}
		if(H_FLAG_TEST)
			registers.A -= 0x6;
	}else{
		if(C_FLAG_TEST || registers.A > 0x99) {
			registers.A += 0x60;
			SET_FLAG(C_FLAG_MASK);
		}
		if (H_FLAG_TEST || (registers.A & 0xF) > 0x9)
			registers.A += 0x6;
	}

	if(registers.A == 0) SET_FLAG(Z_FLAG_MASK);
	else RESET_FLAG(Z_FLAG_MASK);
	RESET_FLAG(H_FLAG_MASK);
}

void Z80::i_0x2c(uint16_t args){
	_INC(&registers.L);
}

void Z80::i_0x2d(uint16_t args){
	_DEC(&registers.L);
}

void Z80::i_0x2f(uint16_t args){
	SET_FLAG(N_FLAG_MASK | H_FLAG_MASK);
	registers.A = ~registers.A;
}

void Z80::i_0x34(uint16_t args){
	uint8_t result = mem.read(registers.HL);
	_INC(&result);
	mem.write(registers.HL, result);
}

void Z80::i_0x35(uint16_t args){
	uint8_t result = mem.read(registers.HL);
	_DEC(&result);
	mem.write(registers.HL, result);
}

void Z80::i_0x37(uint16_t args){
	SET_FLAG(C_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK);
}

void Z80::i_0x3c(uint16_t args){
	_INC(&registers.A);
}

void Z80::i_0x3d(uint16_t args){
	_DEC(&registers.A);
}

void Z80::i_0x3f(uint16_t args){
	if(C_FLAG_TEST)
		RESET_FLAG(C_FLAG_MASK);
	else
		SET_FLAG(C_FLAG_MASK);
	RESET_FLAG(N_FLAG_MASK | H_FLAG_MASK);
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
	registers.F |= 0x80;
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
	_ADD((int8_t)args);
}

void Z80::i_0xce(uint16_t args){
	_ADC((int8_t)args);
}

void Z80::i_0xd6(uint16_t args){
	_SUB((int8_t)args);
}

void Z80::i_0xde(uint16_t args){
	_SDC((int8_t)args);
}

void Z80::i_0xe6(uint16_t args){
	_AND((int8_t)args);
}

void Z80::i_0xee(uint16_t args){
	_XOR((int8_t)args);
}

void Z80::i_0xf6(uint16_t args){
	_OR((int8_t)args);
}

void Z80::i_0xfe(uint16_t args){
	_CP((int8_t)args);
}


/* 16-bit arithmetic / logical instructions */

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
	_ADD16(&registers.SP, (int8_t)(args & 0xFF));
}


/* 8-bit shift, rotate and bit instructions */

void Z80::i_0x7(uint16_t args){
	_RLC(&registers.A);
	RESET_FLAG(Z_FLAG_MASK | N_FLAG_MASK | H_FLAG_MASK);
}

void Z80::i_0xf(uint16_t args){
	_RRC(&registers.A);
	RESET_FLAG(Z_FLAG_MASK | N_FLAG_MASK | H_FLAG_MASK);
}

void Z80::i_0x17(uint16_t args){
	_RL(&registers.A);
	RESET_FLAG(Z_FLAG_MASK | N_FLAG_MASK | H_FLAG_MASK);
}

void Z80::i_0x1f(uint16_t args){
	_RR(&registers.A);
	RESET_FLAG(Z_FLAG_MASK | N_FLAG_MASK | H_FLAG_MASK);
}


/* Misc / control instructions */

void Z80::i_0x0(uint16_t args){
	/* NOP */
	return;
}

void Z80::i_0x10(uint16_t args){
	STOP = true;
}

void Z80::i_0x76(uint16_t args){
	HALT = true;
}

void Z80::i_0xcb(uint16_t args){
	/* PREFIX */
	return;
}

void Z80::i_0xf3(uint16_t args){
	IME = false;
}

void Z80::i_0xfb(uint16_t args){
	IME = true;
}

/* Jumps / calls */

void Z80::i_0x18(uint16_t args){
	registers.PC += (int8_t)(args & 0xFF);
}

void Z80::i_0x20(uint16_t args){
	if(!Z_FLAG_TEST)
		i_0x18(args);
}

void Z80::i_0x28(uint16_t args){
	if(Z_FLAG_TEST)
		i_0x18(args);
}

void Z80::i_0x30(uint16_t args){
	if(!C_FLAG_TEST)
		i_0x18(args);
}

void Z80::i_0x38(uint16_t args){
	if(C_FLAG_TEST)
		i_0x18(args);
}

void Z80::i_0xc0(uint16_t args){
	if(!Z_FLAG_TEST)
		i_0xc9(args);
}

void Z80::i_0xc2(uint16_t args){
	if(!Z_FLAG_TEST)
		i_0xc3(args);
}

void Z80::i_0xc3(uint16_t args){
	registers.PC = args;//((args & 0xFF)<<8)|((args & 0xFF00)>>8);
}

void Z80::i_0xc4(uint16_t args){
	if(!Z_FLAG_TEST)
		i_0xcd(args);
}

void Z80::i_0xc7(uint16_t args){
	i_0xcd(0x00);
}

void Z80::i_0xc8(uint16_t args){
	if(Z_FLAG_TEST)
		i_0xc9(args);
}

void Z80::i_0xc9(uint16_t args){
	registers.PC = mem.read(registers.SP++) | (mem.read(registers.SP++) << 8);
}

void Z80::i_0xca(uint16_t args){
	if(Z_FLAG_TEST)
		i_0xc3(args);
}

void Z80::i_0xcc(uint16_t args){
	if(Z_FLAG_TEST)
		i_0xcd(args);
}

void Z80::i_0xcd(uint16_t args){
	mem.write(--registers.SP, ((registers.PC & 0xFF00)>>8));
	mem.write(--registers.SP, (registers.PC & 0xFF));
	i_0xc3(args);
}

void Z80::i_0xcf(uint16_t args){
	i_0xcd(0x08);
}

void Z80::i_0xd0(uint16_t args){
	if(!C_FLAG_TEST)
		i_0xc9(args);
}

void Z80::i_0xd2(uint16_t args){
	if(!C_FLAG_TEST)
		i_0xc3(args);
}

void Z80::i_0xd4(uint16_t args){
	if(!C_FLAG_TEST)
		i_0xcd(args);
}

void Z80::i_0xd7(uint16_t args){
	i_0xcd(0x10);
}

void Z80::i_0xd8(uint16_t args){
	if(C_FLAG_TEST)
		i_0xc9(args);
}

void Z80::i_0xd9(uint16_t args){
	IME = true;
	i_0xc9(args);
}

void Z80::i_0xda(uint16_t args){
	if(C_FLAG_TEST)
		i_0xc3(args);
}

void Z80::i_0xdc(uint16_t args){
	if(C_FLAG_TEST)
		i_0xcd(args);
}

void Z80::i_0xdf(uint16_t args){
	i_0xcd(0x18);
}

void Z80::i_0xe7(uint16_t args){
	i_0xcd(0x20);
}

void Z80::i_0xe9(uint16_t args){
	registers.PC = registers.HL;
}

void Z80::i_0xef(uint16_t args){
	i_0xcd(0x28);
}

void Z80::i_0xf7(uint16_t args){
	i_0xcd(0x30);
}

void Z80::i_0xff(uint16_t args){
	i_0xcd(0x38);
}

/* Unsupported opcodes */
void Z80::i_0xd3(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xd3 at 0x"<<registers.PC<<"\n";}
void Z80::i_0xdb(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xdb at 0x"<<registers.PC<<"\n";}
void Z80::i_0xdd(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xdd at 0x"<<registers.PC<<"\n";}
void Z80::i_0xe3(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xe3 at 0x"<<registers.PC<<"\n";}
void Z80::i_0xe4(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xe4 at 0x"<<registers.PC<<"\n";}
void Z80::i_0xeb(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xeb at 0x"<<registers.PC<<"\n";}
void Z80::i_0xec(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xec at 0x"<<registers.PC<<"\n";}
void Z80::i_0xed(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xed at 0x"<<registers.PC<<"\n";}
void Z80::i_0xf4(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xf4 at 0x"<<registers.PC<<"\n";}
void Z80::i_0xfc(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xfc at 0x"<<registers.PC<<"\n";}
void Z80::i_0xfd(uint16_t args){std::cout<<"\nUNSUPPORTED OPCODE : 0xfd at 0x"<<registers.PC<<"\n";}


/* Prefixed instructions */


void Z80::pi_0x0(uint16_t args){
	_RLC(&registers.B);
}
void Z80::pi_0x1(uint16_t args){
	_RLC(&registers.C);
}
void Z80::pi_0x2(uint16_t args){
	_RLC(&registers.D);
}
void Z80::pi_0x3(uint16_t args){
	_RLC(&registers.E);
}
void Z80::pi_0x4(uint16_t args){
	_RLC(&registers.H);
}
void Z80::pi_0x5(uint16_t args){
	_RLC(&registers.L);
}
void Z80::pi_0x6(uint16_t args){
	uint8_t temp = (uint8_t) mem.read(registers.HL);
	_RLC(&temp);
	mem.write(registers.HL, temp);
}
void Z80::pi_0x7(uint16_t args){
	_RLC(&registers.A);
}
void Z80::pi_0x8(uint16_t args){
	_RRC(&registers.B);
}
void Z80::pi_0x9(uint16_t args){
	_RRC(&registers.C);
}
void Z80::pi_0xa(uint16_t args){
	_RRC(&registers.D);
}
void Z80::pi_0xb(uint16_t args){
	_RRC(&registers.E);
}
void Z80::pi_0xc(uint16_t args){
	_RRC(&registers.H);
}
void Z80::pi_0xd(uint16_t args){
	_RRC(&registers.L);
}
void Z80::pi_0xe(uint16_t args){
	uint8_t temp = (uint8_t) mem.read(registers.HL);
	_RRC(&temp);
	mem.write(registers.HL, temp);
}
void Z80::pi_0xf(uint16_t args){
	_RRC(&registers.A);
}


void Z80::pi_0x10(uint16_t args){
	_RL(&registers.B);
}
void Z80::pi_0x11(uint16_t args){
	_RL(&registers.C);
}
void Z80::pi_0x12(uint16_t args){
	_RL(&registers.D);
}
void Z80::pi_0x13(uint16_t args){
	_RL(&registers.E);
}
void Z80::pi_0x14(uint16_t args){
	_RL(&registers.H);
}
void Z80::pi_0x15(uint16_t args){
	_RL(&registers.L);
}
void Z80::pi_0x16(uint16_t args){
	uint8_t temp = (uint8_t) mem.read(registers.HL);
	_RL(&temp);
	mem.write(registers.HL, (unsigned char)temp);
}
void Z80::pi_0x17(uint16_t args){
	_RL(&registers.A);
}


void Z80::pi_0x18(uint16_t args){
	_RR(&registers.B);
}
void Z80::pi_0x19(uint16_t args){
	_RR(&registers.C);
}
void Z80::pi_0x1a(uint16_t args){
	_RR(&registers.D);
}
void Z80::pi_0x1b(uint16_t args){
	_RR(&registers.E);
}
void Z80::pi_0x1c(uint16_t args){
	_RR(&registers.H);
}
void Z80::pi_0x1d(uint16_t args){
	_RR(&registers.L);
}
void Z80::pi_0x1e(uint16_t args){
	uint8_t temp = (uint8_t) mem.read(registers.HL);
	_RR(&temp);
	mem.write(registers.HL, temp);
}
void Z80::pi_0x1f(uint16_t args){
	_RR(&registers.A);
}

void Z80::pi_0x20(uint16_t args){
	_SLA(&registers.B);
}
void Z80::pi_0x21(uint16_t args){
	_SLA(&registers.C);
}
void Z80::pi_0x22(uint16_t args){
	_SLA(&registers.D);
}
void Z80::pi_0x23(uint16_t args){
	_SLA(&registers.E);
}
void Z80::pi_0x24(uint16_t args){
	_SLA(&registers.H);
}
void Z80::pi_0x25(uint16_t args){
	_SLA(&registers.L);
}
void Z80::pi_0x26(uint16_t args){
	uint8_t temp = (uint8_t) mem.read(registers.HL);
	_SLA(&temp);
	mem.write(registers.HL, temp);
}
void Z80::pi_0x27(uint16_t args){
	_SLA(&registers.A);
}


void Z80::pi_0x28(uint16_t args){
	_SRA(&registers.B);
}
void Z80::pi_0x29(uint16_t args){
	_SRA(&registers.C);
}
void Z80::pi_0x2a(uint16_t args){
	_SRA(&registers.D);
}
void Z80::pi_0x2b(uint16_t args){
	_SRA(&registers.E);
}
void Z80::pi_0x2c(uint16_t args){
	_SRA(&registers.H);
}
void Z80::pi_0x2d(uint16_t args){
	_SRA(&registers.L);
}
void Z80::pi_0x2e(uint16_t args){
	uint8_t temp = (uint8_t) mem.read(registers.HL);
	_SRA(&temp);
	mem.write(registers.HL, temp);
}
void Z80::pi_0x2f(uint16_t args){
	_SRA(&registers.A);
}


/* SWAP */

void Z80::pi_0x30(uint16_t args){
	_SWAP(registers.B);
}
void Z80::pi_0x31(uint16_t args){
	_SWAP(registers.C);
}
void Z80::pi_0x32(uint16_t args){
	_SWAP(registers.D);
}
void Z80::pi_0x33(uint16_t args){
	_SWAP(registers.E);
}
void Z80::pi_0x34(uint16_t args){
	_SWAP(registers.H);
}
void Z80::pi_0x35(uint16_t args){
	_SWAP(registers.L);
}
void Z80::pi_0x36(uint16_t args){
	uint8_t temp = mem.read(registers.HL);
	_SWAP(temp);
	mem.write(registers.HL, temp);
}
void Z80::pi_0x37(uint16_t args){
	_SWAP(registers.A);
}

void Z80::pi_0x38(uint16_t args){
	_SRL(&registers.B);
}
void Z80::pi_0x39(uint16_t args){
	_SRL(&registers.C);
}
void Z80::pi_0x3a(uint16_t args){
	_SRL(&registers.D);
}
void Z80::pi_0x3b(uint16_t args){
	_SRL(&registers.E);
}
void Z80::pi_0x3c(uint16_t args){
	_SRL(&registers.H);
}
void Z80::pi_0x3d(uint16_t args){
	_SRL(&registers.L);
}
void Z80::pi_0x3e(uint16_t args){
	uint8_t temp = (uint8_t) mem.read(registers.HL);
	_SRL(&temp);
	mem.write(registers.HL, temp);
}
void Z80::pi_0x3f(uint16_t args){
	_SRL(&registers.A);
}

void Z80::pi_0x40(uint16_t args){
	_BIT(0, registers.B);
}
void Z80::pi_0x41(uint16_t args){
	_BIT(0, registers.C);
}
void Z80::pi_0x42(uint16_t args){
	_BIT(0, registers.D);
}
void Z80::pi_0x43(uint16_t args){
	_BIT(0, registers.E);
}
void Z80::pi_0x44(uint16_t args){
	_BIT(0, registers.H);
}
void Z80::pi_0x45(uint16_t args){
	_BIT(0, registers.L);
}
void Z80::pi_0x46(uint16_t args){
	_BIT(0, mem.read(registers.HL));
}
void Z80::pi_0x47(uint16_t args){
	_BIT(0, registers.A);
}

void Z80::pi_0x48(uint16_t args){
	_BIT(1, registers.B);
}
void Z80::pi_0x49(uint16_t args){
	_BIT(1, registers.C);
}
void Z80::pi_0x4a(uint16_t args){
	_BIT(1, registers.D);
}
void Z80::pi_0x4b(uint16_t args){
	_BIT(1, registers.E);
}
void Z80::pi_0x4c(uint16_t args){
	_BIT(1, registers.H);
}
void Z80::pi_0x4d(uint16_t args){
	_BIT(1, registers.L);
}
void Z80::pi_0x4e(uint16_t args){
	_BIT(1, mem.read(registers.HL));
}
void Z80::pi_0x4f(uint16_t args){
	_BIT(1, registers.A);
}


void Z80::pi_0x50(uint16_t args){
	_BIT(2, registers.B);
}
void Z80::pi_0x51(uint16_t args){
	_BIT(2, registers.C);
}
void Z80::pi_0x52(uint16_t args){
	_BIT(2, registers.D);
}
void Z80::pi_0x53(uint16_t args){
	_BIT(2, registers.E);
}
void Z80::pi_0x54(uint16_t args){
	_BIT(2, registers.H);
}
void Z80::pi_0x55(uint16_t args){
	_BIT(2, registers.L);
}
void Z80::pi_0x56(uint16_t args){
	_BIT(2, mem.read(registers.HL));
}
void Z80::pi_0x57(uint16_t args){
	_BIT(2, registers.A);
}

void Z80::pi_0x58(uint16_t args){
	_BIT(3, registers.B);
}
void Z80::pi_0x59(uint16_t args){
	_BIT(3, registers.C);
}
void Z80::pi_0x5a(uint16_t args){
	_BIT(3, registers.D);
}
void Z80::pi_0x5b(uint16_t args){
	_BIT(3, registers.E);
}
void Z80::pi_0x5c(uint16_t args){
	_BIT(3, registers.H);
}
void Z80::pi_0x5d(uint16_t args){
	_BIT(3, registers.L);
}
void Z80::pi_0x5e(uint16_t args){
	_BIT(3, mem.read(registers.HL));
}
void Z80::pi_0x5f(uint16_t args){
	_BIT(3, registers.A);
}

void Z80::pi_0x60(uint16_t args){
	_BIT(4, registers.B);
}
void Z80::pi_0x61(uint16_t args){
	_BIT(4, registers.C);
}
void Z80::pi_0x62(uint16_t args){
	_BIT(4, registers.D);
}
void Z80::pi_0x63(uint16_t args){
	_BIT(4, registers.E);
}
void Z80::pi_0x64(uint16_t args){
	_BIT(4, registers.H);
}
void Z80::pi_0x65(uint16_t args){
	_BIT(4, registers.L);
}
void Z80::pi_0x66(uint16_t args){
	_BIT(4, mem.read(registers.HL));
}
void Z80::pi_0x67(uint16_t args){
	_BIT(4, registers.A);
}

void Z80::pi_0x68(uint16_t args){
	_BIT(5, registers.B);
}
void Z80::pi_0x69(uint16_t args){
	_BIT(5, registers.C);
}
void Z80::pi_0x6a(uint16_t args){
	_BIT(5, registers.D);
}
void Z80::pi_0x6b(uint16_t args){
	_BIT(5, registers.E);
}
void Z80::pi_0x6c(uint16_t args){
	_BIT(5, registers.H);
}
void Z80::pi_0x6d(uint16_t args){
	_BIT(5, registers.L);
}
void Z80::pi_0x6e(uint16_t args){
	_BIT(5, mem.read(registers.HL));
}
void Z80::pi_0x6f(uint16_t args){
	_BIT(5, registers.A);
}

void Z80::pi_0x70(uint16_t args){
	_BIT(6, registers.B);
}
void Z80::pi_0x71(uint16_t args){
	_BIT(6, registers.C);
}
void Z80::pi_0x72(uint16_t args){
	_BIT(6, registers.D);
}
void Z80::pi_0x73(uint16_t args){
	_BIT(6, registers.E);
}
void Z80::pi_0x74(uint16_t args){
	_BIT(6, registers.H);
}
void Z80::pi_0x75(uint16_t args){
	_BIT(6, registers.L);
}
void Z80::pi_0x76(uint16_t args){
	_BIT(6, mem.read(registers.HL));
}
void Z80::pi_0x77(uint16_t args){
	_BIT(6, registers.A);
}

void Z80::pi_0x78(uint16_t args){
	_BIT(7, registers.B);
}
void Z80::pi_0x79(uint16_t args){
	_BIT(7, registers.C);
}
void Z80::pi_0x7a(uint16_t args){
	_BIT(7, registers.D);
}
void Z80::pi_0x7b(uint16_t args){
	_BIT(7, registers.E);
}
void Z80::pi_0x7c(uint16_t args){
	_BIT(7, registers.H);
}
void Z80::pi_0x7d(uint16_t args){
	_BIT(7, registers.L);
}
void Z80::pi_0x7e(uint16_t args){
	_BIT(7, mem.read(registers.HL));
}
void Z80::pi_0x7f(uint16_t args){
	_BIT(7, registers.A);
}

void Z80::pi_0x80(uint16_t args){
	_RES(0, &registers.B);
}
void Z80::pi_0x81(uint16_t args){
	_RES(0, &registers.C);
}
void Z80::pi_0x82(uint16_t args){
	_RES(0, &registers.D);
}
void Z80::pi_0x83(uint16_t args){
	_RES(0, &registers.E);
}
void Z80::pi_0x84(uint16_t args){
	_RES(0, &registers.H);
}
void Z80::pi_0x85(uint16_t args){
	_RES(0, &registers.L);
}
void Z80::pi_0x86(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp & (~(0x01 << 0)));
}
void Z80::pi_0x87(uint16_t args){
	_RES(0, &registers.A);
}

void Z80::pi_0x88(uint16_t args){
	_RES(1, &registers.B);
}
void Z80::pi_0x89(uint16_t args){
	_RES(1, &registers.C);
}
void Z80::pi_0x8a(uint16_t args){
	_RES(1, &registers.D);
}
void Z80::pi_0x8b(uint16_t args){
	_RES(1, &registers.E);
}
void Z80::pi_0x8c(uint16_t args){
	_RES(1, &registers.H);
}
void Z80::pi_0x8d(uint16_t args){
	_RES(1, &registers.L);
}
void Z80::pi_0x8e(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp & (~(0x01 << 1)));
}
void Z80::pi_0x8f(uint16_t args){
	_RES(1, &registers.A);
}

void Z80::pi_0x90(uint16_t args){
	_RES(2, &registers.B);
}
void Z80::pi_0x91(uint16_t args){
	_RES(2, &registers.C);
}
void Z80::pi_0x92(uint16_t args){
	_RES(2, &registers.D);
}
void Z80::pi_0x93(uint16_t args){
	_RES(2, &registers.E);
}
void Z80::pi_0x94(uint16_t args){
	_RES(2, &registers.H);
}
void Z80::pi_0x95(uint16_t args){
	_RES(2, &registers.L);
}
void Z80::pi_0x96(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp & (~(0x01 << 2)));
}
void Z80::pi_0x97(uint16_t args){
	_RES(2, &registers.A);
}

void Z80::pi_0x98(uint16_t args){
	_RES(3, &registers.B);
}
void Z80::pi_0x99(uint16_t args){
	_RES(3, &registers.C);
}
void Z80::pi_0x9a(uint16_t args){
	_RES(3, &registers.D);
}
void Z80::pi_0x9b(uint16_t args){
	_RES(3, &registers.E);
}
void Z80::pi_0x9c(uint16_t args){
	_RES(3, &registers.H);
}
void Z80::pi_0x9d(uint16_t args){
	_RES(3, &registers.L);
}
void Z80::pi_0x9e(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp & (~(0x01 << 3)));
}
void Z80::pi_0x9f(uint16_t args){
	_RES(3, &registers.A);
}

void Z80::pi_0xa0(uint16_t args){
	_RES(4, &registers.B);
}
void Z80::pi_0xa1(uint16_t args){
	_RES(4, &registers.C);
}
void Z80::pi_0xa2(uint16_t args){
	_RES(4, &registers.D);
}
void Z80::pi_0xa3(uint16_t args){
	_RES(4, &registers.E);
}
void Z80::pi_0xa4(uint16_t args){
	_RES(4, &registers.H);
}
void Z80::pi_0xa5(uint16_t args){
	_RES(4, &registers.L);
}
void Z80::pi_0xa6(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp & (~(0x01 << 4)));
}
void Z80::pi_0xa7(uint16_t args){
	_RES(4, &registers.A);
}


void Z80::pi_0xa8(uint16_t args){
	_RES(5, &registers.B);
}
void Z80::pi_0xa9(uint16_t args){
	_RES(5, &registers.C);
}
void Z80::pi_0xaa(uint16_t args){
	_RES(5, &registers.D);
}
void Z80::pi_0xab(uint16_t args){
	_RES(5, &registers.E);
}
void Z80::pi_0xac(uint16_t args){
	_RES(5, &registers.H);
}
void Z80::pi_0xad(uint16_t args){
	_RES(5, &registers.L);
}
void Z80::pi_0xae(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp & (~(0x01 << 5)));
}
void Z80::pi_0xaf(uint16_t args){
	_RES(5, &registers.A);
}


void Z80::pi_0xb0(uint16_t args){
	_RES(6, &registers.B);
}
void Z80::pi_0xb1(uint16_t args){
	_RES(6, &registers.C);
}
void Z80::pi_0xb2(uint16_t args){
	_RES(6, &registers.D);
}
void Z80::pi_0xb3(uint16_t args){
	_RES(6, &registers.E);
}
void Z80::pi_0xb4(uint16_t args){
	_RES(6, &registers.H);
}
void Z80::pi_0xb5(uint16_t args){
	_RES(6, &registers.L);
}
void Z80::pi_0xb6(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp & (~(0x01 << 6)));
}
void Z80::pi_0xb7(uint16_t args){
	_RES(6, &registers.A);
}


void Z80::pi_0xb8(uint16_t args){
	_RES(7, &registers.B);
}
void Z80::pi_0xb9(uint16_t args){
	_RES(7, &registers.C);
}
void Z80::pi_0xba(uint16_t args){
	_RES(7, &registers.D);
}
void Z80::pi_0xbb(uint16_t args){
	_RES(7, &registers.E);
}
void Z80::pi_0xbc(uint16_t args){
	_RES(7, &registers.H);
}
void Z80::pi_0xbd(uint16_t args){
	_RES(7, &registers.L);
}
void Z80::pi_0xbe(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp & (~(0x01 << 7)));
}
void Z80::pi_0xbf(uint16_t args){
	_RES(7, &registers.A);
}

void Z80::pi_0xc0(uint16_t args){
	_SET(0, &registers.B);
}
void Z80::pi_0xc1(uint16_t args){
	_SET(0, &registers.C);
}
void Z80::pi_0xc2(uint16_t args){
	_SET(0, &registers.D);
}
void Z80::pi_0xc3(uint16_t args){
	_SET(0, &registers.E);
}
void Z80::pi_0xc4(uint16_t args){
	_SET(0, &registers.H);
}
void Z80::pi_0xc5(uint16_t args){
	_SET(0, &registers.L);
}
void Z80::pi_0xc6(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp | (0x01 << 0));
}
void Z80::pi_0xc7(uint16_t args){
	_SET(0, &registers.A);
}

void Z80::pi_0xc8(uint16_t args){
	_SET(1, &registers.B);
}
void Z80::pi_0xc9(uint16_t args){
	_SET(1, &registers.C);
}
void Z80::pi_0xca(uint16_t args){
	_SET(1, &registers.D);
}
void Z80::pi_0xcb(uint16_t args){
	_SET(1, &registers.E);
}
void Z80::pi_0xcc(uint16_t args){
	_SET(1, &registers.H);
}
void Z80::pi_0xcd(uint16_t args){
	_SET(1, &registers.L);
}
void Z80::pi_0xce(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp | (0x01 << 1));
}
void Z80::pi_0xcf(uint16_t args){
	_SET(1, &registers.A);
}


void Z80::pi_0xd0(uint16_t args){
	_SET(2, &registers.B);
}
void Z80::pi_0xd1(uint16_t args){
	_SET(2, &registers.C);
}
void Z80::pi_0xd2(uint16_t args){
	_SET(2, &registers.D);
}
void Z80::pi_0xd3(uint16_t args){
	_SET(2, &registers.E);
}
void Z80::pi_0xd4(uint16_t args){
	_SET(2, &registers.H);
}
void Z80::pi_0xd5(uint16_t args){
	_SET(2, &registers.L);
}
void Z80::pi_0xd6(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp | (0x01 << 2));
}
void Z80::pi_0xd7(uint16_t args){
	_SET(2, &registers.A);
}


void Z80::pi_0xd8(uint16_t args){
	_SET(3, &registers.B);
}
void Z80::pi_0xd9(uint16_t args){
	_SET(3, &registers.C);
}
void Z80::pi_0xda(uint16_t args){
	_SET(3, &registers.D);
}
void Z80::pi_0xdb(uint16_t args){
	_SET(3, &registers.E);
}
void Z80::pi_0xdc(uint16_t args){
	_SET(3, &registers.H);
}
void Z80::pi_0xdd(uint16_t args){
	_SET(3, &registers.L);
}
void Z80::pi_0xde(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp | (0x01 << 3));
}
void Z80::pi_0xdf(uint16_t args){
	_SET(3, &registers.A);
}


void Z80::pi_0xe0(uint16_t args){
	_SET(4, &registers.B);
}
void Z80::pi_0xe1(uint16_t args){
	_SET(4, &registers.C);
}
void Z80::pi_0xe2(uint16_t args){
	_SET(4, &registers.D);
}
void Z80::pi_0xe3(uint16_t args){
	_SET(4, &registers.E);
}
void Z80::pi_0xe4(uint16_t args){
	_SET(4, &registers.H);
}
void Z80::pi_0xe5(uint16_t args){
	_SET(4, &registers.L);
}
void Z80::pi_0xe6(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp | (0x01 << 4));
}
void Z80::pi_0xe7(uint16_t args){
	_SET(4, &registers.A);
}


void Z80::pi_0xe8(uint16_t args){
	_SET(5, &registers.B);
}
void Z80::pi_0xe9(uint16_t args){
	_SET(5, &registers.C);
}
void Z80::pi_0xea(uint16_t args){
	_SET(5, &registers.D);
}
void Z80::pi_0xeb(uint16_t args){
	_SET(5, &registers.E);
}
void Z80::pi_0xec(uint16_t args){
	_SET(5, &registers.H);
}
void Z80::pi_0xed(uint16_t args){
	_SET(5, &registers.L);
}
void Z80::pi_0xee(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp | (0x01 << 5));
}
void Z80::pi_0xef(uint16_t args){
	_SET(5, &registers.A);
}


void Z80::pi_0xf0(uint16_t args){
	_SET(6, &registers.B);
}
void Z80::pi_0xf1(uint16_t args){
	_SET(6, &registers.C);
}
void Z80::pi_0xf2(uint16_t args){
	_SET(6, &registers.D);
}
void Z80::pi_0xf3(uint16_t args){
	_SET(6, &registers.E);
}
void Z80::pi_0xf4(uint16_t args){
	_SET(6, &registers.H);
}
void Z80::pi_0xf5(uint16_t args){
	_SET(6, &registers.L);
}
void Z80::pi_0xf6(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp | (0x01 << 6));
}
void Z80::pi_0xf7(uint16_t args){
	_SET(6, &registers.A);
}

void Z80::pi_0xf8(uint16_t args){
	_SET(7, &registers.B);
}
void Z80::pi_0xf9(uint16_t args){
	_SET(7, &registers.C);
}
void Z80::pi_0xfa(uint16_t args){
	_SET(7, &registers.D);
}
void Z80::pi_0xfb(uint16_t args){
	_SET(7, &registers.E);
}
void Z80::pi_0xfc(uint16_t args){
	_SET(7, &registers.H);
}
void Z80::pi_0xfd(uint16_t args){
	_SET(7, &registers.L);
}
void Z80::pi_0xfe(uint16_t args){
	uint16_t temp = mem.read(registers.HL);
	mem.write(registers.HL, temp | (0x01 << 7));
}
void Z80::pi_0xff(uint16_t args){
	_SET(7, &registers.A);
}
