#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;
int time;

int xLoc;
int yLoc;
int height;
int width;
int color;
uint16_t blocks;
int setCam=0;
int fish = 0;
const int forward = 1;
const int backward = 2;
const int left =3;
const int right = 4;
const int neutral = 5;
int drivetest = 0;

//motor one
int Dir1 = 26; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 27;
int motorRight = 6;

void setup() {
  // put your setup code here, to run once:
  pixy.init();
    pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  Serial.begin(9600);

}

void loop() {
 // put your main code here, to run repeatedly:
 while (drivetest <3 )
 {
   drive(forward);
   delay(5500);
   drivetest += 1;
   drive(neutral);
   delay(500);
   drive(left);
   delay(3200);
   drive(neutral);
   delay(1000);
   drive(forward);
   
 }

}
void drive(int direct)
{
  switch(direct)
  {
    case 1:
      digitalWrite(Dir1, LOW);
      digitalWrite(Dir2, LOW);
      analogWrite(motorLeft, 80);
      analogWrite(motorRight, 80);
      break;
    case 2:
      digitalWrite(Dir1, HIGH);
      digitalWrite(Dir2, HIGH);
      analogWrite(motorLeft,80);
      analogWrite(motorRight, 80);
      break;
    case 3:
      digitalWrite(Dir1, HIGH);
      digitalWrite(Dir2, LOW);
      analogWrite(motorRight,80);
      analogWrite(motorLeft, 80);
      
      break;
    case 4:
      digitalWrite(Dir1, LOW);
      digitalWrite(Dir2, HIGH);
      analogWrite(motorRight,80);
      analogWrite(motorLeft, 80);
      break;
    case 5:
      analogWrite(motorLeft, 0);
      analogWrite(motorRight, 0);
      break;
  }
}
