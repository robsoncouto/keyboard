#ifndef sn76489_h
#define sn76489_h

#include"keys.h"

#define SNCLOCK 4000000 //4MHz

#define divider(a) (SNINCLOK/(32*a))

//registers

//frequency registers
#define FREQ1REG 0x00
#define FREQ2REG 0x02
#define FREQ3REG 0x04

//attenuation registers
#define ATT1REG 0x01
#define ATT2REG 0x03
#define ATT3REG 0x05

#define NOISECTRLREG 0x06
#define NOISEATTREG  0x07
#endif
