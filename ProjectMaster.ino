#include <Wire.h>

int x = 0; //if x = 0 => red, x = 1 => green, x = 2 => blue, x = 3 => purple 
int Rindex = 0; 
int Gindex = 0;
int Bindex = 0;

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(9);
  Wire.write(x);
  Wire.endTransmission();

  x++;

  if(x > 3){
    x = 0;
  }
  delay(500);
}
