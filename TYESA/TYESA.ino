//motor one
int Dir1 = 28; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 29;
int motorRight = 6;
#include <SPI.h>  //SPI library to communicate with pixy
/*Pixy library. 
Commands:
 .getblocks() : retrieve data from pixy
 .blocks[z].x :retrive x location of block number z
 .blocks[z].y : retrive y location of block numberz
 .blocks[z].width : width of block z
 .blocks[z].height : height of block z
 */
#include <Pixy.h> 
Pixy pixy;  // New pixy object
int setCam1 = 0;
int found = 0; // Determines if fish is found

void setup() {
  // Establish motor pins as outputs, and direction as forward
  pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  pixy.init(); //initialize the camera
  Serial.begin(9600); //Start serial interface for debugging
}

void loop() {
uint16_t blocks;
blocks = pixy.getBlocks();
 //Set the camera to look down at start, so it does 
 // not see anything.
 while(setCam1==0){
  delay(20); //pixy sends new data apprx. every
             // 20 ms, and needs to be called frequently
             // so the data does not get backed up
  blocks=pixy.getBlocks();
  setCam(600,800);
 }
 // Drive forward untill a fish is found
  while(!blocks ){
   forward();
   blocks = pixy.getBlocks();
   delay(20);
   blocks = pixy.getBlocks();
   found = 1;
 } 
 // Once fish is found, turn untill the fish 
 // is no longer in sight, which 
 // should put the robot in place to grab the fish
 if(found ==1){
   delay(20);
   blocks = pixy.getBlocks();
   while(blocks){
     turnleft();
     delay(20);
     blocks = pixy.getBlocks();
     found = 2;
   }
 }
 //Stop at fish. slightly longer delay so 
 // pixy isnt being called before new data comes in. 
 neutral();
 delay(21);
}
/*forward() function:
  turn off both wheels, and wait a small amount of
  time to ensure both wheels are stopped in case
  the wheels were previously in reverse.
  80 PWM is a good all around speed
  */
  void forward()
{
  neutral();
  delay(10);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  analogWrite(motorLeft, 80);
  analogWrite(motorRight, 80);
  Serial.println("forward");
}

void reverse()
{
  neutral();
  delay(10);
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, HIGH);
  analogWrite(motorLeft,80);
  analogWrite(motorRight, 80);
  
}
 /* neutral() function
    turn off both motors
    */
void neutral()
{
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
  Serial.print("Neutral");
}
/* turnLeft function:
Rotate in place counter clockwise
*/

void turnleft()
{
  neutral();
  delay(10);
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, LOW);
  analogWrite(motorRight,80);
  analogWrite(motorLeft, 80);
  neutral();
}
/* setCam() function:
   set camera to designated pan / tilt locations.
   values are 0 - 1000 with 500,500 being the center.
   0,0 is looking straight up and left*/
void setCam(int pan, int tilt){
    pixy.setServos(pan, tilt);
    setCam1 = 1;
}
 

