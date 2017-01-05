#include "Motor.h"

#define MOTOR1_IN_A		9 
#define MOTOR1_IN_B		10 
#define MOTOR2_IN_A		11 
#define MOTOR2_IN_B		12 
#define MOTOR1_PWM  	5
#define MOTOR2_PWM  	6 
 
#define STBY	4  

//left side motors
Motor motor1(MOTOR1_PWM, MOTOR1_IN_A, MOTOR1_IN_B); //front

 //right side motors
Motor motor2(MOTOR2_PWM, MOTOR2_IN_A, MOTOR2_IN_B); // front

  
void setup() {  
 	
        pinMode(STBY, OUTPUT); 

  	digitalWrite(STBY, HIGH);  
}  
  
void loop() {  
 	motor1.spin(100); 
 	motor2.spin(100); 

	delay(2000);	
  	digitalWrite(STBY, LOW);  
  
	delay(1000);
  	digitalWrite(STBY, HIGH);  

 	motor1.spin(-100); 
 	motor2.spin(-100); 

	delay(2000);	
  	digitalWrite(STBY, LOW);  
  
	delay(2000);
  	digitalWrite(STBY, HIGH);  
}  


