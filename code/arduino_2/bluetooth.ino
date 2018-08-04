static char dataVal = -1;                             //Enthaelt den aktuellen Wert
static char menu = 0, menu_farbe = 0, menu_konfi = 0; //Steuern die Menues
static char _min = 1, _max = 4;                       //Fangen falsche Eingaben ab

void btEvent() {
  if (bt.peek() >= '0' && bt.peek() <= '9') {
    dataVal = getValue();
  } else {
    rewindSerial();
    dataVal = -1;
  }

  if (dataVal >= _min && dataVal <= _max) {
    setSerial();
    sendSerial();
  }
}


void setSerial() {
  switch (menu) {
    case 0: if(dataVal == 1) writeWire("changeOn");
              else menu = dataVal;
      break;
    case 2: setFarbe();
      break;
    case 3: writeWire("effektN = ", dataVal);
            if(dataVal == 0) doDemo = true;
              else doDemo = false;
            doBeat = false;
            menu = 0;
      break;
    case 4: writeWire("effektM = ", dataVal);
            if(dataVal == 0) doDemo = true;
              else doDemo = false;
            doBeat = true;
            menu = 0;
      break;
    case 5: setKonfi();
      break;
  }
}

void setFarbe() {
  if (menu_farbe == 0) {
    writeWire("clrMode = ", dataVal);
    if (dataVal != 1) menu = 0;
      else menu_farbe = 1;
  } else if(menu_farbe == 1) { //Auswahl einer einzelnen Farbe
    writeWire("color = ", dataVal);
    menu = 0;
  }
}

void setKonfi() {
  if (menu_konfi == 0) {
    menu_konfi = dataVal;
    switch (menu_konfi) {
      case 1: writeWire("changeOneStrip"); 
        break;
      case 2: writeWire("changeClockwise");
        break;
      case 3: writeWire("changeContrary");
        break;
      case 6: writeWire("changeFade");
        break;
    }
    if (menu_konfi <= 3 || menu_konfi == 6) menu = 0;
  } else {
    switch (menu_konfi) {
      case 4: writeWire("brightness = ", dataVal);
        break;
      case 5: writeWire("velocity = ", dataVal);
        break;
      case 7: writeWire("snlength = ", dataVal);
        break;
    }
    menu = 0;
  }
}


void sendSerial() {
  switch (menu) {
    case 0: printMenu();
      break;
    case 2: printFarbe();
      break;
    case 3: printEffektN();
      break;
    case 4: printEffektM();
      break;
    case 5: printKonfi();
      break;
  }
}

void printMenu() {
  clearSerial();
  bt.println(F("1: An/Aus"));
  bt.println(F("2: Farbe"));
  bt.println(F("3: Normale Effekte"));
  bt.println(F("4: Musik Effekte"));
  bt.println(F("5: Optionen"));
  _min = 1;
  _max = 5;

  //setzt alle Menuevariablen zurueck
  menu = 0;
  menu_farbe = 0;
  menu_konfi = 0;
}

void printFarbe() {
  clearSerial();
  if (menu_farbe == 0) {
    bt.println(F("1: Einzelne Farbe "));
    bt.println(F("2: 3  Farben"));
    bt.println(F("3: 6  Farben"));
    bt.println(F("4: 12 Farben"));
    bt.println(F("5: Regenbogen (nicht wandernd)"));
    bt.println(F("6: Regenbogen (wandernd)"));
    _min = 1;
    _max = 6;
  } else {
    bt.println(F("0:  weiss"));
    bt.println(F("1:  rot         2:  pink"));
    bt.println(F("3:  violett   4:  lila"));
    bt.println(F("5:  blau      6:  cyan"));
    bt.println(F("7:  tuerkis  8:  tuerkisgruen"));
    bt.println(F("9:  gruen    10: hellgruen"));
    bt.println(F("11: gelb     12: orange"));
    _min = 0;
    _max = 12;
  }
}

void printEffektN() {
  clearSerial();
  bt.println(F("0: Demo         1: All"));
  bt.println(F("2: Snake         3: PingPong"));
  bt.println(F("4: ColorRace  5: Theater Chase"));
  bt.println(F("6: Wipe           7: Fire"));
  bt.println(F("8: Oscillate    9: Bouncing Balls"));
  bt.println(F("10: Sparkle"));
  _min = 0;
  _max = 10;
}

void printEffektM() {
  clearSerial();
  bt.println(F("0: Demo          1: All"));
  bt.println(F("2: PingPong   3: Half "));
  bt.println(F("4: Oscillate     5: Fade "));
  bt.println(F("6: Blink            7: Theater Chase "));
  bt.println(F("8: Beat             9: Color Race"));
  _min = 0;
  _max = 10;
}

void printKonfi() {
  clearSerial();
  switch (menu_konfi) {
    case 4:  bt.println(F("Gebe Sie die Helligkeit in Prozent an"));
      _min = 1;
      _max = 100;
      break;
    case 5:  bt.println(F("Gebe einen Wert zwischen 0 und 10 als Geschwindigkeit ein"));
      _min = 0;
      _max = 10;
      break;
    case 7:  bt.println(F("Geben Sie eine Laenge (der Schlangen) zwischen 5 und 40 ein"));
      _min = 5;
      _max = 40;
      break;
    default: bt.println(F("1: Ein/Zwei Streifen"));
      bt.println(F("2: Umlaufrichtung"));
      bt.println(F("3: Entgegengesetz"));
      bt.println(F("4: Helligkeit"));
      bt.println(F("5: Geschwindigkeit"));
      bt.println(F("6: Faden"));
      bt.println(F("7: Schlangenlaenge"));
      _min = 1;
      _max = 7;
      break;
  }
}
int getValue() { //Gibt ÃƒÂ¼ber Bluetooth gesendete, maximal 3-zahlige Ganzzahlen zurueck
  delay(50);        //Wenn mehrere Zeichen gesendet werden, wird ist der Ablauf sonst mÃƒÂ¶glicherweise
  int value = 0;    //(bsp. bei 100): 1 -1 -1 loop() 0 0 -1 => es wird 1 gelesen
  short stellen = 0, aktV = 0;
  short nums [3];
  for (int i = 0; i < 3; i++) {
    aktV = bt.read() - 48;
    if (aktV >= 0 && aktV <= 9) {
      nums[i] = aktV;
      stellen++;
    }
  }
  for (int i = 0; i < stellen; i++) {
    value += pow10((stellen - 2) - i) * nums[i];
  }
  rewindSerial();
  return value;
}

int pow10(short expo) {
  int ergebnis = 1;
  for(int i = 0; i == expo; i++){
    ergebnis *= 10;
  }
  return ergebnis;
}

void clearSerial() { //leert den Serial-Bildschirm
  for (short z = 0; z <= 20; z++) bt.println("");
}

void rewindSerial() { //leert den Input-Buffer
  for (short z = 0; z <= 10; z++) bt.read();
}
