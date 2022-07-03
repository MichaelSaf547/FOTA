#ifndef BITS_H_
#define BITS_H_

#define SET_BIT(Reg,bit) Reg|=(1<<bit)
#define CLR_BIT(Reg,bit) Reg&=(~(1<<bit))
#define GET_BIT(Reg,bit) ((Reg>>bit)&1)
#define TGL_BIT(Reg,bit) Reg^=(1<<bit)
#define RSHFT_REG(Reg,No) Reg>>=No
#define LSHFT_REG(Reg,No) Reg<<=No
#define CRSHFT_REG(Reg,No) Reg=((Reg>>No)|(Reg<<(8-No)))
#define CLSHFT_REG(Reg,No) Reg=((Reg<<No)|(Reg>>(8-No)))
#define ASSIGN_REG(Reg,Val) Reg=Val
#define SET_REG(Reg) Reg=255
#define CLR_REG(Reg) Reg=0
#define TGL_REG(Reg) Reg=~Reg
#define SET_H_NIB(Reg) Reg|=240
#define SET_L_NIB(Reg) Reg|=15
#define CLR_H_NIB(Reg) Reg&=15
#define CLR_L_NIB(Reg) Reg&=240
#define GET_H_NIB(Reg) ((Reg>>4)&15)
#define GET_L_NIB(Reg) (Reg&15)
#define ASSIGN_H_NIB(Reg,value) Reg=(Reg&15)|(value<<4)
#define ASSIGN_L_NIB(Reg,value) Reg=(Reg&240)|(value)
#define TGL_H_NIB(Reg) Reg^=240
#define TGL_L_NIB(Reg) Reg^=15
#define SWAP_NIB(Reg) Reg=((Reg<<4)|(Reg>>4))

typedef unsigned char u8;
typedef unsigned char* pu8;
typedef signed char s8;
typedef signed char* ps8;
typedef unsigned short int u16;
typedef unsigned short int* pu16;
typedef signed short int s16;
typedef signed short int* ps16;
typedef unsigned long int u32;
typedef unsigned long int* pu32;
typedef signed long int s32;
typedef signed long int* ps32;
typedef unsigned long long int u64;
typedef unsigned long long int* pu64;
typedef signed long long int s64;
typedef signed long long int* ps64;
typedef float f32;
typedef double f64;
typedef long double f128;


#endif
