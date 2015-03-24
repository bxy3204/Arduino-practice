#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_9DOF.h>

Adafruit_9DOF                dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 11;
int in1 = 13;
int in2 = 12;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

  double compassA;
  double compassB;
  double motorA=70;
  double motorB=100;
  double start;

void initSensors()
{
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
   sensors_vec_t   orientation;
  sensors_event_t mag_event;
  
  mag.getEvent(&mag_event);
  dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation);
  start = orientation.heading;


}

void setup(void)
{

  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(115200);
  
  
 
  
  /* Initialise the sensors */
  initSensors();
    // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
    // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
    // set speed to 200 out of possible range 0~255
  analogWrite(enA, motorA);

  // set speed to 200 out of possible range 0~255
  analogWrite(enB, motorB);
}



void loop(void)
{
  sensors_vec_t   orientation;
  sensors_event_t mag_event;
  mag.getEvent(&mag_event);
  dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation);
  compassA = orientation.heading+3;
  compassB = compassA-6;
  


  
  while(compassA < start){
    if(motorA < 245){
      motorA++;
  }
    if (motorB > 10){
      motorB++;
    }
    analogWrite(enA, motorA);
    analogWrite(enB, motorB);
 
    mag.getEvent(&mag_event);
    dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation);
    compassA = orientation.heading+5;
    delay(500);
  }
   while(compassB > start){
  if(motorB < 245){
      motorB++;
  }
    if (motorA > 10){
      motorA++;
    }    
    analogWrite(enA, motorA);
    analogWrite(enB, motorB);


     mag.getEvent(&mag_event);
     dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation);
     compassB = orientation.heading-5;
     delay(500);
  }
  

  /*Serial.println("motorA ");
  
  Serial.print(compassA);
  Serial.println("motorB ");
  
 Serial.print(compassB);*/
  Serial.println(start);
  Serial.println(compassA);
  Serial.println(compassB);
  
  delay(1500);
}
  
  
