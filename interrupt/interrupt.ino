#include "TimerThree.h"
#include <SPI.h>  
#include <Pixy.h>
Pixy pixy;

void setup() {
  // put your setup code here, to run once:
  Timer3.initialize();
  pixy.init();
  Timer3.attachInterrupt(getfish,20);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void getfish(void)
{
  int blocks;
  blocks = pixy.getBlocks();
}
