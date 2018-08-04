void clapEvent(){
  static double onceTimer = 0;  //verhindert dass einmaliges klatschen mehrfach gezaehlt wird
  static double twiceTimer = 0; //Bewertet ob zweimal hintereinander geklatscht wurde
  
  if(millis() - onceTimer > 100) {
    onceTimer = millis();
    if(millis() - twiceTimer < 600){
      changeOn = true;   //Im loop wird changeOn auf false gesetzt und "changeOn" ueber Wire zum 1. Arduino weitergegeben
      twiceTimer = 0;
    } else {
      twiceTimer = millis();
    }
  }
}

