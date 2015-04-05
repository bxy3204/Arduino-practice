// connect motor controller pins to Arduino digital pins
// motor one
int Dir1 = 28;
int motorLeft = 5;
// motor two
int Dir2 = 29;
int motorRight = 6;

#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;


int y;
int x;
int width;
int height;
int area;
int blockarray;
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
void forward(int fspeed)
{
  neutral();
  delay(100);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  analogWrite(motorLeft, fspeed);
  analogWrite(motorRight, fspeed);
  Serial.print("forward");
}
void reverse(int rspeed)
{
  neutral();
  delay(100);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  analogWrite(motorLeft, rspeed);
  analogWrite(motorRight, rspeed);
  Serial.print("forward");
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

/*void turnleft(int ltime)
{
  neutral();
  delay(100);
  digitalWrite(Dir1, HIGH);
  analogWrite(motorRight,80);
  analogWrite(motorLeft, 80);
  delay(ltime);
  neutral();
}*/
void loop() {
  // put your main code here, to run repeatedly:
  uint16_t blocks;
  blocks = pixy.getBlocks();
  y = pixy.blocks[0].y;
  x = pixy.blocks[0].x;
  width = pixy.blocks[0].width;
  height = pixy.blocks[0].height;
  area = height + width;
  if(blocks)
  {
    if (y < 100)
    {
      forward(80);
      while (y < 100)
      {
       blocks = pixy.getBlocks();
       y = pixy.blocks[0].y;
      Serial.println(area);
      }
      neutral();
    }
    else{
      neutral();
    }
  /*if (x<100)
  {
    turnleft();
    while(x<100);
    {
    blocks = pixy.getBlocks();
    x = pixy.blocks[0].x;
    }
    neutral();
  }
    else
    {
      neutral();
    }*
  }
}

  
  

