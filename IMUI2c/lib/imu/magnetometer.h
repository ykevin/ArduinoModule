#ifndef _MAGNETOMETER_H_
#define _MAGNETOMETER_H_

uint8_t mag_reads = 0;
byte mag_buffer[6];

bool check_magnetometer();
void measure_magnetometer();
double raw_magnetic_field_x;
double raw_magnetic_field_y;
double raw_magnetic_field_z;

#if defined(HMC5883L)
  #include "magnetometer_HMC5883L.h"
#endif

#endif  // _MAGNETOMETER_H_
