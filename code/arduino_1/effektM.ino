void allM(){
  static uint32_t c;
  static boolean newClr = true;
  
  while(!nextEffekt){
    strip.clear();
    if(clrMode == 1) clrMode = 2;
    
    if(isNewBeat(50)){
      newClr = false;
      if(!isRbClr()){
        c = nextFixClr();
      } else {
        c = randClr();
      }
    }
  
    for(int i = 0; i < pixel; i++){
      setPixel(i, c);
    }
    
    strip.show();
  }
}

void pingM(){
  waitFactor = 5;
  short z = pixel/2;
  uint32_t c, C;
  double timer;

  while(!nextEffekt){
    if(millis() - timer > getWaitTime()){
      strip.clear();
      
      if(isNewBeat(80) ){
        clockwise = !clockwise;
        z = pixel + snlength - z;
        nextFixClr();
      }
      
      if(!isRbClr()){
        c = getFixClr();
      } else {
        c = nextRbClr();
      }
      C = c;

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

static void halfM(){
  uint32_t c, C;
  boolean right = false;
  double beatTimer;
  short rbZ = 0;
  
  while(!nextEffekt){
    strip.clear();
    
    if(isNewBeat(50)){
      beatTimer = millis();
      right = !right;
      if(!isRbClr()) C = nextFixClr();
    }
    if(isRbClr()){
      C = rbClr(rbZ);
      rbZ++;
    }

    if(fade){
      if(millis() - beatTimer > 200) beatTimer = millis() - 200;
      c = dimm(C, 100 * (1 - (millis() - beatTimer)/200));
    } else {
      if(millis() - beatTimer > 100) c = 0;
      else c = C;
    }
    
    if(right){
      for(int i = 0; i < pixel/2; i++){
        if(clrMode == 6) {
          C = rbClr(rbZ + i);
          if(fade){
            if(millis() - beatTimer > 200) beatTimer = millis() - 200;
            c = dimm(C, 100 * (1 - (millis() - beatTimer)/200));
          } else {
            if(millis() - beatTimer > 100) c = 0;
            else c = C;
          }
        }
        
        setPixel(i, c);
      }
    } else {
      for(int i = pixel/2; i < pixel; i++){
        if(clrMode == 6) {
          C = rbClr(rbZ + i);
          if(fade){
            if(millis() - beatTimer > 200) beatTimer = millis() - 200;
            c = dimm(C, 100 * (1 - (millis() - beatTimer)/200));
          } else {
            if(millis() - beatTimer > 100) c = 0;
            else c = C;
          }
        }
        
        setPixel(i, c);
      }
    }

    strip.show();
  }
}


static void oscM(){
  uint32_t c, C;
  double beatTimer;
  short rbZ = 0;
  
  while(!nextEffekt){
    strip.clear();
    
    if(isNewBeat(50)){
      beatTimer = millis();
      if(!isRbClr()) C = nextFixClr();
    }
    if(isRbClr()){
      C = rbClr(rbZ);
      rbZ++;
    }

    if(fade){
      if(millis() - beatTimer > 200) beatTimer = millis() - 200;
      c = dimm(C, 100 * (1 - (millis() - beatTimer)/200));
    } else {
      if(millis() - beatTimer > 100) c = 0;
      else c = C;
    }
    
    for(int i = 0; i < pixel; i++){      
      setPixel(i, c);
    }

    strip.show();
  }
}

void fadeM(){
  waitFactor = 1;
  short redNow = random(256), greenNow = random(256), blueNow = random(256);
  short redNew = 0, greenNew = 0, blueNew = 0;
  double timer;

  while(!nextEffekt){ 
    if(millis() - timer > getWaitTime()){
      timer = millis();

      if((redNow != redNew) || (blueNow != blueNew) || (greenNow != greenNew)){
        fadeC(&redNow, redNew);
        fadeC(&greenNow, greenNew);
        fadeC(&blueNow, blueNew);
        uint32_t c = strip.Color(redNow, greenNow, blueNow);
        for(int i = 0; i < pixel; i++){
          setPixel(i, c);
        }
      } else {
        if(fade) strip.clear();
      }
      
      if(isNewBeat(50)){
        redNew = random(255);
        greenNew = random(255);
        blueNew = random(255);
      }

      strip.show();
    }
  }
}

void fadeC(int *x, int y){
  #define STEP 5
  if(*x >= y + STEP) *x -= STEP; 
  else if(*x <= y - STEP) *x += STEP; 
  else *x = y;
}

void blinkM(byte times){
  waitFactor = 8;
  double timer;
  uint32_t c;
  short onTime = 3 * getWaitTime(), periodTime = 5 * getWaitTime();
  short rbZ = 0;
  
  while(!nextEffekt){
    rbZ++;
    onTime = 3 * getWaitTime();
    periodTime = 5 * getWaitTime();
    
    if(isNewBeat(50)){
      timer = millis();
      
      if(!isRbClr()){
        c = nextFixClr();
      } else {
        c = rbClr(rbZ);
      }

      for(int p = 0; p < times; p++){
        for(int i = 0; i < pixel; i++){
          if(clrMode == 6) c = rbClr(rbZ + i);
          setPixel(i, c);
        }
        strip.show();
        while(millis() - timer < onTime + p * periodTime);
        strip.clear();
        strip.show();
        while(millis() - timer < (p+1)*periodTime);
      }
    }
  }
}

void tChaseM(){
  waitFactor = 3;
  uint32_t c;
  byte pixelPerStep = 10;
  short z = 3 * pixelPerStep;
  short rbZ = 0;
  double timer = 0;

  while(!nextEffekt){    
    strip.clear();
    
    if(isNewBeat(100)){
      z++;
      if(z >= 3) z = 0;
        
      if(!random(6) && !isRbClr()) c = nextFixClr();
    } 

    if(isRbClr() && millis() - timer > getWaitTime()){
      timer = millis();
        
      rbZ++;
    }

    c = getFixClr();
    if(clrMode == 5) c = rbClr(rbZ);
    
    for(int i = z * pixelPerStep; i < pixel; i += pixelPerStep * 3){
      for(int s = i; s < i + pixelPerStep; s++){ 
        if(clrMode == 6) c = rbClr(rbZ + i);
        setPixel(s, c);
      }
    }

    strip.show(); 
  }
}

void beatM(){
  const byte START = 10;
  uint32_t c, C;
  short z = START + 2;
  short rbZ;
  boolean newBeat = false;
  boolean countUp = true;
 
  while(!nextEffekt){
    if(isRbClr()){
      rbZ++;
      c = rbClr(rbZ);
      for(int i = 0; i <= START; i++){
        setPixel(i, c);
        setPixel((pixel - 1) - i, c);
      }
      strip.show();
    }
    
    if(isNewBeat(50)){ 
    if(!isRbClr()) c = nextFixClr();
      newBeat = true;
      countUp = true;
      z = START + 2;
    }    
    
    if(newBeat){
      strip.clear();  
  
      if(countUp) z+=5;
        else z-=5;   

      if(z >= pixel/2 - 1) countUp = false;
      if(z <= START){
        countUp = true;
        newBeat = false;
      }
      
      for(int i = 0; i < z; i++){
        if(clrMode == 6) c = rbClr(rbZ + i);
        setPixel(i, c); 
        setPixel((pixel - 1) - i, c);
      }
        
      strip.show();
    }
  }
}

void cRaceM(){
  waitFactor = 10;
  short z = 0;
  byte farbe = 1;
  uint32_t C, c;
  short refrZ, rbZ;
  double timer;

  while(!nextEffekt){
    if(isNewBeat(100)) clockwise = !clockwise;
      
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
