#define trigpin 12 //We need trig and echo pin in order to use HC-SR04 Sensor.
#define echopin 11
#define clock 10 //Clock, latch and data pins are about 74HC595 shift register
#define latch 9 //These pins are needed for the LEDs
#define data 8 
#define buzzer 5 //We are using 1 buzzer for the noise to get feedback from the obstacles

static int range; //We need this variable for our Sensor.
static int Time;

void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  Serial.begin(9600);
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
    bzzr(1000); //our buzzer intensity in this range
  }

  if(range>=101&&range<=120){
    //digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[1]);
    //digitalWrite(latch,HIGH);    
    bzzr(700);
  }
  
  if(range>=81&&range<=100){
    //digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[2]);
    //digitalWrite(latch,HIGH); 
    bzzr(500);
  }
  
  if(range>=61&&range<=80){
    //digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[3]);
    //digitalWrite(latch,HIGH); 
    bzzr(300);
  }
  
  if(range>=41&&range<=60){
   // digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[4]);
   // digitalWrite(latch,HIGH);
    bzzr(200);
  }
  
  if(range>=21&&range<=40){
   // digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[5]);
   // digitalWrite(latch,HIGH); 
    bzzr(100);
  }
  
  if(range>=11&&range<=20){
 //   digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[6]);
    //digitalWrite(latch,HIGH);
    bzzr(50);
  }
  
  if(range>=0&&range<=10){
 //   digitalWrite(latch,LOW);
    //shiftOut(data,clock,MSBFIRST,leds[7]);
   // digitalWrite(latch,HIGH);
    bzzr(1);
  }
}

void bzzr(int time){
  tone(buzzer, 1000);
  delay(time);
  noTone(buzzer);
  delay(time);
}
