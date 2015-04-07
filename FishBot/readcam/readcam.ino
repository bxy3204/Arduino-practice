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
void setup() {
  // put your setup code here, to run once:
pixy.init();

}

void loop() {
  // put your main code here, to run repeatedly:

}
void readpixy()
//uint16_t blocks;
{
 blocks = pixy.getBlocks();
 if(!blocks)
 {
   delay(20);
   blocks = pixy.getBlocks();
 }
 if(!blocks){
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
 
   
