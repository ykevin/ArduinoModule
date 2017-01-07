#ifndef Battery_h
#define Battery_h

#include "Arduino.h"

class Battery {
	public: 
		Battery(int Battery_Pin, float Threshold, float Volt_Min, float Volt_Max);
		float Get_Volt(void);
		float Get_Battery_Notifier(void);
		bool  Get_Battery_Low(void);

	private:
		int _Battery_Pin;
		float _Threshold;
		float _Volt_Min;
		float _Volt_Max;
};

#endif
