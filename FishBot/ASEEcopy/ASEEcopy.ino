// Pixy and SPI libraries for communicating with camera
#include <SPI.h>  
#include <Pixy.h>
#include <Encoder.h>
Pixy pixy;

int time; //Track time as needed
// Place holders for parameters of objects found
int xLoc;
uint16_t yLoc;
int height;
int width;
int color;
uint16_t j;
Encoder motorL(20, 21);
Encoder motorR(2, 3);
int camFlag = 0;
int flag1 =0;


uint16_t blocks; //holds number of objects found

int setCam=0; // check if camera is set to initial position
int fish = 1;  //number of fish caught
//Values for motor control


//motor one
int Dir1 = 26; //motor direction. low = forward
int motorLeft = 5; //motor speed. pwm 60-254
// motor two
int Dir2 = 27;
int motorRight = 6;

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
}
/*readPixy function"
  Check camera for objects, if nothing found
  wait 20ms and check again to verify no objects are in sight.
  If objects are found, copy the parameters of object.
*/
void readPixy(){


  
 blocks = pixy.getBlocks();

 if(!blocks)
 {
   delay(20);
   blocks = pixy.getBlocks();
   
 }
 
 if (blocks)
 {
  
   xLoc = pixy.blocks[0].x;
   yLoc = pixy.blocks[0].y;
   width = pixy.blocks[0].width;
   height = pixy.blocks[0].height;
   color = pixy.blocks[0].signature;
   
 }
}
/* camPos function:
   On start up, wait untill the camera has started pulling data,
   then move towards first fish.
*/
void camPos()
{
 
  if(!setCam)
  {
    while(!blocks){
     readPixy();
     pixy.setServos(300,600);
     
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
      /*if (camFlag ==1)
      {
        time = millis();
        
        readPixy();
        pixy.setServos(300,600);
        readPixy();
        camFlag=2;
      }*/
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
  time = millis();
  switch(fishcount)
  {
    
    case 1:
    Serial.println(yLoc);
      if(yLoc < 165)
      {
        
      digitalWrite(Dir1, LOW);
      digitalWrite(Dir2, LOW);
      analogWrite(motorLeft, 80);
      analogWrite(motorRight, 80);
       
      }
      if(yLoc > 165) //mimics pick up.
      {
        while((millis() - time) < 2000)
        {
          readPixy();
        analogWrite(motorLeft, 0);
        analogWrite(motorRight, 0);
        fish = 2;
        Serial.println("wait!!!!");
        
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
       }
       if(camFlag == 2 && !blocks)
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
         
     
     if(!blocks)
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
    }
      break;
  }
}

   




