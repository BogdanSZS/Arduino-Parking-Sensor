#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define trigpin 12 //We need trig and echo pin in order to use HC-SR04 Sensor.
#define echopin 11 
#define buzzer 5 //We are using 1 buzzer for the noise to get feedback from the obstacles
#define neopixelpin 9
#define NUMPIXELS 12
#define ISRpin 20

Adafruit_NeoPixel pixels(NUMPIXELS, neopixelpin, NEO_GRB + NEO_KHZ800);
static int range; //We need this variable for our Sensor.
static int Time;
int x = 0;
int Rindex = 0;
int Gindex = 0;
int Bindex = 0;

void setup() {
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  pixels.begin();
  pixels.setBrightness(10);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(neopixelpin, OUTPUT);
  pinMode(ISRpin, INPUT);

  Serial.begin(9600);
}

void receiveEvent(int bytes){
  x = Wire.read();
}

void loop() {
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigpin, LOW);

  Time = pulseIn(echopin, HIGH);
  range = (Time/2) / 29.1;

  Serial.println(range);

  if(range >= 141){
    //digitalWrite(latch, LOW);
    //shiftOut(data, clock, MSBFIRST, leds[8]);
    //digitalWrite(latch, HIGH);
    //We are setting our leds off at over 141cm range
  }

  if(range>=121&&range<=140){
    //digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[0]); //Which led scenario will be work in this range
    //digitalWrite(latch,HIGH);
    pixels.setBrightness(10);
    bzzr(1000); //our buzzer intensity in this range
  }

  if(range>=101&&range<=120){
    //digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[1]);
    //digitalWrite(latch,HIGH);    
    pixels.setBrightness(10);
    bzzr(700);
  }
  
  if(range>=81&&range<=100){
    //digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[2]);
    //digitalWrite(latch,HIGH); 
    pixels.setBrightness(10);
    bzzr(500);
  }
  
  if(range>=61&&range<=80){
    //digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[3]);
    //digitalWrite(latch,HIGH); 
    pixels.setBrightness(10);
    bzzr(300);
  }
  
  if(range>=41&&range<=60){
   // digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[4]);
   // digitalWrite(latch,HIGH);
    pixels.setBrightness(10);
    bzzr(200);
  }
  
  if(range>=21&&range<=40){
   // digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[5]);
   // digitalWrite(latch,HIGH); 
    pixels.setBrightness(10);
    bzzr(100);
  }
  
  if(range>=11&&range<=20){
 //   digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[6]);
    //digitalWrite(latch,HIGH);
    pixels.setBrightness(10);
    bzzr(50);
  }
  
  if(range>=0&&range<=10){
 //   digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[7]);
   // digitalWrite(latch,HIGH);
    //digitalWrite(ISRpin, HIGH);
    
    bzzr(1);
    pixels.setBrightness(50);
    NeoBlink(NUMPIXELS, 250);
  }
}

void bzzr(int time){
  tone(buzzer, 1000);
  delay(time);
  noTone(buzzer);
  delay(time);
}

void NeoBlink(int num, int wait)
{
for (int i = 0; i < num; i++)
{
pixels.setPixelColor(i, 35, 35, 35);
}
pixels.show();
delay(wait);
for (int j = 0; j < num; j++)
{
  if(x == '0'){
    pixels.setPixelColor(j, 255, 0, 0);    
  }

  if(x == '1'){
    pixels.setPixelColor(j, 0, 255, 0);    
  }

  if(x == '2'){
    pixels.setPixelColor(j, 0, 0, 255);    
  }

  if(x == '3'){
    pixels.setPixelColor(j, 114, 9, 183);    
  }
}
pixels.show();
delay(wait);
}
