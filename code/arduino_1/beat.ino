void beatEvent(){
  if(digitalRead(BEATPIN)) beat = true;
  else beat = false;
}

boolean wasBeatLastly(int ms){
  static double timer = 0;
  boolean actBeat = isBeat();
  if(actBeat) timer = millis();
  if(millis() - timer > ms) return false; 
  return true;
}

boolean isNewBeat(int ms){
  static double timer = millis();
  
  if(isBeat()  && millis() - timer > ms){
    timer = millis();
    return true; 
  }
  return false;
}

boolean isBeat(){
  return beat;
}

