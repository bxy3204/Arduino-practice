#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;
int time;
int setCam=0;
uint16_t blocks;
int fish = 0;

void setup() {
  // put your setup code here, to run once:
pixy.init();
}

void loop() {
  
}
void campos(){
  if(setCam == 0)
  {
   while(!blocks);
   {
    //readCam();
    delay(20);
   }
   pixy.setServos(300,500);
   setCam =1;
  }
}

 
   
