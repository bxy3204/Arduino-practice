#include <SPI.h>  
#include <Pixy.h>
//motor one
int Dir1 = 28; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 29;
int motorRight = 6;

Pixy pixy;
int time;
int setCam=0;
uint16_t blocks;
int fish = 0;
const int forward = 1;
const int backward = 2;
const int left =3;
const int right = 4;
const int neutral = 5;

void setup() {
  // put your setup code here, to run once:
pixy.init();
      pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, LOW);
}

void loop() {
  drive(left);
  
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
