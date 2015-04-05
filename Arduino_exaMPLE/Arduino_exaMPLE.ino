// connect motor controller pins to Arduino digital pins
// motor one
int enA = 9;
int in1 = 34;
int in2 = 35;
// motor two
int enB = 10;
int in3 = 36;
int in4 = 37;
void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000);

}
void turn(){
  analogWrite(enB,0);
  analogWrite(enA,0);
  delay(500);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  delay(2000);
  analogWrite(enB, 0);
  analogWrite(enA, 0);
  delay(500);
}
void loop()
{
  delay(1000);
  turn();
  delay(1000);
}
