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

//motor one
int Dir1 = 28; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 29;
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
  readPixy();
  camPos();
  
  if(fish == 0 && color > 0 && yLoc < 180)
  {
    //drive(forward);
    
  }
  if (yLoc >180)
  {
    drive(neutral);
    fish = 1;
    Serial.println("yyy");
  }
  if ((time - millis()) < 2000 && fish == 1)
    {
      //drive(forward);
      //Serial.println(time);
    }
}

void readPixy()

//uint16_t blocks;
{
  
 blocks = pixy.getBlocks();
 if(!blocks)
 {
   delay(20);
   blocks = pixy.getBlocks();
   
 }
 if(!blocks){
   xLoc = 0;
   yLoc = 0;
   width = 0;
   height = 0;
   color = 0;
   color = 0;
   
 }
 if (blocks)
 {
   xLoc = pixy.blocks[0].x;
   yLoc = pixy.blocks[0].y;
   width = pixy.blocks[0].width;
   height = pixy.blocks[0].height;
   color = pixy.blocks[0].signature;
   
 }
}
void camPos()
{
  if(!setCam)
  {
    while(!blocks){
     readPixy();
     pixy.setServos(300,500);
    }
  
   setCam =1;
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

   


