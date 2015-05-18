#include <Stepper.h>
#define STEPS 32 //32 step stepper
//Bin locations based on color
const int red = 1;
const int blue =  2;
const int green = 3;
const int yellow = 4; 
Stepper binFloor = Stepper(STEPS,46,50,48,52); //Colored bins
Stepper bin = Stepper(STEPS,28,30,29,31); //Entire bin
//Stepper bin = Stepper(STEPS,28,30,29,31); //Entire binFloor
int binLoc = 1; // Location of bin(1:red 2:blue 3:green 4:yellow)
int binMove = 0; // number of steps to move bin
int drop = 0; //Bucket location for drop off
void setup() {
  
  
  bin.setSpeed(500);
  binFloor.setSpeed(500);
  
}
/* findBin Function:
   input color of desired binFloor, find the difference
   between the desired binFloor location and
   the current binFloor location. Multiply by a factor of
   695 (steps between each binFloor);
*/
void findBin(int color)
{
  binMove = (color - binLoc) * -695;
  bin.step(binMove);
  binLoc = color;
}
/* dropOff Function:
    The first time this function is called, the bin will be moved
    into position to drop off the first set of fish, then move the
    bins floor to drop the fish. Subsequent calls will advance the 
    bin one position to drop off the next set of of fish.
 */
void dropOff()
{
 // findBin(-yellow);
//  bin.step(-695);
  binFloor.step(-650);//negative to drop
  binLoc = 1;
}
void loop() {
  findBin(red);
  delay(2000);
  findBin(blue);
  delay(2000);
  findBin(green);
  delay(2000);
  findBin(yellow);
  delay(2000);
 /* dropOff();
  delay(10000);*/
  
}
