#ifndef keys_h
#define keys_h

//The keyboard uses a matrix of keys
//I consider lines the outputs and columms the inputs

#define NUMLINES 8
#define NUMCOLS  6

#define SNPORT PORTA
#define SNDDR PORTA

#define CTRLPORT PORTB
#define CTRLDDR DDRB

#define COLSPORT PORTD
#define COLSDDR DDRD

#define LINESPORT PORTD
#define LINESDDR DDRD
//FIXME correct numbers
#define SNWR 1
#define SNRDY 2
#define SNEN 3
#define SNCLKIN 3




#endif
