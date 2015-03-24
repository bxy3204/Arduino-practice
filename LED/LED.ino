int led = 13;

void setup() {
  // put your setup code here, to run once:
  int led = 13;
  pinMode(led, OUTPUT); // initialize pin 13 as output

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, HIGH); // set LED on (High voltage level)
  delay(100000);       // wait 1 sec
  digitalWrite(led, LOW);  // set led low
  delay(1000);          
  
}

