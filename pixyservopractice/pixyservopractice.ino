
#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

void setup() {
  // put your setup code here, to run once:
   pixy.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t blocks;
  blocks = pixy.getBlocks();
  pixy.setServos(500,900); //range = 0-1000, dont try to rapidly set position
  delay(1000);
  // pixy.setServos(0,0);
  
}
