#include <Encoder.h>
// motor one
int Dir1 = 28;
int motorLeft = 5;
int Dir2 = 29;
int motorRight = 6;
long track=0;

Encoder myEnc(3, 2);
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
      pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, LOW);
  digitalWrite(Dir2, LOW);
  

}
long oldPosition  = -999;

void loop() {
    analogWrite(motorLeft, 80);
  analogWrite(motorRight, 80);
  // put your main code here, to run repeatedly:
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(track);
    track += newPosition;
    delay(100);
  }

}
