// Pixy and SPI libraries for communicating with camera
#include <SPI.h>  
#include <Pixy.h>
#include <Encoder.h>
Pixy pixy;
int blockCheck =0;
int time; //Track time as needed
// Place holders for parameters of objects found
int xLoc;
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
int leftSpeed = 80;
int rightSpeed = 80;

uint16_t blocks; //holds number of objects found

int setCam=0; // check if camera is set to initial position
int fish = 1;  //number of fish caught
//Values for motor control
const int forward = 1;
const int backward = 2;
const int left =3;
const int right = 4;
const int neutral = 5;

//motor one
int Dir1 = 26; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 27;
int motorRight = 6;
int driveFlag=0;

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

}

void loop() {
  readPixy();
  camPos();
  
  drive(fish);
  Serial.println("Yloc:");
  Serial.println(yLoc);
    Serial.println("xloc:");
  Serial.println(xLoc);
  //Serial.println(rightEnc);
}
/*readPixy function"
  Check camera for objects, if nothing found
  wait 20ms and check again to verify no objects are in sight.
  If objects are found, copy the parameters of object.
  Check 4 frames to verify what camera sees
*/
void readPixy()
//uint16_t blocks;
{
 blocks = pixy.getBlocks();
 if(!blocks)
 {
   for (int i=0; i <5; i++)
   {
     delay(20);
     blocks = pixy.getBlocks();
     if(blocks)
     {
       i=5;
     }
   }
 }

 if(!blocks){
   blockCheck--;
   blockCheck = constrain(blockCheck,0,4);
 }
 if (blocks)
 {
   xLoc = pixy.blocks[0].x;
   yLoc = pixy.blocks[0].y;
   width = pixy.blocks[0].width;
   height = pixy.blocks[0].height;
   color = pixy.blocks[0].signature;
   blockCheck = 4;
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
     pixy.setServos(300,600);
     Serial.println(blocks);
    }
  
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
        pixy.setServos(300,600);
        readPixy();
      }
      break;
  }
        
    
  
}
/* drive function:
   Takes the current fish count, and drives towards fish.
   The robot should be positioned close the front of the first fish.
 */
void drive(int fishcount)
{
  //Serial.println("working");
  
  
  switch(fish)
  {
    
    case 1:
    
     leftEnc = motorLEnc.read();
     rightEnc = motorREnc.read();
    
    if(abs(leftEnc) < 14250)
   {
     analogWrite(motorLeft, leftSpeed);
     analogWrite(motorRight, rightSpeed);
     
     leftEnc = motorLEnc.read();
     rightEnc = motorREnc.read();

     if(abs(rightEnc) < abs(leftEnc))
     {
       rightSpeed = constrain(rightSpeed++,75,85);
     }
     if(abs(rightEnc) > abs(leftEnc))
     {
       rightSpeed = constrain(rightSpeed--,75,85);
     }
   }
 
     leftEnc = motorLEnc.read();
     rightEnc = motorREnc.read();
     if(abs(rightEnc)> 14250 && abs(rightEnc) < 19190)
     {
         if(driveFlag==0){  
           analogWrite(motorLeft, 0);
           analogWrite(motorRight, 0);
           digitalWrite(Dir1, HIGH);
           driveFlag++;
         }
       
       analogWrite(motorLeft, leftSpeed);
       analogWrite(motorRight, rightSpeed);
     
     leftEnc = motorLEnc.read();
     rightEnc = motorREnc.read();
     
     
     if(abs(rightEnc) < abs(leftEnc))
     {
       rightSpeed = constrain(rightSpeed++,75,85);
     }
     if(abs(rightEnc) > abs(leftEnc))
     {
       rightSpeed = constrain(rightSpeed--,75,85);
     }
     }
     if(abs(rightEnc)> 19190 && (yLoc < 147 || !blocks)  )
     {
       if(driveFlag==1)
       {
        digitalWrite(Dir1, LOW);
        driveFlag++;
        analogWrite(motorLeft, 0);
        analogWrite(motorRight, 0);
       }
      analogWrite(motorLeft, 80);
      analogWrite(motorRight, 80);
     }
     if(yLoc > 100 && abs(rightEnc) > 19190 && blocks)
     {
       analogWrite(motorLeft, 0);
        analogWrite(motorRight, 0);
        if (xLoc > 221 && blocks)
        {
          digitalWrite(Dir2, HIGH);
          analogWrite(motorLeft, 80);
          analogWrite(motorRight, 80);
        }
        
     }  
      break;
     
    case 2:
       if(!blocks && flag1 < 10)
       { 
        analogWrite(motorLeft, 80);
        analogWrite(motorRight, 80);
        Serial.println("GO!!!!!");
       }
      if(blocks)
       {
        readPixy();
        analogWrite(motorLeft, 0);
        analogWrite(motorRight, 0);
        Serial.println("stop!!");
        flag1++;
        if (flag1 >= 10)
        {
          camFlag =1;
        }
       }
      /* if(camFlag == 2 && !blocks)
       {
         digitalWrite(Dir1, HIGH);
         digitalWrite(Dir2, LOW);
         analogWrite(motorRight,80);
         analogWrite(motorLeft, 80);
         Serial.println("TRUN!!!!!");
       }
      // Serial.println("Blocks:");
       //Serial.print(blocks);
       if (camFlag ==2 && blocks >0)
       {
         camFlag=3;
         analogWrite(motorLeft, 0);
         analogWrite(motorRight, 0);
         Serial.println("stop!!!!!!!");
       }
         
     
     /*if(!blocks)
    { 
      digitalWrite(Dir1, LOW);
      digitalWrite(Dir2, LOW);
      analogWrite(motorLeft,80);
      analogWrite(motorRight, 80);
    }
    if (blocks && camFlag > 0)
    {
      analogWrite(motorLeft, 0);
      analogWrite(motorRight, 0);
    }*/
      break;
    
  }
}

   




