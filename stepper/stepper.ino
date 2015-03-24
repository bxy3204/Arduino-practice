#include <Stepper.h>
#define STEPS 32
Stepper stepper = Stepper(STEPS,42,46,44,48);
void setup() {
  
  // put your setup code here, to run once:
  stepper.setSpeed(500);

}

void loop() {
  stepper.step(695);
  delay(2000);// put your main code here, to run repeatedly:
 
}
