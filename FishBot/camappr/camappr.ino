#include <Stepper.h>
#define STEPS 32
Stepper arm = Stepper(STEPS,41,45,43,47);//Positive towards bucket
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
int xLoc;
int fucker;
uint16_t yLoc;
int camAppFlag;
int height;
int width;
int color;
uint16_t j;
Encoder motorLEnc(18, 19);
Encoder motorREnc(20, 21);
long leftEnc;
long rightEnc;
int camFlag = 0;
int flag1 = 0;
int leftSpeed = 80;
int rightSpeed = 80;


uint16_t blocks; //holds number of objects found
int setCam = 0; // check if camera is set to initial position
int fish = 0;  //number of fish caught
//Values for motor control
//const int forward = 1;
const int backward = 2;
const int left = 3;
const int right = 4;
//const int neutral = 5;

//motor one
int Dir1 = 36; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 37;
int motorRight = 6;
int driveFlag = 0;
int motorDir = 0;
int i;
int area;
void setup() {
  // put your setup code here, to run once:
  pixy.init(); //initialize camera
  pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  Serial.begin(9600);
  Serial.println("start");
  arm.setSpeed(300);
  delay(3100);
  
}

void loop() {
 readPixy();
 camAppr();
 //turnLeft();
// fwd(10000);
//turnRight();
 //Serial.println(camAppFlag);
 //Serial.println("xLoc");
 Serial.println(area);
 if(driveFlag==1)
 {
   //fwd(5000);
 }
 //forward();
 

}

void fwd(long distance)
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
void neutral()
{
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
}
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


void readPixy()

//uint16_t blocks;

{

   blocks = pixy.getBlocks();

   if(!blocks)            // if no data

   {

     if (pixyReadTimer < millis())   // and if we are beyond holding the last valid reading

     {                               // then there really is nothing being seen

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
      
      area = height+width;

      pixyReadTimer = millis() + 25;  // Max time to hold an old value is 25 ms.

   }
}
void turnLeft()
{
      digitalWrite(Dir1, LOW);
    digitalWrite(Dir2, HIGH);
    analogWrite(motorLeft, 0);
    analogWrite(motorRight, rightSpeed);
}
void turnRight()
{
      digitalWrite(Dir1, HIGH);
    digitalWrite(Dir2, LOW);
    analogWrite(motorLeft, leftSpeed);
    analogWrite(motorRight, 0);
}
void camAppr()
{
  
 if(area < 100 && !camAppFlag && area != 0){
   forward();
  // camAppFlag++;
 }
 if (area > 100 && !camAppFlag)
 {
   camAppFlag++;
 }
 if(area > 100 && xLoc >165 && camAppFlag==1 && !driveFlag)
{
  turnRight();
  Serial.println("right");
}
if((area > 100 && area > 0) && xLoc < 159 && camAppFlag==1&& !driveFlag)
{
  turnLeft();
  Serial.println("left");
}
if (area > 100 && (xLoc >165 && xLoc < 170)&&!driveFlag)
{
 time = millis();
 neutral();
 driveFlag++;
}
}
void forward()
{
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, HIGH);
  analogWrite(motorLeft, leftSpeed);
  analogWrite(motorRight, rightSpeed);
}

