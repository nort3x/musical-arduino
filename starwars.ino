/*written by w0lfic : github.com/nort3x , under GPL3 have fun*/



/*
connect pin9 and gnd of atmega32 to signal input of your speaker and enjoy starwars music :D
*/



// includes
#include "starwarmusic.h"
#define OUT 9          // output pin


// constants
const int numberOfNotes =36 ; // number of steps

//functions
inline void Set_frequency(long);



void setup() {
  
  Serial.begin(9600); // for Com
  pinMode(OUT,OUTPUT); // set pin to output mode
}


void loop() {
  digitalWrite(OUT,HIGH);
  for(int i=0;i<numberOfNotes;++i){
        Set_frequency(mNotes[i]);
        delay(mTimes[i]);
    }
Set_frequency(100000);
    delay(1000);
}



// will tweak duty cycle by overriding default clock
 void Set_frequency(long freq)
{
  
  TCCR1A = 0b01000000; //64
  uint16_t ocr;
  
  if(freq < 134) 
  {
    TCCR1B = 0b00001010; 
    ocr = 1000000UL/freq - 1;
    freq = 1000000UL/(ocr+1);
  }
  
  else 
  {
    TCCR1B = 0b00001001;
    ocr = 8000000UL/freq - 1;
    freq = 8000000UL/(ocr+1);
  }
  
  OCR1AH = highByte(ocr);
  OCR1AL = lowByte(ocr);
  TIMSK1 = 0;
}
