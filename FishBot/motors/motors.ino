//motor one
int Dir1 = 26; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 27;
int motorRight = 6;
#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;
int yLoc;
int xLoc;
int width;
int height;
int area;
int color;
void setup() {
  // put your setup code here, to run once:
  pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
}

void loop() {
uint16_t blocks;
blocks = pixy.getBlocks();
 if (blocks)
 {
      xLoc = pixy.blocks[0].x;

      yLoc = pixy.blocks[0].y;

      width = pixy.blocks[0].width;

      height = pixy.blocks[0].height;

      color = pixy.blocks[0].signature;
      
      area = height+width;
 }
 if (area < 500)
 {
    analogWrite(motorLeft, 80);
  analogWrite(motorRight, 80);
 }
 if (area > 500)
 {
    analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
 }

}
