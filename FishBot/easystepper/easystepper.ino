void setup() {                

  pinMode(24, OUTPUT);     

  pinMode(25, OUTPUT);

  digitalWrite(24, LOW);

  digitalWrite(25, HIGH);

}


void loop() {

  digitalWrite(24, HIGH);
  delayMicroseconds(1000);    

  digitalWrite(24, LOW); 
  delayMicroseconds(1000);    

}
