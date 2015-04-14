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
int blockCheck;
void setup() {
  // put your setup code here, to run once:
pixy.init();
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  readpixy();
  Serial.println(blocks);

}
void readpixy()
//uint16_t blocks;
{
 blocks = pixy.getBlocks();
 if(!blocks)
 {
   for (int i=0; i <5; i++)
   {
     delay(20);
     blocks = pixy.getBlocks();
     if(blocks)
     {
       i=5;
     }
   }
 }

 if(!blocks){
   blockCheck--;
   blockCheck = constrain(blockCheck,0,4);
 }
 if (blocks)
 {
   xLoc = pixy.blocks[0].x;
   yLoc = pixy.blocks[0].y;
   width = pixy.blocks[0].width;
   height = pixy.blocks[0].height;
   color = pixy.blocks[0].signature;
   blockCheck = 4;
 }
}
 
   
