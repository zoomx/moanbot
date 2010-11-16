#include <avr/interrupt.h>
#include "Moanbot.h"
#include "WaveHC.h"

/*
 This file contains sections from WaveHC by William Greiman and Ladyada.
 It has been modified to use the on-chip PWM instead of an external DAC.
 
 William Greiman's modified version of Ladyada's wave shield library
 I have made many changes that may have introduced bugs.  Major changes are:
 optimized DAC macros to allow 44.1 k 16-bit files
 use of FatReader to read FAT32 and FAT16 files
 modified readwavhack to be readWaveData
 use standard SD and SDHC flash cards.
 skip non-data chunks after fmt chunk
 allow 18 byte format chunk if no compression
 play stereo as mono by interleaving channels
 change method of reading fmt chunk - use union of structs
*/

MoanbotClass Moanbot;
SdReader card;
FatVolume vol;
FatReader root;
WaveHC wave;

#define LED_MOUTH_TOP_1  (0x31)
#define LED_MOUTH_TOP_2  (0x91)
#define LED_MOUTH_TOP_3  (0x62)
#define LED_MOUTH_TOP_4  (0x64)
#define LED_MOUTH_BOT_1  (0x51)
#define LED_MOUTH_BOT_2  (0x32)
#define LED_MOUTH_BOT_3  (0xA2)
#define LED_MOUTH_BOT_4  (0x54)
#define LED_HAT          (0xC4)
#define LED_NOSE_R       (0xA8)
#define LED_NOSE_G       (0xC8)
#define LED_NOSE_B       (0x98)
#define LED_NONE         (0x00)

uint8_t ledRoster[LEDMAP_LEN]={
  LED_MOUTH_TOP_1, LED_MOUTH_TOP_2, LED_MOUTH_TOP_3, LED_MOUTH_TOP_4,
  LED_MOUTH_BOT_1, LED_MOUTH_BOT_2, LED_MOUTH_BOT_3, LED_MOUTH_BOT_4,
  LED_HAT, LED_NOSE_R, LED_NOSE_G, LED_NOSE_B
};
uint8_t ledDwellTime[LEDMAP_LEN]={
  3,3,3,3,3,3,3,3,15,1,1,1
};

void MoanbotClass::begin() {
  //TCCR2A = _BV(COM2A1) | _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);// Set up Timer 2 to 62kHz PWM
  //TCCR2A = _BV(COM2B1) | _BV(WGM20);// Set up Timer 2 to 31kHz PWM

  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);// Set up Timer 2 to 62kHz PWM
  TCCR2B = _BV(CS20);
  OCR2B = 0x00;
  DDRD |= _BV(3);
  // Timer 2 interrupt drives LED matrix
  TIMSK2 = _BV(TOIE2);

  mouthCustom(0,0,0,0,0,0,0,0);
  nose(1);
  hat(0);
  
  // Initialise SD card
  if (!card.init()) {for(;;);}
  nose(2);
  card.partialBlockRead(true);
  nose(3);
  uint8_t part;
  for (part=0; part<5; part++) if (vol.init(card,part)) break; // CRASH
  nose(4);
  if (part==5) {
    //Serial.println("No valid FAT partition");
    while(1);
  }
  nose(5);
  if (!root.openRoot(vol)) {
    //Serial.println("Could not open root dir");
    while(1);
  }
  nose(6);
  
  //if (fatvol.init(card)) {nose(2); for (;;);}
  //if (root.openRoot(fatvol)) {nose(3); for (;;);}
}
void MoanbotClass::mouthHappy() {
  mouthCustom(3,0,0,3,0,3,3,0);
}
void MoanbotClass::mouthSad() {
  mouthCustom(0,3,3,0,3,0,0,3);
}
void MoanbotClass::mouthFlat() {
  mouthCustom(0,0,0,0,3,3,3,3);
}
void MoanbotClass::mouthRipple() {
  mouthCustom(3,0,3,0,0,3,0,3);
};
void MoanbotClass::mouthCustom(
  uint8_t a,uint8_t b,uint8_t c,uint8_t d,
  uint8_t e,uint8_t f,uint8_t g,uint8_t h
) {
  ledDwellTime[0]=a;
  ledDwellTime[1]=b;
  ledDwellTime[2]=c;
  ledDwellTime[3]=d;
  ledDwellTime[4]=e;
  ledDwellTime[5]=f;
  ledDwellTime[6]=g;
  ledDwellTime[7]=h;
};
void MoanbotClass::hat(uint8_t a) {
  ledDwellTime[8]=a;
}
void MoanbotClass::nose(uint8_t a){
  ledDwellTime[9]=(a & 1)?1:0;
  ledDwellTime[10]=(a & 2)?1:0;
  ledDwellTime[11]=(a & 4)?1:0;
}

uint16_t MoanbotClass::tempReadLeft() {
  ADMUX = _BV(REFS0) | _BV(MUX1);
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC));
  return ADCW;
}

uint16_t MoanbotClass::tempReadRight() {
  ADMUX = _BV(REFS0) | _BV(MUX1) | _BV(MUX0);
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC));
  return ADCW;
}
uint16_t MoanbotClass::lightReadLeft() {
  ADMUX = _BV(REFS0);
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC));
  return ADCW;
}
uint16_t MoanbotClass::lightReadRight() {
  ADMUX = _BV(REFS0) | _BV(MUX0);
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC));
  return ADCW;
}
//char filename[]="0000.WAV";
uint8_t MoanbotClass::play(uint16_t a) {
  char filename[13];
  char *f=filename;
  *f++='0'+(a/1000); a = a % 1000;
  *f++='0'+(a/100); a = a % 100;
  *f++='0'+(a/10); a = a % 10;
  *f++='0'+a;
  *f++='.';
  *f++='W';
  *f++='A';
  *f++='V';
  *f=0;
  FatReader file;
    
  if (wave.isplaying) wave.stop();
  if (!file.open(root,filename)) return 1;
  if (!wave.create(file)) return 2;
  wave.play();
  while(wave.isplaying);
  if (card.errorCode()) return 3;
  return 0;
};
uint8_t MoanbotClass::tilt() {
  DDRD |= _BV(4);
  PORTD |= _BV(4);
  return (PIND & _BV(4)) ? 1:0;
}
SIGNAL(TIMER2_OVF_vect) {
  static uint8_t ledPosn=0;
  static uint8_t ledDwell=0;
  if (ledDwell) {
    ledDwell--;
  } else {
    uint8_t bitfield;

    ledDwell = ledDwellTime[ledPosn];
    bitfield = ledDwell ? ledRoster[ledPosn] : 0;
    if (ledDwell) ledDwell--;

    PORTB &= ~(_BV(1) | _BV(0));  PORTD &= ~(_BV(7) | _BV(6));
    DDRB &= ~(_BV(1) | _BV(0));  DDRD &= ~(_BV(7) | _BV(6));
    if (bitfield & _BV(7)) DDRB |= _BV(1);
    if (bitfield & _BV(6)) DDRB |= _BV(0);
    if (bitfield & _BV(5)) DDRD |= _BV(7);
    if (bitfield & _BV(4)) DDRD |= _BV(6);
    if (bitfield & _BV(3)) PORTB |= _BV(1);
    if (bitfield & _BV(2)) PORTB |= _BV(0);
    if (bitfield & _BV(1)) PORTD |= _BV(7);
    if (bitfield & _BV(0)) PORTD |= _BV(6);

    if (++ledPosn >= LEDMAP_LEN) ledPosn = 0;
  }

}
