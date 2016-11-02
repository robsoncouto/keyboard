
#define F_CPU 16000000UL

#include<avr/io.h>
#include"keys.h"
#include"sn76489.h"
#include"serial/uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdlib.h>
#include<string.h>

#ifdef DEBUG_ON
void print(int data) {
  char strin[10];
  memset(strin,0,10);
  uart_puts("print:");
  itoa(data,(char*)strin,16);
  uart_puts((char*)strin);
  uart_putc('\n');

}
#endif

void initHardware(void){
  //IO
  CTRLDDR=(1<<SNWR)|(1<<SNEN)|(1<<SNCLKIN)|(0<<SNRDY);
  CTRLPORT=(1<<SNWR)|(1<<SNEN)|(1<<SNCLKIN);

  LINESDDR=0xFF;//
  COLSDDR=0x02;//

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
  uint8_t count=0;//FIXME car**ho
  uint8_t key=48;
  LINESPORT=0x00;
  COLSPORT=0x00;
  memset(notes,0,size);
  for(uint8_t i=0;i<NUMLINES;i++){
    LINESPORT=(1<<i);
    _delay_ms(1);
    for(uint8_t j=2;j<NUMCOLS;j++){
      if(COLSPIN&(1<<j)){
        notes[count]=key;
        count++;
        if (count==size) {
          return;
        }
      }
      key--;

    }
  }
}
//this is necessary to reverse a byte on PORTA,  just so I don't have to desolder
//everything and solder again. Pin 0 shold be connected to 0, but I connected to 7
//and so on...
uint8_t reverse(uint8_t data){
  uint8_t reversed = data;
  reversed=((reversed&0xAA)>>1) | ((reversed&0x55)<<1);
  reversed=((reversed&0xCC)>>2) | ((reversed&0x33)<<2);
  reversed=((reversed&0xF0)>>4) | ((reversed&0x0F)<<4);
  return reversed;
}
void writeData(uint8_t data){
  //writes data to sn76489
  SNPORT = reverse(data); //I messed up my circuit and connected 7 to 0, 6 to  1, and so on...
  CTRLPORT&=~(1<<SNEN);
  CTRLPORT&=~(1<<SNWR);
  _delay_ms(1);
  CTRLPORT=(1<<SNWR)|(1<<SNEN);
}
/*The existing datasheets can be pretty confusing. I have rewritten
the following function many times.Trusty info can be found at:
http://www.smspower.org/Development/SN76489
http://www.primrosebank.net/computers/mtx/projects/mtxplus/data/SN76489.pdf
*/

void changeFreq(uint8_t channel, uint16_t value){
  uint8_t data =0x80;
  switch (channel) {
    case 0x00: data|=(FREQ1REG<<4);
      break;
    case 0x01: data|=(FREQ2REG<<4);
      break;
    case 0x03: data|=(FREQ3REG<<4);
      break;
    default:
      return;
  }
  data|=(value&0x0F);
  writeData(data);
  data=0x00;
  data|=(value>>4)&0x3F;
  writeData(data);

}
void changeAttenuation(uint8_t channel, uint8_t value){
  uint8_t data =0x80;
  switch (channel) {
    case 0x00: data|=(ATT1REG<<4)|(value&0x0F);
      break;
    case 0x01: data|=(ATT2REG<<4)|(value&0x0F);
      break;
    case 0x02: data|=(ATT3REG<<4)|(value&0x0F);
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

#ifdef DEBUG_ON
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
#endif

void updateChannels(uint8_t *keys,uint8_t size){
  uint8_t skip_flag=0; //If the key was already hit last time, keep it
  for (int k = 0; k < 3; k++) {
    for (int l = 0; l < size; l++) {
      if(channels[k]==keys[l]){
        if(channels[k]!=0){
          skip_flag=1;
          #ifdef DEBUG_ON
          uart_puts("skipped\n");
          print(k);
          uart_putc('\n');
          #endif
          break;
        }
      }
    }
    if (!skip_flag) { //don't need to process if the key was already pressed
      if(keys[k]!=0){
        channels[k]=keys[k];

        changeFreq(k, codes[channels[k]+24]); //starting from C2
        changeAttenuation(k,0x00);
        #ifdef DEBUG_ON
        uart_puts("(pressed) channel:");
        print(k);
        uart_putc('\n');
        #endif
        _delay_ms(1);

      }else{
        #ifdef DEBUG_ON
        uart_puts("(Not pressed)channel:");
        print(k);
        #endif
        changeFreq(k, 0x0000);
        changeAttenuation(k,0x0F);
        channels[k]=0;

      }
    }
    skip_flag=0;
  }
}


int main(void){
  uart_init(UART_BAUD_SELECT(9600,16000000UL));
  sei();
  initHardware();
  setupTimer();

  changeAttenuation(1,0x0F);
  changeAttenuation(2,0x0F);
  changeAttenuation(3,0x0F);

  _delay_ms(10);
  uint8_t prevkey;
  prevkey=0;
  while(1){
    scanKeys(keys,10);
    updateChannels(keys,10);
    // if(keys[0]!=prevkey){
    //   changeAttenuation(1,0x00);
    //   changeAttenuation(2,0x0F);
    //   changeAttenuation(3,0x0F);
    //   changeFreq(1, codes[keys[0]+24]);
    //   prevkey=keys[0];
    // }
    // if ((keys[0]>48)||(keys[0]<1)) {
    //   changeAttenuation(1,0x0F);
    //   changeAttenuation(2,0x0F);
    //   changeAttenuation(3,0x0F);
    // }
    //printKeys(keys,10);
    //_delay_ms(1000);
  }
}
