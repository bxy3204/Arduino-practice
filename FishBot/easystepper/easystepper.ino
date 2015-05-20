int arm=0;
void setup() {                

  pinMode(24, OUTPUT);     

  pinMode(25, OUTPUT);

  digitalWrite(24, LOW);

  digitalWrite(25, HIGH); //Low towards bucket

}


void loop() {
if(arm < 1400){
  digitalWrite(24, HIGH);
  delayMicroseconds(1000);    

  digitalWrite(24, LOW); 
  delayMicroseconds(1000); 
 arm++; 
}  

}
