


#include<avr/io.h>
#include"keys.h"
#include"sn76489.h"


void initHardware(void){
  //IO
  CTRLDDR=(1<<SNWR)|(1<<SNEN)|(1<<SNCLKIN)|(0<<SNRDY);
  CTRLPORT=(1<<SNWR)|(1<<SNEN)|(1<<SNCLKIN);

  LINESDDR=0x00;//Inputs
  COLSDDR=0xFF;//Outpus

  //direction of the data port for the sn76489
  SNDDR=0xFF;
  SNPORT=0xFF;
}

void setupTimer(void){
  //A timer is used to generate a clock in one of the pins for the sn76489

  //CTC mode, toggle output on match, no prescalling
  TCCR0=(1<<FOC0)|(1<<WGM01)|(0<<WGM00);
  TCCR0|=(0<<COM01)|(1<<COM00)|(1<<CS00);
  OCR0=0x01;
}
uint8_t scanKeys(void){
  LINESPORT=0x00;
  COLSPORT=0x00;
}
void writeData(uint8_t data){
  //writes data to sn76489
  SNPORT = data;
  CTRLPORT&=~(1<<SNEN);
  CTRLPORT&=~(1<<SNWR);
  CTRLPORT=(1<<SNWR)|(1<<SNEN);
}
void changeFreq(uint8_t channel, uint16_t value){
  uint8_t data =0x01;
  switch (channel) {
    case 0x01: data|=(FREQ1REG<<1);
      break;
    case 0x02: data|=(FREQ2REG<<1);
      break;
    case 0x03: data|=(FREQ3REG<<1);
      break;
    default:
      return
  }
  data|=value>>6;
  writeData(data);
  data=0x00;
  data|=(value<<2);
  writeData(data);


}
void changeAttenuation(uint8_t channel, uint8_t value){
  uint8_t data =0x01;
  switch (channel) {
    case 0x01: data|=(ATT1REG<<1)|(value<<4);
      break;
    case 0x02: data|=(ATT2REG<<1)|(value<<4);
      break;
    case 0x03: data|=(ATT3REG<<1)|(value<<4);
      break;
    default:
      return
  }

  writeData(data);
}


int main(void){
  DDRB=(1<<PINB3);
  setupTimer();
  while(1){

  }
}
