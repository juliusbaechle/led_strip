#include <Wire.h>

#define BEATPIN 6
#define CLAPPIN 3

//Sollte spaeter auf Serial umgestellt werden aus Gruenden der Performance
#define RXPIN    4
#define TXPIN    5
#include <SoftwareSerial.h>
SoftwareSerial bt(RXPIN, TXPIN);

volatile byte actMode = 1;
volatile boolean changeOn = false;
unsigned char bpm;
boolean doDemo = false, doBeat = true;

void setup() {
  bt.begin(9600);
  printMenu();
    
  Wire.begin();
  Serial.begin(9600);
  
  pinMode(BEATPIN,  OUTPUT);
  pinMode(CLAPPIN,  INPUT);
  
  attachInterrupt(digitalPinToInterrupt(CLAPPIN), clapEvent, FALLING);
}

void loop() {
  if(bt.available()){
    btEvent();
  }
  
  if(changeOn){
    changeOn = false;
    writeWire("changeOn");
  }
  
  if(doDemo) writeDemo();
  if(doBeat) writeBeat();
}

void writeDemo(){
  static double timer;
  static int demoTime = random(3000, 15000);
  
  if(millis() - timer > demoTime){
    timer = millis();
    demoTime = random(3000, 15000);
    writeWire("demo");
  }
}


