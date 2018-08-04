const byte ALLN = 1, SNAKEN = 2, PINGN = 3, CRACEN = 4, TCHASEN = 5, WIPEN = 6, FIREN = 7, OSCN = 8, BALLSN = 9, SPARKLEN = 10; 
const byte ALLM = 1, PINGM = 2, HALFM = 3, OSCM = 4, FADEM = 5, BLINKM = 6, TCHASEM = 7, BEATM = 8, CRACEM = 9;
short waitFactor = 10;

void selectEffect(){
  if(!music){
    switch(effektN){
      case ALLN: allN();
      case SNAKEN: snakeN();
      case PINGN: pingN();
      case CRACEN: cRaceN();
      case TCHASEN: tChaseN();
      case WIPEN: wipeN();
      case FIREN: fireN();
      case OSCN: oscN();
      case BALLSN: ballsN();
      case SPARKLEN: sparkleN();
    }   
  } else {
    switch(effektM){
      case ALLM: allM();
      case PINGM: pingM();
      case HALFM: halfM();
      case OSCM: oscM();
      case FADEM: fadeM();
      case BLINKM: blinkM(3);
      case TCHASEM: tChaseM();
      case BEATM: beatM();
      case CRACEM: cRaceM();
    }
  }
}

static void setPixel(int nr, uint32_t color) {
  if (oneStrip) {
    if (clockwise) {
      strip.setPixelColor(nr, color);
    } else {
      strip.setPixelColor((NUMPIXEL - 1) - nr, color);
    }
  } else if (nr >= 0 && nr <= NUMPIXEL/2 - 1) {
    if (contrary) {
      if (clockwise) {
        strip.setPixelColor(nr, color);
        strip.setPixelColor(NUMPIXEL/2 + nr, color);
      } else {
        strip.setPixelColor((NUMPIXEL/2 - 1) - nr, color);
        strip.setPixelColor((NUMPIXEL - 1) - nr, color);
      }
    } else {
      if (clockwise) {
        strip.setPixelColor(nr, color);
        strip.setPixelColor((NUMPIXEL - 1) - nr, color);
      } else {
        strip.setPixelColor((NUMPIXEL/2 - 1) - nr, color);
        strip.setPixelColor(NUMPIXEL/2 + nr, color);
      }
    }
  }
}

void drawOff(){
  strip.clear(); 
  strip.setPixelColor((NUMPIXEL * 1.0)/4, strip.Color(255, 0, 0));
  strip.setPixelColor((NUMPIXEL * 3.0)/4 - 1, strip.Color(255, 0, 0));
  strip.show();
}

int getWaitTime(){
  return (10 - velocity)*waitFactor;
}


