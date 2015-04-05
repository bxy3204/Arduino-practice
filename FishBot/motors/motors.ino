// connect motor controller pins to Arduino digital pins
// motor one
int Dir1 = 28;
int motorLeft = 5;
// motor two
int Dir2 = 29;
int motorRight = 6;


void setup() {
  // put your setup code here, to run once:
  pinMode(Dir1, OUTPUT);
  pinMode(Dir2, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  digitalWrite(Dir1, HIGH);
  digitalWrite(Dir2, HIGH);
}

void loop() {
  analogWrite(motorLeft, 250);
  analogWrite(motorRight, 250);

  

}
