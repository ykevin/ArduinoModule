
#include <Wire.h>
#include "imu_configuration.h"

#define IMU_PUBLISH_RATE 10 //hz

unsigned long previous_imu_time = 0;
bool is_first = true;
bool accelerometer;
bool gyroscope;
bool magnetometer;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  delay(5);
}
void loop()
{
  if ((millis() - previous_imu_time) >= (1000 / IMU_PUBLISH_RATE)){
    if (is_first){
      check_imu();
    } else{
        //publish the IMU data
      publish_imu();
    }
    previous_imu_time = millis();
  }
}

void check_imu()
{
  //this function checks if IMU is present
  accelerometer = check_accelerometer();
  gyroscope = check_gyroscope();
  magnetometer = check_magnetometer();

  if (!accelerometer)
  {
    Serial.print("Accelerometer NOT FOUND!");
  }

  if (!gyroscope)
  {
    Serial.print("Gyroscope NOT FOUND!");
  }

  if (!magnetometer)
  {
    Serial.print("Magnetometer NOT FOUND!");
  }

  is_first = false;
}

void publish_imu()
{
  if (accelerometer)
  {
    measure_acceleration();
    Serial.print("x = : ");
    Serial.print(raw_acceleration_x);
  }

  //measure gyroscope
  if (gyroscope)
  {
    measure_gyroscope();

  }

  //measure magnetometer
  if (magnetometer)
  {
    measure_magnetometer();
  }
}
