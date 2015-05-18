#include <Encoder.h>
// motor one
int Dir1 = 36;
int motorLeft = 6;
int Dir2 = 37;
int motorRight = 5;
long track=0;
Encoder motorLEnc(18, 19);
Encoder motorREnc(20, 21);
int lSpeed=80;
int rSpeed = 80;
long track2 =0;
long error;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
      pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, HIGH);
  

}
long oldPosition  = -999;

void loop() {
    analogWrite(motorLeft, lSpeed);
  analogWrite(motorRight, rSpeed);
  track = motorLEnc.read();
  track2 = motorREnc.read();
Serial.println(error);
error = abs(track) - abs(track2);
error = round(error);
if(error < 0 )
{
  lSpeed=constrain(lSpeed + 10, 60,90 );
  rSpeed = constrain(rSpeed - 10,60,90);
}
if(error > 1)
{
  lSpeed=constrain(lSpeed- 10, 60,90 );
  rSpeed = constrain(rSpeed + 10,60,90);

  }
}
 

