#ifndef LINO_BASE_CONFIG_H
#define LINO_BASE_CONFIG_H

#define DEBUG 1

float K_P = 0.4; // P constant
float K_I = 0.4; // I constant
float K_D = 1.0; // D constant

//define your motors' specs here

const int MAX_RPM = 366; //motor's maximum RPM
const int COUNTS_PER_REV = 1560; //wheel encoder's no of ticks per rev(gear_ratio * pulse_per_rev)
const float WHEEL_DIAMETER = 0.066; //wheel's diameter in meters

#define BASE_WIDTH 0.27 // width of the plate you are using

//ENCODER PINS
// left side encoders pins
#define MOTOR1_ENCODER_A 0 //front_A
#define MOTOR1_ENCODER_B 1 //front_B

// right side encoders pins
#define MOTOR2_ENCODER_A 2 //front_A
#define MOTOR2_ENCODER_B 3 //front_B

//don't change this if you followed the schematic diagram
//MOTOR PINS
//left side motor pins
#define MOTOR1_PWM 6
#define MOTOR1_IN_A 12
#define MOTOR1_IN_B 11

//right side motor pins
#define MOTOR2_PWM 5
#define MOTOR2_IN_A 9
#define MOTOR2_IN_B 10

#endif
