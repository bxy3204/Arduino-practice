int Dir1 = 28;
int motorLeft = 5;
// motor two
int Dir2 = 29;
int motorRight = 6;
#include "TimerThree.h"
#include <SPI.h>  
#include <Pixy.h>
int pan = 500;
int tilt = 500;
Pixy pixy;
int setcam = 0;
int found = 0;
uint16_t blocks = 0;

void setup() {
  // put your setup code here, to run once:
    pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  pixy.init();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
uint16_t blocks;
blocks = pixy.getBlocks();
while(setcam==0){
  if(blocks){
    pixy.setServos(600,800);
    delay(20);
    blocks=pixy.getBlocks();
    setcam = 1;
  }
  delay(20);
  blocks=pixy.getBlocks();
}
  while(!blocks ){
   forward();
   blocks = pixy.getBlocks();
   delay(20);
   blocks = pixy.getBlocks();
   
 } 
 
 if(found ==1){
   delay(20);
   blocks = pixy.getBlocks();
   while(blocks){
     turnleft();
     delay(20);
     blocks = pixy.getBlocks();
     found = 2;
   }
 }
   
 neutral();
 delay(21);
}
  void forward()
{
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  analogWrite(motorLeft, 150);
  analogWrite(motorRight, 150);
  Serial.println("forward");
}
void reverse(int rspeed)
{
  neutral();
  delay(100);
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, HIGH);
  analogWrite(motorLeft, rspeed);
  analogWrite(motorRight, rspeed);
  
}
 
void neutral()
{
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
  Serial.print("Neutral");
}
/* turnLeft function:
Rotate in place counter clockwise for ltime. 2700 = ~90 deg
*/

void turnleft()
{
  neutral();
  delay(10);
  digitalWrite(Dir1, HIGH);
  analogWrite(motorRight,80);
  analogWrite(motorLeft, 80);
  neutral();
}


