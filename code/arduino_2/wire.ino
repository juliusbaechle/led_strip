void writeWire(char* s, int num){
  char arr[20];
  strcpy(arr, s);
  char numarr[6];
  strcat(arr, itoa(num, numarr, 10));
  writeWire(arr);
}

//  music, velocity, brightness, snlenght, effektN, effektM, clrMode, color,
//  changeClockwise, changeOneStrip, changeOn, changeContrary, changeFade

void writeWire(char* s){
  Wire.beginTransmission(1);
  Wire.write(s);
  Wire.endTransmission();
  delay(50);
}
