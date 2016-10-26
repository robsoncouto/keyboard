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
#define NOISEATTREG 0x07
#endif

#define regfreq SNCLOCK/32 //f = N / 32n , N/32 frequency without division

#define BASE 26
//values of n
uint16_t codes[]={
 regfreq/NOTE_C0,
 regfreq/NOTE_CS0,
 regfreq/NOTE_CS0,
 regfreq/NOTE_D0,
 regfreq/NOTE_DS0,
 regfreq/NOTE_E0,
 regfreq/NOTE_F0,
 regfreq/NOTE_FS0,
 regfreq/NOTE_G0,
 regfreq/NOTE_GS0,
 regfreq/NOTE_A0,
 regfreq/NOTE_AS0,
 regfreq/NOTE_B0,
 regfreq/NOTE_C1,
 regfreq/NOTE_CS1,
 regfreq/NOTE_D1,
 regfreq/NOTE_DS1,
 regfreq/NOTE_E1,
 regfreq/NOTE_F1,
 regfreq/NOTE_FS1,
 regfreq/NOTE_G1,
 regfreq/NOTE_GS1,
 regfreq/NOTE_A1,
 regfreq/NOTE_AS1,
 regfreq/NOTE_B1,
 regfreq/NOTE_C2,
 regfreq/NOTE_CS2,
 regfreq/NOTE_D2,
 regfreq/NOTE_DS2,
 regfreq/NOTE_E2,
 regfreq/NOTE_F2,
 regfreq/NOTE_FS2,
 regfreq/NOTE_G2,
 regfreq/NOTE_GS2,
 regfreq/NOTE_A2,
 regfreq/NOTE_AS2,
 regfreq/NOTE_B2,
 regfreq/NOTE_C3,
 regfreq/NOTE_CS3,
 regfreq/NOTE_D3,
 regfreq/NOTE_DS3,
 regfreq/NOTE_E3,
 regfreq/NOTE_F3,
 regfreq/NOTE_FS3,
 regfreq/NOTE_G3,
 regfreq/NOTE_GS3,
 regfreq/NOTE_A3,
 regfreq/NOTE_AS3,
 regfreq/NOTE_B3,
 regfreq/NOTE_C4,
 regfreq/NOTE_CS4,
 regfreq/NOTE_D4,
 regfreq/NOTE_DS4,
 regfreq/NOTE_E4,
 regfreq/NOTE_F4,
 regfreq/NOTE_FS4,
 regfreq/NOTE_G4,
 regfreq/NOTE_GS4,
 regfreq/NOTE_A4,
 regfreq/NOTE_B4,
 regfreq/NOTE_C5,
 regfreq/NOTE_CS5,
 regfreq/NOTE_D5,
 regfreq/NOTE_DS5,
 regfreq/NOTE_E5,
 regfreq/NOTE_F5,
 regfreq/NOTE_FS5,
 regfreq/NOTE_G5,
 regfreq/NOTE_GS5,
 regfreq/NOTE_A5,
 regfreq/NOTE_AS5,
 regfreq/NOTE_B5,
 regfreq/NOTE_C6,
 regfreq/NOTE_CS6,
 regfreq/NOTE_D6,
 regfreq/NOTE_DS6,
 regfreq/NOTE_E6,
 regfreq/NOTE_F6,
 regfreq/NOTE_FS6,
 regfreq/NOTE_G6,
 regfreq/NOTE_GS6,
 regfreq/NOTE_A6,
 regfreq/NOTE_AS6,
 regfreq/NOTE_B6,
 regfreq/NOTE_C7,
 regfreq/NOTE_CS7,
 regfreq/NOTE_D7,
 regfreq/NOTE_DS7,
 regfreq/NOTE_E7,
 regfreq/NOTE_F7,
 regfreq/NOTE_FS7,
 regfreq/NOTE_G7,
 regfreq/NOTE_GS7,
 regfreq/NOTE_A7,
 regfreq/NOTE_AS7,
 regfreq/NOTE_B7,
 regfreq/NOTE_C8,
 regfreq/NOTE_CS8,
 regfreq/NOTE_D8,
 regfreq/NOTE_DS8,
 regfreq/NOTE_E8,
 regfreq/NOTE_F8,
 regfreq/NOTE_FS8,
 regfreq/NOTE_G8,
 regfreq/NOTE_GS8,
 regfreq/NOTE_A8,
 regfreq/NOTE_AS8,
 regfreq/NOTE_B8};
