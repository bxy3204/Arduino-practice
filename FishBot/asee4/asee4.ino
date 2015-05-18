
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
int lSpeed=80;
int rSpeed = 80;
long track=0;
long track2 =0;
long error;
int xLoc;
uint16_t yLoc;
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
int leftSpeed = 80;  //motor speed. pwm 60-254
int rightSpeed = 80;
int grabFlag = 0;
#include <Servo.h>
int grabPos = 0;
int dropFlag = 0;
Servo myservo;  // create servo object to control a servo
uint16_t blocks; //holds number of objects found
int setCam = 0; // check if camera is set to initial position
int fish = 0;  //number of fish caught
//Values for motor control
//const int forward = 1;
const int backward = 2;
const int left = 3;
const int right = 4;
//const int neutral = 5;
int arm;
//motor one
int Dir1 = 36; //motor direction. low = forward
int motorLeft = 6;
// motor two
int Dir2 = 37;
int motorRight = 5;
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
  myservo.attach(9);
  myservo.write(140);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW); //Low towards bucket
  int arm = 0;
  delay(3000);
}

void loop() {
 Serial.println(driveFlag);
if(!driveFlag) //8000 foward
{
  fwd(7600);
}
if(driveFlag==1) 
{
  turn(2175);
  delay(100);
}
if(driveFlag==2)
{
  fwd(700);
  time = millis();
}
if(driveFlag == 3 && (millis() - time) > 3000)
{
  driveFlag=0;
}
/*if(driveFlag ==1)
{
  turn(1800);
}*/

Serial.println(driveFlag);
  /*turn(4500);
  readPixy();
  Serial.println(area);
  if (dropFlag == 0)
  {
    liftDown();
  }
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

void fwd(long distance)
{
  rightEnc = motorREnc.read();
  leftEnc = motorLEnc.read();
    track = motorLEnc.read();
  track2 = motorREnc.read();
  error = abs(track) - abs(track2);
error = round(error);
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
  /* forward();
   if (xLoc > 150)
   {
     leftSpeed=0;
   }
   if(xLoc < 160)
   {
     leftSpeed=80;
   }*/

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

    pixyReadTimer = millis() + 25;  // Max time to hold an old value is 25 ms.

  }
}
void camAppr()
{
  area = width + height;
  if (area < 200 && area > 0) {
    forward();
  }
  if (area > 200)
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
void grab(int pos)
{
  myservo.write(pos);
  grabFlag++;
}
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

