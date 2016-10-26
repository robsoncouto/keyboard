
#define F_CPU 16000000UL

#include<avr/io.h>
#include"keys.h"
#include"sn76489.h"
#include"serial/uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdlib.h>
#include<string.h>


void initHardware(void){
  //IO
  CTRLDDR=(1<<SNWR)|(1<<SNEN)|(1<<SNCLKIN)|(0<<SNRDY);
  CTRLPORT=(1<<SNWR)|(1<<SNEN)|(1<<SNCLKIN);

  LINESDDR=0xFF;//
  COLSDDR=0x02;//
  COLSPORT=0x00;

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
void scanKeys(uint8_t* notes,uint8_t size){
  uint8_t count=0;
  uint8_t key=1;

  memset(notes,0,size);

  LINESPORT=0x00;
  COLSPORT=0x00;
  for(uint8_t i=7;i!=0;i--){
    LINESPORT=(1<<i);
    for(uint8_t j=7;j!=0;j--){
      if(COLSPIN&(1<<j)){
        notes[count]=key;
        count++;
        if (count==size) {
          return;
        }

      }
      key++;

    }
  }
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
      return;
  }
  data|=(value>>2)&(0xF1);
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
      return;
  }

  writeData(data);
}

uint8_t channels[3];
uint8_t keys[10];
uint8_t keyPressed(uint8_t* data,uint8_t size){
  for(int i=0;i<size;i++){
    if(data[i]){
      return 1;
    }
  }
  return 0;
}

void printKeys(uint8_t* data, uint8_t size){
    uint8_t str[10];
  uart_puts("Keys pressed:\n");
  for (int i=0;i<size;i++){
    itoa(data[i],(char*)str,10);
    uart_puts("key:");
    uart_puts((char*)str);
    uart_putc('\n');
    memset(str,0,10);
  }
}

int main(void){
  DDRB=(1<<PINB3);
  uart_init(UART_BAUD_SELECT(9600,16000000UL));
  sei();
  initHardware();
  setupTimer();
  uint8_t str[20];
  while(1){
    scanKeys(keys,10);
    //check if keys still pressed
    if(keyPressed(keys,10)){
      for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 10; l++) {
          if(keys[l]==channels[k]){
            break;
          }

        }
        channels[k]=keys[k];
        //upadte channel
        changeFreq(k, codes[keys[k]+25]); //starting from C2
        uart_puts("code:");
        itoa(codes[keys[k]+25],(char*)str,2);
        uart_puts((char*)str);
        uart_putc('\n');
        memset(str,0,20);
      }
    }
    printKeys(keys,10);
    _delay_ms(1000);
  }
}
