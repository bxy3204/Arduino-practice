#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;
int pan = 550;
int tilt = 550;
int time;
int oldtilt;
int oldpan;
int fishcount = 0;
int x;

void setup() {
  // put your setup code here, to run once:
  pixy.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t blocks;
  uint16_t blocks2;
  blocks = pixy.getBlocks();
  pixy.setServos(0,0);
 while(fishcount == 0){
   pixy.setServos(0,0);
   while(!blocks){
 
     blocks = pixy.getBlocks();
   }
   while(blocks){
    x = pixy.blocks[0].x;
    if (x < 140){
      pixy.setServos(200, 650);
    }
    if (x > 160){
      pixy.setServos(900,650);
    }
    blocks = pixy.getBlocks();
   }
  }
 
}
