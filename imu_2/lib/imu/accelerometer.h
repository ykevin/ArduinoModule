#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

uint8_t acc_reads = 0;
byte acc_buffer[6];

bool check_accelerometer();

void measure_acceleration();
double raw_acceleration_x;
double raw_acceleration_y;
double raw_acceleration_z;


#if defined(ADXL345)
  #include "accelerometer_ADXL345.h"
#endif

#endif  // _ACCELEROMETER_H_
