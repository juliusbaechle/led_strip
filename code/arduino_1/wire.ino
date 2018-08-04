void receiveEvent(){
  char receivedChars[20];
  for(int i = 0; i < 20; i++){
    receivedChars[i] = 0;
  }
  
  short i = 0;
  while(Wire.available()){
    receivedChars[i] = Wire.read();
    i++;      
  }

  //Aendert volatile global Variablen entsprechend ab
  // boolean: music
  // change : changeOn, changeOneStrip, changeClockwise, changeContrary, changeFade
  // integer: clrMode, color, effektN, effektM, velocity, brightness, snlength

  //Demo - Modus
  if(strcmp(receivedChars, "demo") == 0) demoFunc();
  
  //boolean
  if(strncmp(receivedChars, "music = ", 8) == 0){
    if(atoi(receivedChars + 8) == 1) setMusic(true);
    else setMusic(false);
  }
  
  //change - methods
  if(strcmp(receivedChars, "changeOn"       ) == 0) changeOn();
  if(strcmp(receivedChars, "changeOneStrip" ) == 0) changeOneStrip();
  if(strcmp(receivedChars, "changeClockwise") == 0) changeClockwise();
  if(strcmp(receivedChars, "changeContrary" ) == 0) changeContrary();
  if(strcmp(receivedChars, "changeFade"     ) == 0) changeFade(); 

  //integer
  if(strncmp(receivedChars, "clrMode = "   , 10) == 0) setClrMode(atoi(receivedChars + 10));
  if(strncmp(receivedChars, "color = "     ,  8) == 0) color      = atoi(receivedChars +  8);
  if(strncmp(receivedChars, "effektN = "   , 10) == 0){
    effektN    = atoi(receivedChars + 10);
    setMusic(false);
    if(effektN == 0) demoFunc();
    nextEffekt = true;
  }
  if(strncmp(receivedChars, "effektM = "   , 10) == 0){
    effektM    = atoi(receivedChars + 10);
    setMusic(true);
    if(effektM == 0) demoFunc();
    nextEffekt = true;
  }
  if(strncmp(receivedChars, "velocity = "  , 11) == 0) velocity   = atoi(receivedChars + 11);
  if(strncmp(receivedChars, "brightness = ", 13) == 0) brightness = atoi(receivedChars + 13);
  if(strncmp(receivedChars, "snlength = "  , 11) == 0) snlength   = atoi(receivedChars + 11);

  //Serial.print("receivedChars: ");
  //Serial.println(receivedChars);
}

void writeWire(char* s){
  //Serial.print("wrote: ");
  //Serial.println(s);
  Wire.beginTransmission(2);
  Wire.write(s);
  Wire.endTransmission();
}

void demoFunc(){
  nextEffekt = true;
  
  clrMode = random(1, 7);
  if(clrMode == 1) color = random(0, 13);

  if(music){
    byte oldEffektM = effektM;
    effektM = random(1, 10);
    if(effektM != oldEffektM) nextEffekt = true;
  } else {
    byte oldEffektN = effektN;
    effektN = random(1, 11);
    if(effektN != oldEffektN) nextEffekt = true;
  }

  fade = random(0, 2);
  snlength = random(10, 41);
  if(random(2)) changeOneStrip();
  if(random(2)) changeContrary();
}

void changeOn(){
  on = !on;
  nextEffekt = true;
}

void changeOneStrip(){
  oneStrip = !oneStrip;
  
  if(oneStrip) pixel = NUMPIXEL;
  else pixel = NUMPIXEL/2;
}

void changeClockwise(){
  clockwise = !clockwise;
}

void changeContrary(){
  contrary = !contrary;
  oneStrip = false;
  pixel = NUMPIXEL/2;
}

void changeFade(){
  fade = !fade;
}

void setMusic(boolean value){
  music = value;
}

