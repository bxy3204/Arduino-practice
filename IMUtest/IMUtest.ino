#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

int angle=0;
int gyro;
int acc;
int dt;
int time;

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified       gyros  = Adafruit_L3GD20_Unified(20);

void setup() {
  // put your setup code here, to run once:
 time = millis();
 Serial.begin(9600);
 accel.begin();
 mag.begin();
 gyros.begin();
}

void loop() {
//Serial.println("go");
   sensors_event_t event;
 accel.getEvent(&event);
  mag.getEvent(&event);
  gyros.getEvent(&event);
  gyro = event.gyro.x;
  acc = event.acceleration.x;
  dt = 10;
//  Serial.println(time);
  if((millis() - time) > 10)
  {
    time = millis();
    angle = 0.98 *(angle+gyro*dt) + 0.02*acc;
    Serial.println(angle);
  }
  
  // put your main code here, to run repeatedly:

}
