#include "arduinoFFT.h"
arduinoFFT FFT = arduinoFFT();


#define OFFSET 339 //Ohne USB-Verbindung zum PC
//#define OFFSET 272 //Mit USB-Verbindung zum PC

#define MIKROPIN A7
const float EMPF = 1.3;

int* getFreq(int samples, int frequency){
  unsigned int sampling_period_us = round(1000000*(1.0/frequency));
  int vFreq[samples/2 + 1];
  double vReal[samples];
  double vImag[samples];
  static unsigned long microseconds = micros();
  
  for(int i=0; i<samples; i++){
    microseconds = micros();    //Overflows after around 70 minutes!
    
    vReal[i] = analogRead(MIKROPIN) - OFFSET;
    vImag[i] = 0;

    while(micros() < (microseconds + sampling_period_us));
  }
  
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  
  for(int i = 0; i < samples/2; i++){
    vFreq[i] = vReal[i] + vReal[samples - i]; 
  }
  vFreq[samples/2 + 1] = 0;
  
  return vFreq;
}

int getGesSchnitt(int* vFreq, int samples){
  double schnitt = 0;
  for(int i = 0; i < samples; i++){
    schnitt += vFreq[i];
  }
  schnitt /= samples;
  if(schnitt<0) schnitt = -schnitt;
  return schnitt;
}

boolean getBeat(){ 
  const boolean serial = true;
  const int MIN = 170;

  const float EMPFS = 2.3 * EMPF; //Schnitt des bereits gefilterten Signals
  const int TIMESS = 50;
  static int schnitt = MIN;
  
  int* vFreq = getFreq(32, 3000);
  int wert = vFreq[0] + vFreq[1];

  wert = filterBeat(wert);
  
  if(wert - schnitt > 0){
    schnitt += (wert - schnitt)/TIMESS;
  } else {
    schnitt += 2*(wert - schnitt)/TIMESS;
  }
  
  if(serial){
    Serial.print(wert);
    Serial.print(",");
    Serial.print(schnitt * EMPFS + MIN);
    Serial.print(",");
    Serial.print(schnitt * EMPFS + MIN);
    Serial.print(",");
    Serial.println((wert > schnitt * EMPFS + MIN) * 800);
  }
  
  if(wert > schnitt * EMPFS + MIN){
    return true;
  } else {
    return false;
  }
  
}

int filterBeat(int wert){ //Nimmt TÃ¶ne tieferer Frequenzen raus
  const boolean serial = false;
  
  const int TIMESD1 = 20;
  static int dauerhaft1;

  const int TIMESD2 = 5;          //Greift bei starkem Anstieg ein
  static int dauerhaft2;

  if(serial){
    Serial.print(wert);
    Serial.print(",");
    Serial.print(dauerhaft1 * EMPF);
    Serial.print(",");
    Serial.print(dauerhaft2 * EMPF);
  }

  
  if(wert > dauerhaft1){
    dauerhaft1 += (wert - dauerhaft1 * EMPF) / TIMESD1;
  } else {
    dauerhaft1 += 3 * (wert - dauerhaft1 * EMPF) / TIMESD1;
  }

  if(wert > dauerhaft2){
    dauerhaft2 += (wert - dauerhaft2 * EMPF) / TIMESD2;
  } else {
    dauerhaft2 += 3 * (wert - dauerhaft2 * EMPF) / TIMESD2;
  }
  if(dauerhaft2 > 2*dauerhaft1){
    dauerhaft1 += dauerhaft2;
  }

  wert -= dauerhaft1 * EMPF;
  if(wert < 0) wert = 0;
  return wert;
}

void writeBeat(){
  if(getBeat()){
    digitalWrite(BEATPIN, HIGH);
  } else {
    digitalWrite(BEATPIN, LOW);
  }
}


