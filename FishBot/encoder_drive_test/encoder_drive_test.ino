#include <Encoder.h>
// motor one
int Dir1 = 26;
int motorLeft = 5;
int Dir2 = 27;
int motorRight =6;
long track=0;
int newPosition;

Encoder motorLEnc(18,19);
Encoder motorREnc(20,21);
int leftSpeed = 80;
int rightSpeed = 80;
long leftEnc;
long rightEnc;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
      pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, LOW);
  

}
long oldPosition  = -999;

void loop() {
    leftEnc = motorLEnc.read();
    rightEnc = motorREnc.read();
    motorLEnc.write(0);
    motorREnc.write(0);
    while(abs(leftEnc) < 4250)
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
     analogWrite(motorLeft,0);
     analogWrite(motorRight, 0);
     delay(3000);
     /*analogWrite(motorLeft, 0);
     analogWrite(motorRight, 0);
     delay(100);
     digitalWrite(Dir1, HIGH);
     motorLEnc.write(0);
     motorREnc.write(0);
     Serial.println("TURN!!");
     leftEnc = motorLEnc.read();
     rightEnc = motorREnc.read();
     while(abs(leftEnc) < 4940)
     {
       analogWrite(motorLeft, leftSpeed);
     analogWrite(motorRight, rightSpeed);
     newPosition = leftEnc;
     leftEnc = motorLEnc.read();
     rightEnc = motorREnc.read();
     Serial.println(leftEnc);
     
     if(abs(rightEnc) < abs(leftEnc))
     {
       rightSpeed = constrain(rightSpeed++,75,85);
     }
     if(abs(rightEnc) > abs(leftEnc))
     {
       rightSpeed = constrain(rightSpeed--,75,85);
     }
     }
     while(1)
     {analogWrite(motorLeft, 0);
     analogWrite(motorRight, 0);
      delay(100000);
     }*/
  }
 



