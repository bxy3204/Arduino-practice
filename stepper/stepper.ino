#include <Stepper.h>
#define STEPS 32
Stepper stepper = Stepper(STEPS,28,32,30,34);
void setup() {
  
  // put your setup code here, to run once:
  stepper.setSpeed(800);

}

void loop() {
  stepper.step(695); //positive -towards floor
  delay(1000);// put your main code here, to run repeatedly:
 
}
