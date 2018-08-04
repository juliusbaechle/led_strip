#include <FastLED.h>

const char C1 = 1, C3 = 2, C6 = 3, C12 = 4, RB1 = 5, RB2 = 6;
short rbZ, rbZ2;


uint32_t getFixClr(){
  return fixedClr(color);
}

uint32_t nextFixClr() {
  switch(clrMode){
    case C3: color += 4;
      break;
    case C6: color += 2;
      break;
    case C12: color ++;
      break;
  }
  if(color > 12) color = 1;
  
  return fixedClr(color);
}

uint32_t fixedClr(short num) {
  uint32_t c;
  switch (num){
    case 1:  c = 0xFF0000; //rot
      break;
    case 2:  c = 0xC00040; //pink
      break;
    case 3:  c = 0x800080; //voilett
      break;
    case 4:  c = 0x4000C0; //lila
      break;
    case 5:  c = 0x0000FF; //blau
      break;
    case 6:  c = 0x0040C0; //cyan
      break;
    case 7:  c = 0x008080; //tuerkis
      break;
    case 8:  c = 0x00C040; //tuerkisgruen
      break;
    case 9:  c = 0x00FF00; //gruen
      break;
    case 10: c = 0x40C000; //hellgruen
      break;
    case 11: c = 0x808000; //gelb
      break;
    case 12: c = 0xC04000; //orange
      break;
    default: c = 0xFFFFFF; //weiss
      break;
  }
  return dimm(c, brightness);
}

uint32_t getRbClr(){
  if(clrMode == RB2){
    rbZ2 ++;
    if(rbZ2 > 255) rbZ2 = 0;
  }
  return rbClr(rbZ + rbZ2);
}

uint32_t nextRbClr(){
  rbZ++;
  rbZ2 = 0;
  return rbClr(rbZ);
}

uint32_t rbClr(int number) {
  number = number%256;
  CHSV cHSV(255 - number, 220, 255);
  CRGB cRGB = cHSV;
  uint32_t c = strip.Color(cRGB.r, cRGB.g, cRGB.b);
  c = dimm(c, brightness);
  return c;
}

uint32_t getFireClr(short value){
  uint32_t c;
     
  byte heatramp = value & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  if( value > 0x80) {                     // hottest
    c = strip.Color(255, 255, heatramp);
  } else if( value > 0x40 ) {             // middle
    c = strip.Color(255, heatramp, 0);
  } else {                                // coolest
    c = strip.Color(heatramp, 0, 0);
  }
  return dimm(c, brightness);
}

uint32_t randClr(){
  switch(clrMode){
    case C1:  return getFixClr();
                break;
    case C3:  return fixedClr(1 + random(3)*4);
                break;
    case C6:  return fixedClr(1 + random(6) * 2);
                break;
    case C12: return fixedClr(random(1, 13));
                break;
    case RB1:
    case RB2: return rbClr(random(0, 255));
                break;
  }
}

//dimmt color auf Prozente der Eingangsfarbe
uint32_t dimm(uint32_t color, short percent) { 
  byte b = color & 0xff;
  byte g = (color >> 8) & 0xff;
  byte r = (color >> 16) & 0xff;
  float k = (float)percent / 100;
  return strip.Color(k * r, k * g, k * b);
}
  
boolean isRbClr(){
  if(clrMode > 4) return true;
  return false;  
}

int getClrMode(){
  return clrMode;
}

void setClrMode(int value){
  clrMode = value;
  if (clrMode >= C3 && clrMode <= C12) color = 1;
}
