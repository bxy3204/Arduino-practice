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
int x = 0;
// Pixy and SPI libraries for communicating with camera
#include <SPI.h>
#include <Pixy.h>
#include <Encoder.h>
unsigned long pixyReadTimer = 0;   // This will control how long we hold a valid reading
Pixy pixy;
int blockCheck = 0;
int time; //Track time as needed
// Place holders for parameters of objects found
int lSpeed=80; //speed for the left motor
int rSpeed = 80; //speed for the right motor 
long track=0; //track the number of revs from encoder for proportional control
long track2 =0; // track the number of revs from the second encoder for proportional control
long error; // difference between encoders
int xLoc; // x location of object in camera
uint16_t yLoc; //t location of object in camera
int height; //height of object in camera
int width; //widrth of object in camera
int color; //color of object in camera
uint16_t j; //testing variable
Encoder motorLEnc(18, 19); //left encoder
Encoder motorREnc(20, 21); //right encoder
long leftEnc; //values from left encoder
long rightEnc; //values from right encoder
int camFlag = 0; //flag to determine when camera has indicated a condition is met
int flag1 = 0; //generic flag for conditions
int leftSpeed = 80;  //motor speed. pwm 60-254
int rightSpeed = 80;
int grabFlag = 0; //flag to indicate fish has been grabbed
#include <Servo.h> //servo library
int grabPos = 0; //pos of servo controlling claw
int dropFlag = 0; //flag to indicate location of arm
Servo myservo;  // create servo object to control a servo
uint16_t blocks; //holds number of objects found
int setCam = 0; // check if camera is set to initial position
int fish = 0;  //number of fish caught

int arm; //steps for arm stepper
//motor one
int Dir1 = 36; //left motor direction. low = forward
int motorLeft = 6; //left motor drive pin. 
// motor two
int Dir2 = 37; //right motor direction low = forward
int motorRight = 5; // right motor drive pin. 
int driveFlag = 0; //flag to indicate drive condition is met
int i;
int area; //height + width from camera
int binFlag=0; //flag to indicate bin condition is met
void setup() {
  pixy.init(); //initialize camera
  pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  Serial.begin(9600);//serial print for testing
  Serial.println("start"); //indicate arduino is communicating with PC
  myservo.attach(9); //claw servo attached to pin 9
  myservo.write(140); //set claw servo to open
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW); //Low towards bucket
  int arm = 0; //set arm steps to 0
  delay(3000); //give camera and claw time to setup
  bin.setSpeed(500); //set speed of bin stepper
  binFloor.setSpeed(500); //set speed of the floor stepper
}

void loop() {
 //Use flags to change states.
  readPixy();
  //Serial.println(area);
 //Approach the fish to a set distance and line up to grab. 
  if (!driveFlag)
  {
    arm=0;
    camAppr();
  }
  //robot will stop an drop arm
  if(driveFlag==1 && !dropFlag)
  {
    liftDown();
  }
  //find correct bin for color
  if(!binFlag && dropFlag==1)
  {
    findBin(color);
  }
  // drive forward to grab/pushing fish into alignment
  if(driveFlag==1 && dropFlag==1)
  {
    fwd(2000);
  }
  //grab fish, wait a small amount of time to give servo time to close
  if(driveFlag==2 && dropFlag==1)
  {
    driveFlag++;
    grab(90);
    arm=0;
    time = millis();
  }
  //lift arm up for drop off
  if(grabFlag ==1 && arm !=1350 && ( millis()-time) > 500)
  {
    liftUp();
  }
  //release fish
  if(grabFlag==1 && arm == 1350 && driveFlag <4)
  {
    grab(135);
    driveFlag++;
    time=millis();
  }
  //clear flags to start again
  if((millis() - time)> 3000 && driveFlag == 4 && fish <2)
  {
    driveFlag=0;
    arm=0;
    dropFlag=0;
    grabFlag=0;
    fish++;
    binFlag=0;
  }
  //temporary stop
  if(fish==2)
  {
    delay (100000);
  }
 //if (fish==4)
 // {
   /* x=0;
    while(x < 500)
    {
     liftDown();
     x++;
    } */
  //  dropOff();
   // delay(3000);
   // fish++;
 //}
    
 /* if (driveFlag < 1 && dropFlag > 0) {
    camAppr();
  }*/
  /*if(fish ==0 && !grabFlag && dropFlag>0)
  {
    //Serial.println("grab");
    grab(90);
    arm=0;
    time = millis();
  }
  if(grabFlag ==1 && arm !=1350 && ( millis()-time) > 500)
  {
    liftUp();
    fish++;
  }
  if(grabFlag==1 && arm == 1350 && driveFlag <2)
  {
    grab(135);

  }
  if(grabFlag ==2 && driveFlag <1)
  {
    fwd(7500);
  }

  /* if(driveFlag == 1)
  {
    turn(2500);
  }*/

}
//move forward (distance) number of encoder ticks.
//A value is sent to the function, and the distance is tracked
// untill that value is met. Continue sending the same distance
// untill the distance is reached and the flag is incremented.
void fwd(long distance)
{
  rightEnc = motorREnc.read();
  leftEnc = motorLEnc.read();
    track = motorLEnc.read();
  track2 = motorREnc.read();
  error = abs(track) - abs(track2);
error = round(error);
//adjust speed to drive a straight line
if(error < 0 )
{
  lSpeed=constrain(lSpeed + 8, 60,90 );
  rSpeed = constrain(rSpeed - 10,60,90);
}
if(error > 1)
{
  lSpeed=constrain(lSpeed- 8, 60,90 );
  rSpeed = constrain(rSpeed + 10,60,90);

  }
  if (x == 0)
  {
    x = distance;
    motorLEnc.write(0);
    motorREnc.write(0);
    lSpeed=80;
    rSpeed=80;
    leftEnc = motorLEnc.read();
  }
  if (x > abs(leftEnc))
  {
    digitalWrite(Dir1, HIGH);
    digitalWrite(Dir2, HIGH);
    analogWrite(motorLeft, lSpeed);
    analogWrite(motorRight, rSpeed);
  }
  if (x < abs(leftEnc))
  {
    neutral();
    driveFlag++;
    x = 0;
  }

}
//stop the motors
void neutral()
{
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
}
//turn left (distance) number of encoder ticks.
//A value is sent to the function, and the distance is tracked
// untill that value is met. Continue sending the same distance
// untill the distance is reached and the flag is incremented.
void turn(long distance)
{
  rightEnc = motorREnc.read();
  leftEnc = motorLEnc.read();
  if (x == 0)
  {
    x = distance;
    motorLEnc.write(0);
    leftEnc = motorLEnc.read();
  }
  if (x > abs(leftEnc))
  {
    digitalWrite(Dir1, HIGH);
    digitalWrite(Dir2, LOW);
    analogWrite(motorLeft, leftSpeed);
    analogWrite(motorRight, rightSpeed);
  }
  if (x < abs(leftEnc))
  {
    neutral();
    driveFlag++;
    x = 0;
  }
}
//move backwards (distance) number of encoder ticks.
//A value is sent to the function, and the distance is tracked
// untill that value is met. Continue sending the same distance
// untill the distance is reached and the flag is incremented.
void rvrs(long distance)
{
  rightEnc = motorREnc.read();
  leftEnc = motorLEnc.read();
  if (x == 0)
  {
    x = distance;
    motorLEnc.write(0);
    leftEnc = motorLEnc.read();
  }
  if (x > abs(leftEnc))
  {
    digitalWrite(Dir1, HIGH);
    digitalWrite(Dir2, HIGH);
    analogWrite(motorLeft, leftSpeed);
    analogWrite(motorRight, rightSpeed);
  }
  if (x < abs(leftEnc))
  {
    neutral();
    driveFlag++;
    x = 0;
  }
}

//read from camera and save whats found. This function needs to be called frequently (every 20ms ideally) to clear the buffer
void readPixy()

//uint16_t blocks;

{
  blocks = pixy.getBlocks();

  if (!blocks)           // if no data

  {

    if (pixyReadTimer < millis())   // and if we are beyond holding the last valid reading

    { // then there really is nothing being seen

      //xLoc = 0;

      // yLoc = 0;

      //width = 0;

      //height = 0;

      //color = 0;

    }

  }

  else  // Some good info from the camera

  {

    xLoc = pixy.blocks[0].x;

    yLoc = pixy.blocks[0].y;

    width = pixy.blocks[0].width;

    height = pixy.blocks[0].height;

    color = pixy.blocks[0].signature;
    
    area = height + width;

    pixyReadTimer = millis() + 25;  // Max time to hold an old value is 25 ms.

  }
}
//camAppr(): use the camera to apprach the fish. Stops the robot when a set distance is reached, and turns toward the fish while driving.
void camAppr()
{
  area = width + height;
  if (area < 120 && area > 0) {
    if(xLoc > 160)
    {
      rightSpeed = 95;
      leftSpeed= 75;
    }
    if(xLoc < 160)
    {
      rightSpeed = 75;
      leftSpeed = 95;
    }
    forward();
  }
  if (area > 120)
  {
    time = millis();
    neutral();
    driveFlag++;
  }
}
//drive forward indefinately
void forward()
{
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, HIGH);
  analogWrite(motorLeft, leftSpeed);
  analogWrite(motorRight, rightSpeed);
}
//grab(): opens and closes the claw. 90 for close, 140 for open
void grab(int pos)
{
  myservo.write(pos);
  grabFlag++;
}
//liftUp() lifts the arm up, 1350 steps to reach bucket
void liftUp()
{
  digitalWrite(25, LOW);
  if (arm < 1350) {
    digitalWrite(24, HIGH);
    delayMicroseconds(1000);

    digitalWrite(24, LOW);
    delayMicroseconds(1000);
  }
  arm++;
}
//liftDown() lifts the arm up, 1350 steps to reach bucket
void liftDown()
{
  digitalWrite(25, HIGH);
  if (arm < 1350) {
    digitalWrite(24, HIGH);
    delayMicroseconds(1000);

    digitalWrite(24, LOW);
    delayMicroseconds(1000);
  }
  arm++;
  if (arm == 1350)
  {
    dropFlag++;
  }


}
//findBin() moves the bin to the current color. location is relative, bucket must start closed.
void findBin(int colour)
{
  binMove = (colour - binLoc) * 695;
  bin.step(binMove);
  binLoc = colour;
  binFlag++;
}
/* dropOff Function:
    The first time this function is called, the bin will be moved
    into position to drop off the first set of fish, then move the
    bins floor to drop the fish. Subsequent calls will advance the 
    bin one position to drop off the next set of of fish.
 */
void dropOff()
{
  findBin(yellow);
  bin.step(695);
  binFloor.step(650);//negative to drop
  binLoc = 1;
}

