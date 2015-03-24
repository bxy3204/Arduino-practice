
#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;





// connect motor controller pins to Arduino digital pins
// motor one
int enA = 8;

// motor two
int enB = 10;

int x;
int width;
void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pixy.init();
  Serial.begin(9600);
  Serial.print("Starting...\n");
  
}


 
  
void forward()
{
  
  analogWrite(enA, 80);
  analogWrite(enB, 80);
  Serial.print("forward");
}
 
void neutral()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  Serial.print("Neutral");
}

void loop()
{

  uint16_t blocks;
  blocks = pixy.getBlocks();
  x = pixy.blocks[0].x;
  width = pixy.blocks[0].width;
  
  if(blocks)
  {
    if (width < 250)
    {
      forward();
      while (width < 250 )
      {
      blocks = pixy.getBlocks();
      width = pixy.blocks[0].width;
      Serial.print(width);
      }
      neutral();
    }
    else{
      neutral();
    }
  }
  
}


