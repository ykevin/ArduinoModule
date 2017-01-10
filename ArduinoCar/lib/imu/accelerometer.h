#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

uint8_t acc_reads = 0;
byte acc_buffer[6];

bool check_accelerometer();

void measure_acceleration();
//geometry_msgs::Vector3 raw_acceleration;
typedef struct {
  double x;
  double y;
  double z;
}Accelerometer;

Accelerometer raw_acceleration;


#if defined(ADXL345)
  #include "accelerometer_ADXL345.h"
#endif

#endif  // _ACCELEROMETER_H_
