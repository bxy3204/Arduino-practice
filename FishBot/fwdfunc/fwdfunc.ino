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
int leftSpeed = 151;
int rightSpeed = 150;

uint16_t blocks; //holds number of objects found
int setCam = 0; // check if camera is set to initial position
int fish = 0;  //number of fish caught
//Values for motor control
const int forward = 1;
const int backward = 2;
const int left = 3;
const int right = 4;
//const int neutral = 5;

//motor one
int Dir1 = 26; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 27;
int motorRight = 6;
int driveFlag = 0;
int motorDir = 0;

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
}

void loop() {
 if(!driveFlag){
  fwd(12000);
 }

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
  if (x > leftEnc)
  {
    digitalWrite(Dir1, LOW);
    digitalWrite(Dir2, LOW);
    analogWrite(motorLeft, leftSpeed);
    analogWrite(motorRight, rightSpeed);
  }
  if (x < leftEnc)
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
