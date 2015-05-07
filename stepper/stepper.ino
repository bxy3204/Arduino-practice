#include <Stepper.h>
#define STEPS 32
Stepper stepper = Stepper(STEPS,41,45,43,47);
void setup() {
  
  // put your setup code here, to run once:
  stepper.setSpeed(1);

}

void loop() {
  stepper.step(-1); //positive -towards floor
  delay(100);// put your main code here, to run repeatedly:
 
}
