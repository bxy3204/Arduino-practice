// Pixy and SPI libraries for communicating with camera
#include <SPI.h>  
#include <Pixy.h>
#include <Encoder.h>
unsigned long pixyReadTimer = 0;   // This will control how long we hold a valid reading
Pixy pixy;
int blockCheck =0;
int time; //Track time as needed
// Place holders for parameters of objects found
int xLoc;
int fucker;
uint16_t yLoc;
int height;
int width;
int color;
uint16_t j;
Encoder motorLEnc(18,19);
Encoder motorREnc(20,21);
long leftEnc;
long rightEnc;
int camFlag = 0;
int flag1 =0;
int leftSpeed = 90;
int rightSpeed = 90;

uint16_t blocks; //holds number of objects found
int setCam=0; // check if camera is set to initial position
int fish = 0;  //number of fish caught
//Values for motor control
const int forward = 1;
const int backward = 2;
const int left =3;
const int right = 4;
//const int neutral = 5;

//motor one
int Dir1 = 26; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 27;
int motorRight = 6;
int driveFlag=0;
int motorDir =0;

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
  int area;
  readPixy();
  camPos();
  drive();
  area= height + width;
  Serial.println(yLoc);
  /*if ( (xLoc < 180) || blockCheck <= 0)
  {
    turn();
    //Serial.println(xLoc);
  }
  if (xLoc >=180)
  {
    driveFlag=1;
  }
  /*if(driveFlag >0 && yLoc <90)
  {
    fwd();
  }
  if (xLoc > 180)
  {
    neutral();
    Serial.println(xLoc);
  }
  delay(25);
  //Serial.println(xLoc);*/
}
/*readPixy function"

  Check camera for objects, if nothing found

  then for upto 25ms report the previous information

  After 25ms without any valid info, then send back zeros.

  If you have valid information then reset the timer for another 25ms.

*/



 

void readPixy()

//uint16_t blocks;

{

   blocks = pixy.getBlocks();

   if(!blocks)            // if no data

   {

     if (pixyReadTimer < millis())   // and if we are beyond holding the last valid reading

     {                               // then there really is nothing being seen

       xLoc = 0;

       yLoc = 0;

       width = 0;

       height = 0;

       color = 0;

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
/* camPos function:
   On start up, wait untill the camera has started pulling data,
   then move towards first fish.
   pan must be greater than 300.
*/
void camPos()
{
 
  if(!setCam)
  {
    while(!blocks){
     readPixy();
     
     //Serial.println(blocks);
    }
   pixy.setServos(300,700);
   setCam =1;
  }
  switch(fish)
  {
    case 2:
      
      if(!blocks && !camFlag)
      {
        
        
        //readPixy();
        pixy.setServos(1000,550);
        readPixy();
        
      }
      //Serial.println(camFlag);
      if (camFlag ==1)
      {
        time = millis();
        //Serial.println("fuck ya");
        readPixy();
        pixy.setServos(300,700);
        readPixy();
      }
      break;
  }
        
    
  
}
/* drive function:
   Takes the current fish count, and drives towards fish.
   The robot should be positioned close the front of the first fish.
   enc = 4250 90 deg turn
 */
void drive()
{
  //Serial.println("working");
  
  
  switch(fish)
  {
    case 0:
    if (yLoc < 110 && yLoc != 0 && driveFlag==0)
    {
      fwd();
      Serial.println("forward");
      fish--;
      fish = constrain(fish, 0,1);
      time = millis();
    }
    if (yLoc >= 110)
    {
      //driveFlag++;
      neutral();
      Serial.println("stop");
      if (millis() - time > 3000)
      {
      fish++;
      driveFlag=0;
      }
      fish = constrain(fish,0,1);
      motorLEnc.write(0);
 
    }
    break;
    case 1:
       leftEnc = motorLEnc.read();
      if(abs(leftEnc)  < 4150 && !driveFlag)
      {
        turn();
      }
      if(abs(leftEnc) > 4150 && !driveFlag)
      {
        driveFlag=1;
        motorLEnc.write(0);
      }
      if(abs(leftEnc) < 8750 && driveFlag ==1 )
      {
        fwd();
      }
      
     if(abs(leftEnc) > 8720 && driveFlag==1 )
      {
        
        neutral();
        driveFlag=2;
        
        motorLEnc.write(0);
      }
      if(driveFlag==2 && abs(leftEnc) < 4250)
      {
        turnRight();
        time=millis();
      }
      if(driveFlag ==2 && leftEnc > 4250)
      {
        neutral();
       //fish++;
       if (millis() - time > 3000)
       {
        fish++;
        driveFlag=0;
        motorLEnc.write(0);
       }
      }
   
        
      break;
    case 2:
     /*leftEnc=motorLEnc.read();
     if(leftEnc < 2000)
     {
       fwd();
     }
     if(leftEnc > 2000)
     {
       neutral();
     }*/
    break;
  }
  
}
void fwd()
{
  if(motorDir!= 0)
  {
    neutral();
  }
    motorDir =0;
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  analogWrite(motorLeft, leftSpeed);
  analogWrite(motorRight, rightSpeed);
}
void turn()
{
  if(motorDir !=1)
  {
    neutral();
  }
  motorDir =1;
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, LOW);
  analogWrite(motorLeft, leftSpeed);
  analogWrite(motorRight, rightSpeed);
}
void neutral()
{
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
}
  
void rvrs()
{
  if(motorDir !=2)
  {
    neutral();
  }
  motorDir=2;
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, HIGH);
  analogWrite(motorLeft, leftSpeed);
  analogWrite(motorRight, rightSpeed);
}
void turnRight()
{
    if(motorDir !=3)
  {
    neutral();
  }
  motorDir =3;
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, HIGH);
  analogWrite(motorLeft, leftSpeed);
  analogWrite(motorRight, rightSpeed);
}

