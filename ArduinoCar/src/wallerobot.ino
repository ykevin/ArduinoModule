/*
 Copyright (c) 2016, Juan Jimeno

 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of  nor the names of its contributors may be used to
 endorse or promote products derived from this software without specific
 prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */
#include <Arduino.h>
//header file for pid server
#include <SoftWire.h>
#include "imu_configuration.h"
#include "config.h"
#include "Encoder.h"
#include "Motor.h"

#define ENCODER_OPTIMIZE_INTERRUPTS

#define IMU_PUBLISH_RATE 10 //hz
#define VEL_PUBLISH_RATE 10 //hz
#define COMMAND_RATE 10 //hz
#define DEBUG_RATE 5

//left side motors
Motor motor1(MOTOR1_PWM, MOTOR1_IN_A, MOTOR1_IN_B); //front

//right side motors
Motor motor2(MOTOR2_PWM, MOTOR2_IN_A, MOTOR2_IN_B); // front

//left side encoders
Encoder motor1_encoder(MOTOR1_ENCODER_A,MOTOR1_ENCODER_B); //front

//right side encoders
Encoder motor2_encoder(MOTOR2_ENCODER_A,MOTOR2_ENCODER_B); //front

float Motor::Kp = K_P;
float Motor::Kd = K_D;
float Motor::Ki = K_I;

int Motor::max_rpm = MAX_RPM;
int Motor::counts_per_rev = COUNTS_PER_REV;
float Motor::wheel_diameter = WHEEL_DIAMETER;

double required_angular_vel = 0.5;
double required_linear_vel = 1.0;
unsigned long previous_command_time = 0;
unsigned long previous_control_time = 0;
unsigned long publish_vel_time = 0;
unsigned long previous_imu_time = 0;
unsigned long previous_debug_time = 0;

bool  accelerometer, gyroscope, magnetometer;
bool is_first = true;
char buffer[50];

void setup()
{
  Wire.begin();
  delay(5);
}

void loop()
{
  //this block drives the robot based on defined rate
  if ((millis() - previous_control_time) >= (3000 / COMMAND_RATE)){
    do_kinematics();
    move_base();
    previous_control_time = millis();
  }

  //this block stops the motor when no command is received
  if ((millis() - previous_command_time) >= 400){
    stop_base();
  }

  //this block publishes velocity based on defined rate
  if ((millis() - publish_vel_time) >= (3000 / VEL_PUBLISH_RATE)){
    publish_linear_velocity();
    publish_vel_time = millis();
  }

  //this block publishes the IMU data based on defined rate
  if ((millis() - previous_imu_time) >= (3000 / IMU_PUBLISH_RATE)) {
    //sanity check if the IMU exits
    if (is_first) {
      check_imu();
    } else {
      //publish the IMU data
      publish_imu();
    }
    previous_imu_time = millis();
  }

  //this block displays the encoder readings. change DEBUG to 0 if you don't want to display
  if(DEBUG) {
    if ((millis() - previous_debug_time) >= (3000 / DEBUG_RATE)) {
      print_debug();
      previous_debug_time = millis();
    }
  }
}

void do_kinematics()
{
  //convert m/s to m/min
  double linear_vel_mins = required_linear_vel * 60;
  //convert rad/s to rad/min
  double angular_vel_mins = required_angular_vel * 60;
  //calculate the wheel's circumference
  double circumference = PI * WHEEL_DIAMETER;
  //calculate the tangential velocity of the wheel if the robot's rotating where Vt = ω * radius
  double tangential_vel = angular_vel_mins * BASE_WIDTH;

  //calculate and assign desired RPM for each motor
  //left side
  motor1.required_rpm = (linear_vel_mins / circumference) - (tangential_vel / circumference);
  //right side
  motor2.required_rpm = (linear_vel_mins / circumference) + (tangential_vel / circumference);
}

void move_base()
{
  //calculate each motor's rpm for pwm calculation and odometry
  motor1.calculate_rpm(motor1_encoder.read());
  motor2.calculate_rpm(motor2_encoder.read());

  motor1.spin(motor1.calculate_pwm());
  motor2.spin(motor2.calculate_pwm());
}

void stop_base()
{
  required_linear_vel = 0;
  required_angular_vel = 0;
}

void publish_linear_velocity()
{

  //calculate the average RPM
  double average_rpm = (motor1.current_rpm + motor2.current_rpm) / 2; // RPM
  //convert revolutions per minute to revolutions per second
  double average_rps = average_rpm / 60; // RPS
  //calculate linear speed
  double linear_velocity = (average_rps * (WHEEL_DIAMETER * PI)); // m/s

  sprintf(buffer, "Robot Motor RPM is : %f, Line Speed Is: %f",
  average_rpm, linear_velocity);
  Serial.println(buffer);
}

void check_imu()
{
  //this function checks if IMU is present
  accelerometer = check_accelerometer();
  gyroscope = check_gyroscope();
  magnetometer = check_magnetometer();

  if (!accelerometer) {
    Serial.println("Accelerometer NOT FOUND!");
  }

  if (!gyroscope) {
    Serial.println("Gyroscope NOT FOUND!");
  }

  if (!magnetometer){
    Serial.println("Magnetometer NOT FOUND!");
  }

  is_first = false;
}

void publish_imu()
{
  if (accelerometer) {
    measure_acceleration();
    sprintf(buffer, "Accelerometer is : x: %f, y: %f, z: %f",
    raw_acceleration.x, raw_acceleration.y, raw_acceleration.z);
    Serial.println(buffer);
  }

  //measure gyroscope
  if (gyroscope) {
    measure_gyroscope();
    sprintf(buffer, "Gyroscope is : x: %f, y: %f, z: %f",
    raw_rotation.x, raw_rotation.y, raw_rotation.z);
    Serial.println(buffer);
  }

  //measure magnetometer
  if (magnetometer) {
    measure_magnetometer();
    sprintf(buffer, "Magnetometer is : x: %f, y: %f, z: %f",
    raw_magnetic_field.x, raw_magnetic_field.y, raw_magnetic_field.z);
    Serial.println(buffer);
  }
}

void print_debug()
{
  sprintf (buffer, "Encoder Left: %ld", motor1_encoder.read());
  Serial.println(buffer);
  sprintf (buffer, "Encoder Right: %ld", motor2_encoder.read());
  Serial.println(buffer);
}
