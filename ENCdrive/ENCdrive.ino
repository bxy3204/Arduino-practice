#include <Encoder.h>
// motor one
int Dir1 = 28;
int motorLeft = 5;
int Dir2 = 29;
int motorRight = 6;
Encoder lEnc(2, 3);
Encoder rEnc(18, 19);
int leftspeed=80;
int rightspeed=80;
int encTime1;
int encTime2;
int encLS=0;
int encRS=0;
void setup() {
  // put your setup code here, to run once:
    pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  Serial.begin(9600);

}
void forward(int dur){
  encTime1 = millis();
  encTime2 = millis();
  int encL;
  int encR;
  analogWrite(motorLeft, leftspeed);
  analogWrite(motorRight, rightspeed);
  while ((encTime2 - encTime1) < dur)
  {
    encLS = encLS + lEnc.read();
    encRS = encRS + rEnc.read();
    if (encRS < encLS){
      rightspeed += 3;
      rightspeed = constrain(rightspeed,70,95);
      analogWrite(motorRight, rightspeed);
    }
    if (encRS > encLS){
      rightspeed -= 3;
      rightspeed = constrain(rightspeed,70,95);
      analogWrite(motorRight, rightspeed);
    }
    encTime2 = millis();
    
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  forward(3000);
  delay(1000);
 
 // Serial.println("left     right");
  Serial.println();
  Serial.print(lEnc.read());
  Serial.print("___________");
  Serial.print(rEnc.read());
}

