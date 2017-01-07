#include "Battery.h"

Battery::Battery(int Battery_Pin, float Threshold, float Volt_Min, float Volt_Max)
{
	_Battery_Pin = Battery_Pin; 
	_Threshold = Threshold;
	_Volt_Min = Volt_Min;
	_Volt_Max = Volt_Max;
}

float Battery::Get_Volt(void)
{
	int Value = analogRead(_Battery_Pin);
	
	return ((Value * 5.0 * 11) / 1024.0);
}

float Battery::Get_Battery_Notifier()
{
	float Volt = Get_Volt();

	return ((Volt-_Volt_Min) / (_Volt_Max - _Volt_Min) * 100);
}

bool Battery::Get_Battery_Low(void)
{
	float Value = Get_Battery_Notifier();
	if (Value > _Threshold)
		return false;
	else
		return true;
}

