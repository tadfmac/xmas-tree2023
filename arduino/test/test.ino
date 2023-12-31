#include <Adafruit_NeoPixel.h>

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

void setup() {
  xiaoRGBLedOff();

  pinMode(MODE_PIN, INPUT);

  MODE = digitalRead(MODE_PIN);

  randomSeed(analogRead(0));
  
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


void blink(){
  if(MODE == HIGH){
    blink4();
  }else{
    blink3();
  }
}

void loop() {
  blink();
}
