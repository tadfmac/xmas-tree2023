/*

 xmass tree usb-midi firmware 
 
 ©2024 by D.F.Mac.@TripArts Music
 
 ver. history
 
 - 2024/10/10 : alpha
 - 2024/10/14 : beta

*/
extern "C" void flash_get_unique_id(uint8_t *p);

#include <Adafruit_TinyUSB.h>
#include <Adafruit_NeoPixel.h>
#include <MIDI.h>
#include "makeUUID.h"

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

#define LED_PIN D7
#define MODE_PIN D0
#define TOP_LED 15
#define LED_NUM 16

// XIAO RGB LEDs
#define RED_LED 17
#define GREEN_LED 16
#define BLUE_LED 25

void xiaoRGBLedOff(){
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(BLUE_LED,HIGH);  
}

Adafruit_NeoPixel pixels(LED_NUM, LED_PIN);

int MODE = LOW;

char prdDescStr[33];

void makePrdDescStr(){
  uint8_t uuid[8];
  int cnt;
  
  flash_get_unique_id(uuid);
  prdDescStr[0] = 'm';
  prdDescStr[1] = 'i';
  prdDescStr[2] = ':';
  prdDescStr[3] = 'm';
  prdDescStr[4] = 'u';
  prdDescStr[5] = 'z';
  prdDescStr[6] = ':';
  prdDescStr[7] = 't';
  prdDescStr[8] = 'r';
  prdDescStr[9] = 'e';
  prdDescStr[10] = 'e';
  prdDescStr[11] = '-';
  prdDescStr[23] = 0;
  convert8bitToAscii(uuid,&(prdDescStr[12]));
  // prdDescStr[12] ++; // For patching when duplicate uuids are obtained
}  

//////////////////////////////////////////////////////////////
// Patterns
typedef struct pat{
  uint8_t *p;
  size_t size;
} Pat;

uint8_t pat1_0[] = {6};
uint8_t pat1_1[] = {7};
uint8_t pat1_2[] = {10};
uint8_t pat1_3[] = {6,7,10};
uint8_t pat1_4[] = {0,2,4,9,11,14};
uint8_t pat1_5[] = {0,1,2,3,4,5,8,9,11,12,13,14};
uint8_t pat1_6[] = {0,2,4,9,11,14};
uint8_t pat1_7[] = {6,7,10};
Pat pat1[] = {
  {pat1_0,sizeof(pat1_0)},
  {pat1_1,sizeof(pat1_1)},
  {pat1_2,sizeof(pat1_2)},
  {pat1_3,sizeof(pat1_3)},
  {pat1_4,sizeof(pat1_4)},
  {pat1_5,sizeof(pat1_5)},
  {pat1_6,sizeof(pat1_6)},
  {pat1_7,sizeof(pat1_7)}
};

uint8_t pat2_0[] = {2};
uint8_t pat2_1[] = {1,3,6,7,10};
uint8_t pat2_2[] = {0,4,5,8,9,11,12,13,14};
uint8_t pat2_3[] = {15};
uint8_t pat2_4[] = {2};
uint8_t pat2_5[] = {1,3,6,7,10};
uint8_t pat2_6[] = {0,4,5,8,9,11,12,13,14};
uint8_t pat2_7[] = {15};
Pat pat2[] = {
  {pat2_0,sizeof(pat2_0)},
  {pat2_1,sizeof(pat2_1)},
  {pat2_2,sizeof(pat2_2)},
  {pat2_3,sizeof(pat2_3)},
  {pat2_4,sizeof(pat2_4)},
  {pat2_5,sizeof(pat2_5)},
  {pat2_6,sizeof(pat2_6)},
  {pat2_7,sizeof(pat2_7)}
};

uint8_t pat3_0[] = {0,1,2,3,4};
uint8_t pat3_1[] = {5,6,7,8};
uint8_t pat3_2[] = {9,10,11};
uint8_t pat3_3[] = {12,13};
uint8_t pat3_4[] = {14,15};
uint8_t pat3_5[] = {12,13};
uint8_t pat3_6[] = {9,10,11};
uint8_t pat3_7[] = {5,6,7,8};
Pat pat3[] = {
  {pat3_0,sizeof(pat3_0)},
  {pat3_1,sizeof(pat3_1)},
  {pat3_2,sizeof(pat3_2)},
  {pat3_3,sizeof(pat3_3)},
  {pat3_4,sizeof(pat3_4)},
  {pat3_5,sizeof(pat3_5)},
  {pat3_6,sizeof(pat3_6)},
  {pat3_7,sizeof(pat3_7)}
};

uint8_t pat4_0[] = {0,1,2,3,4};
uint8_t pat4_1[] = {0,1,2,3,4,5,6,7,8};
uint8_t pat4_2[] = {0,1,2,3,4,5,6,7,8,9,10,11};
uint8_t pat4_3[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
uint8_t pat4_4[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t pat4_5[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
uint8_t pat4_6[] = {0,1,2,3,4,5,6,7,8,9,10,11};
uint8_t pat4_7[] = {0,1,2,3,4,5,6,7,8};
Pat pat4[] = {
  {pat4_0,sizeof(pat4_0)},
  {pat4_1,sizeof(pat4_1)},
  {pat4_2,sizeof(pat4_2)},
  {pat4_3,sizeof(pat4_3)},
  {pat4_4,sizeof(pat4_4)},
  {pat4_5,sizeof(pat4_5)},
  {pat4_6,sizeof(pat4_6)},
  {pat4_7,sizeof(pat4_7)}
};

uint32_t red = pixels.Color(16, 0, 0);
uint32_t green = pixels.Color(0, 16, 0);
uint32_t blue = pixels.Color(0, 0, 16);
uint32_t purple = pixels.Color(12, 0, 12);
uint32_t yellow = pixels.Color(12, 12, 0);
uint32_t white = pixels.Color(8, 8, 8);
uint32_t colors[] = {red,green,blue,purple,yellow,white};

void handleNoteOn(byte channel, byte num, byte val){
  Serial.print("NoteOn: channel:");
  Serial.print(channel);
  Serial.print(" num:");
  Serial.print(num);
  Serial.print(" val:");
  Serial.println(val);

  int idx;
  int cnt;
  uint8_t *p;

  if(MODE == LOW){ // Auto
    return;
  }
  if(val == 0){
    pixels.clear();
    pixels.show();
    return;
  }
  int cIndx = (int)(num % (sizeof(colors) / sizeof(colors[0])));
  uint32_t color = colors[cIndx];
  if((val >= 10)&&(val <= 17)){ // pat1
    idx = int(val -10);
    p = pat1[idx].p;
    pixels.clear();
    for(cnt=0;cnt<pat1[idx].size;cnt++){
       pixels.setPixelColor(p[cnt], color);
    }
    pixels.show();
  }else if((val >= 20)&&(val <= 27)){
    idx = int(val -20);
    p = pat2[idx].p;
    pixels.clear();
    for(cnt=0;cnt<pat2[idx].size;cnt++){
       pixels.setPixelColor(p[cnt], color);
    }
    pixels.show();
  }else if((val >= 30)&&(val <= 37)){
    idx = int(val -30);
    p = pat3[idx].p;
    pixels.clear();
    for(cnt=0;cnt<pat3[idx].size;cnt++){
       pixels.setPixelColor(p[cnt], color);
    }
    pixels.show();
  }else if((val >= 40)&&(val <= 47)){
    idx = int(val -40);
    p = pat4[idx].p;
    pixels.clear();
    for(cnt=0;cnt<pat4[idx].size;cnt++){
       pixels.setPixelColor(p[cnt], color);
    }
    pixels.show();
  }else{
    pixels.clear();
    pixels.show();
  }
}

void handleNoteOff(byte channel, byte num, byte val){
  Serial.print("NoteOff: channel:");
  Serial.print(channel);
  Serial.print(" num:");
  Serial.print(num);
  Serial.print(" val:");
  Serial.println(val);
  if(MODE == LOW){ // Auto
    return;
  }
  pixels.clear();
  pixels.show();
}

void setup() {
#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  TinyUSB_Device_Init(0);
#endif 
  USBDevice.setManufacturerDescriptor("TripArts Music");
  makePrdDescStr();
  USBDevice.setProductDescriptor((const char *)prdDescStr);
  USBDevice.setSerialDescriptor((const char *)&(prdDescStr[12]));
  USBDevice.setID(0x1209,0xDF03);
  
  xiaoRGBLedOff();

  pinMode(MODE_PIN, INPUT);

  randomSeed(analogRead(0));

  SerialTinyUSB.begin(115200);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  delay(1500);
  
}

int out = 0;

void blink1(){
  pixels.setPixelColor(out, pixels.Color(0, 0, 16));
  pixels.setPixelColor(TOP_LED, pixels.Color(0, 0, 16));
  pixels.show();
  delay(1000);
  pixels.setPixelColor(out, pixels.Color(0, 16, 0));
  pixels.setPixelColor(TOP_LED, pixels.Color(16, 0, 0));
  pixels.show();
  delay(1000);
  pixels.setPixelColor(out, pixels.Color(16, 0, 0));
  pixels.setPixelColor(TOP_LED, pixels.Color(0, 16, 0));
  pixels.show();
  delay(1000);
  pixels.clear();
  pixels.setPixelColor(TOP_LED, pixels.Color(16, 16, 16));
  pixels.show();
  delay(1000);
  out += 1;
  if(out >= 15){
    out = 0;
  }
}

void blink2(){
  int cnt;
  for(cnt=0;cnt<LED_NUM;cnt++){
    pixels.setPixelColor(cnt, pixels.Color(16, 16, 16));
  }
  pixels.show();
  delay(200);
  pixels.clear();
  pixels.show();
  delay(100);
}

void blink3(){
  int led = random(15);
  int r = random(16);
  int g = random(16);
  int b = random(16);
  pixels.setPixelColor(led, pixels.Color(r, g, b));
  led = random(15);
  r = random(16);
  g = random(16);
  b = random(16);
  pixels.setPixelColor(led, pixels.Color(r, g, b));
  led = random(15);
  r = random(16);
  g = random(16);
  b = random(16);
  pixels.setPixelColor(led, pixels.Color(r, g, b));
  pixels.setPixelColor(TOP_LED, pixels.Color(16, 16, 16));
  pixels.show();
  delay(200);
  pixels.clear();
  pixels.show();
  delay(200);
}

void blink4(){
  pixels.clear();
  int led = random(15);
  int r = random(16);
  int g = random(16);
  int b = random(16);
  pixels.setPixelColor(led, pixels.Color(r, g, b));
  led = random(15);
  r = random(16);
  g = random(16);
  b = random(16);
  pixels.setPixelColor(led, pixels.Color(r, g, b));
  led = random(15);
  r = random(16);
  g = random(16);
  b = random(16);
  pixels.setPixelColor(led, pixels.Color(r, g, b));
  pixels.setPixelColor(TOP_LED, pixels.Color(16, 16, 16));
  pixels.show();
  delay(500);
  r = random(16);
  g = random(16);
  b = random(16);
  pixels.setPixelColor(TOP_LED, pixels.Color(r, g, b));
  pixels.show();
  delay(3500);
}

void loop() {
  int md = digitalRead(MODE_PIN);
  if(md != MODE){
    pixels.clear();
    pixels.show();
  }
  MODE = md;
  if(MODE == LOW){ // Auto
    blink3();
  }
  if(SerialTinyUSB.available() > 0) {
    uint8_t data = SerialTinyUSB.read();
    if(10 == data) {
      data = '\n';
    }
    SerialTinyUSB.print(data);
  }
  MIDI.read();
  delay(1);
}
