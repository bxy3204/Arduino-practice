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


int x;
int width;
int height;
int area;
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
  
x=1;
}

void loop() {
  // put your main code here, to run repeatedly:
 
  pixy.setServos(500,900);
  
  delay(1000);
  analogWrite(motorLeft, 60);
  analogWrite(motorRight, 135);
  /*if(blocks)
  {
    neutral();
    blocks = pixy.getBlocks();
    width = pixy.blocks[0].width;
    Serial.println(blocks);
    Serial.println(width);
    delay(1500);
    
  }
    if (area < 600)
    {
      forward();
      while (area < 600)
      {
       blocks = pixy.getBlocks();
       width = pixy.blocks[0].width;
       height = pixy.blocks[0].height;
       area = height + width;
       delay(1000);
      Serial.println(area);
      }
      neutral();
    }
    else{
      neutral();
    }
  }*/
 
   
}
void forward()
{
  
  analogWrite(motorLeft, 80);
  analogWrite(motorRight, 80);
  Serial.print("forward");
}
 
void neutral()
{
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
  Serial.print("Neutral");
}

 
  
