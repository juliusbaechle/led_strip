#include <Wire.h>

#define STRIPPIN 4
#define NUMPIXEL 300
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXEL, STRIPPIN, NEO_GRB + NEO_KHZ800);

#define BEATPIN  3

//Variablen, die von Wire verändert werden
volatile byte clrMode = 1;
volatile byte color = 0;
volatile byte effektN = 1, effektM = 1;
volatile byte velocity = 5;
volatile byte actMode = 0; 
volatile unsigned char snlength = 20;
volatile unsigned char brightness = 100;
volatile unsigned char bpm = 120;
volatile short pixel = NUMPIXEL;

volatile boolean on = true;
volatile boolean music = false;
volatile boolean beat = false;
volatile boolean oneStrip = true;
volatile boolean clockwise = true;
volatile boolean contrary = true;
volatile boolean fade = false;
volatile boolean nextEffekt = false;
volatile boolean demo = false;

void setup() {
  attachInterrupt(digitalPinToInterrupt(BEATPIN), beatEvent, CHANGE);

  Wire.begin(1);                
  Wire.onReceive(receiveEvent);
  
  Serial.begin(9600);
  
  strip.begin();
}

void loop() {
  nextEffekt = false;
  strip.clear();
  strip.show();
  if(on) selectEffect();
  else {
    drawOff();
  }
}
