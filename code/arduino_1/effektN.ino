void allN(){
  waitFactor = 10;
  uint32_t c = getFixClr();
  double timer = 0;
  short clrZ = 0;
  short rbZ = 0;
  short fadeZ = 0;
  bool fadeUp = true;
  
  while(!nextEffekt){      
    if(millis() - timer > getWaitTime()){
      timer = millis();

      if(!isRbClr()){
        clrZ++;
        if(!fade && clrZ > 30){
          clrZ = 0;
          nextFixClr();
        }
        c = getFixClr();
      } else {
        rbZ++;
        c = nextRbClr();
      }

      if(fade){
        if(fadeUp){
          fadeZ++;
          if(fadeZ >= 100) fadeUp = false;
        } else {
          fadeZ--;
          if(fadeZ <= 0){
            fadeUp = true;
            c = nextFixClr();
          }
        }
        c = dimm(c, fadeZ);
      }

      for(int i = 0; i < pixel; i++){
        if(getClrMode() == 6){
          c = getRbClr();
          if(fade) c = dimm(c, fadeZ);
        }
        setPixel(i, c);
      }

      strip.show();
    }    
  }
  strip.clear();
  strip.show();
}

void snakeN(){
  waitFactor = 10;
  short z = 0; //Ort des Kopfes
  uint32_t c, C;
  double timer;

  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      timer = millis();
      
      if(!isRbClr()){
        c = getFixClr();
      } else {
        c = nextRbClr();
      }
      C = c;

      strip.clear();
      for (int i = z; i > z - snlength && i > 0; i--){
        if(fade){
          float x = 1 - (((float)((z - i) + 1)/(float)(snlength + 1)));
          c = dimm(C, (short)(x * x * 100));
        }
        setPixel(i, c);
      }
      
      if(z > pixel + snlength){
        z = 0;
        nextFixClr();
      } else z += (int)(0.3 * velocity) + 1;
  
      strip.show();
    }
  }
}

void pingN(){
  waitFactor = 10;
  short z = 0;
  uint32_t c, C;
  double timer;

  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      timer = millis();
      
      if(!isRbClr()){
        c = getFixClr();
      } else {
        c = nextRbClr();
      }
      C = c;
      
      strip.clear();
      for (int i = z; i > z - snlength && i > 0; i--){
        if(fade){
          float x = 1 - (((float)((z - i) + 1)/(float)(snlength + 1)));
          c = dimm(C, (short)(x*x*100));
        }
        setPixel(i, c);
      }
      
      if(z > pixel + snlength){
        z = 0;
        nextFixClr();
        clockwise= !clockwise; 
      } else z += (int)(0.3 * velocity) + 1;
      
      strip.show();  
    }
  }
}

//Probleme bei Regenbogenfarben
void cRaceN(){
  waitFactor = 10;
  short z = 0;
  short rbZ = 0;
  unsigned char refrZ = 0;
  unsigned char farbe = 1;
  uint32_t C, c;
  double timer;

  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      timer = millis();
      strip.clear();

      if(clrMode == 1 || clrMode == 5 || clrMode == 6) fade = true; 
      
      if(!isRbClr()){
        if(refrZ < 2*snlength){
          refrZ++;
        } else {
          switch(clrMode){
            case 2: farbe += 4;
              break;
            case 3: farbe += 2;
              break;
            case 4: farbe++;
              break;
          }
          if(farbe > 12) farbe = 1;
          refrZ = 0;
        }
        if(clrMode != 1) color = farbe;
        
        c = getFixClr();
        C = c; 
      } else {
        if(refrZ < 2*snlength) refrZ++;
        else refrZ = 0;
        
        c = rbClr(rbZ);
        rbZ += 3;
      }
      
      z = refrZ;


    
      for(short i = 0; i < pixel; i++){        
        if(clrMode == 6){
          c = rbClr(rbZ + i);
          C = c;
        } else if(clrMode == 5){
          c = rbClr(rbZ);
          C = c;
        }
        
        if(z >= 2*snlength){
          z = 1;
          if(clrMode >= 2 && clrMode <= 4){
            c = nextFixClr();
            C = c;
          }
        } else {
          z++;
        }
        
        if(fade){
          if(z < snlength){
            float x = z/(float)snlength;
            c = dimm(C, (short)(100*(x*x)));
          } else {
            float x = (2*snlength - z)/(float)snlength;
            c = dimm(C, (short)(100*(x*x)));
          }
        }
        
        setPixel(i, c);
      }
      
      strip.show();
    }
  }
}

void tChaseN(){
  waitFactor = 10;
  uint32_t c;
  unsigned char refrZ = 0;
  short z = 0;
  double timer;
  
  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      timer = millis();
      strip.clear();
      
      if(clrMode <= 4) c = getFixClr();
       else c = nextRbClr();
      
      for(short i = z; i < pixel; i += 3){
        if(clrMode == 6) c = getRbClr();
        setPixel(i, c);
      }
      
      if(z<3) z++;
        else z=0;
      if(refrZ >= 30){
        refrZ = 0;
        nextFixClr();
      } else {
        refrZ++;
      }
      
      strip.show();
    }
  }
}

void wipeN(){
  waitFactor = 20;
  short z = 0;
  char farbe = 1;
  uint32_t c;
  double timer;

  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      timer = millis();
      strip.clear();

      if(clrMode == 1) clrMode = 2;
      if(clrMode == 5 || clrMode == 6) clrMode = 4;
      color = farbe;
      c = getFixClr();
      for(int i = z; i < pixel; i++){
        setPixel(i, c);
      }
      c = nextFixClr();
      for(int i = 0; i <= z; i++){
        setPixel(i, c);
      }
    
      z++;
      if(z > pixel){
        z = 0;
        switch(clrMode){
          case 2: farbe += 4;
            break;
          case 3: farbe += 2;
            break;
          case 4: farbe++;
            break;
        }
        if(farbe > 12) farbe = 1;
      }

      strip.show();
    }
  }
}

void fireN() {
  waitFactor = 10;
  uint32_t c;
  unsigned char heat[2][70];
  short cooldown;
  double timer;
  #define COOLING 23
  #define SPARKING 120
  #define LENGTH 70

  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      timer = millis();
      strip.clear();
      contrary = false;
      oneStrip = false;
      pixel = NUMPIXEL/2;
      
      for(short side=0; side<=1; side++){
        for(int i=0; i<70; i++) {
          cooldown = random(0, ((COOLING * 10) / 70) + 2);
          
          if(cooldown>heat[side][i]) {
            heat[side][i]=0;
          } else {
            heat[side][i]=heat[side][i]-cooldown;
          }
        }
        
        for(int k = LENGTH - 1; k >= 2; k--) {
          heat[side][k] = (heat[side][k - 1] + 2 * heat[side][k - 2]) / 3;
        }
      
        if(random(255) < SPARKING) {
          int y = random(7);
          heat[side][y] = heat[side][y] + random(160,255);
        }
      
        for(short i=0; i < LENGTH; i++) {
          uint32_t c = getFireClr((int)((heat[side][i]/255.0)*191));
          
          if(side==0) setPixel(i, c);
          if(side==1) setPixel(pixel - i, c);
        }
      }
      strip.show();
    }
  }
}

void oscN(){
  waitFactor = 10;
  boolean osz_on = true;
  double timer;
  uint32_t c = getFixClr();
  short clrZ = 0;
  short rbZ = 0;
  short fadeZ = 0;
  bool fadeUp = true;
  
  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      timer = millis();
      
      if(osz_on){
        if(!isRbClr()){
          clrZ++;
          if(clrZ > 20){
            clrZ = 0;
            nextFixClr();
          }
          c = getFixClr();
        } else {
          rbZ++;
          c = nextRbClr();
        }
        
        for(int i = 0; i < pixel; i++){
          if(getClrMode() == 6){
            c = getRbClr();
            if(fade) c = dimm(c, fadeZ);
          }
          setPixel(i, c);
        }
      } else strip.clear();
      
      osz_on=!osz_on;
      strip.show();
    }
  }
}

void ballsN() {
  waitFactor = 0;
  
  #define VSTART 7
  #define BALLCOUNT 3
  const float DAMPENING = 0.15;
  const uint32_t farben [BALLCOUNT] = {strip.Color(255, 0, 0), strip.Color(0, 255, 0), strip.Color(0, 0, 255)};
  
  float x [BALLCOUNT] = {1, 1, 1};                                   
  float t0 [BALLCOUNT] = {millis(), millis(), millis()};  
  float v0 [BALLCOUNT] = {VSTART, 0.7 * VSTART, 0.5 * VSTART};     

  double timer;
  
  while(!nextEffekt){
    oneStrip = false;
    contrary = false;
    pixel = NUMPIXEL/2;
    strip.clear();
    
    //Berechnung der Position
    for (int i = 0; i < BALLCOUNT; i++){
      float  t = (millis() - t0[i])/400;
      x[i] = v0[i] * t - 0.5 * 9.81 * t * t; //x(t) = v0t - 1/2gt^2
      if(x[i] < 0) { //Ball ist aufgeschlagen
        v0[i] = (1 - DAMPENING) * v0[i];
        t0[i] = millis();
        if (v0[i] < 0.57) v0[i] = VSTART - random(0, 20)/10;
      }
    }
  
    //Ausgabe
    for(int i = 0; i < BALLCOUNT; i++){
      short pos = x[i] * 60; //Umrechnung in Pixelhoehe
      setPixel(pos, farben[i]);
    }
    strip.show();
  }
}

//springt automatisch zu ausgangfarbe zurück
void sparkleN(){ 
  #define ANZPIXEL 30
  waitFactor = 10;
  
  struct Pixel{
    unsigned char cycles = random(10, 50); //Erscheinungszeit in Zyklen!, 1 Zyklus entspricht (10-v)*10 ms;
    short pos = random(pixel);             //Die Position des Pixels auf dem Streifen
    uint32_t color = randClr();            //Farbe des Pixels
  };
  struct Pixel pixelArr[ANZPIXEL];

  double timer;

  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      timer = millis();
      
      oneStrip = false;
      pixel = 150;
      contrary = true;
      strip.clear();
      
      for(int i = 0; i < ANZPIXEL; i++){
        if(pixelArr[i].cycles > 0){
          pixelArr[i].cycles--;
        } else {
          pixelArr[i].cycles = random(10, 50);
          pixelArr[i].pos = random(0, pixel);
          pixelArr[i].color = randClr();
        }
        setPixel(pixelArr[i].pos, pixelArr[i].color);
      }
      
      strip.show();
    }
  }
}
