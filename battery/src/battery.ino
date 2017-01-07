#include "Battery.h"

Battery battery(A0, 20.00, 9.6, 12.0);

void setup()
{
	Serial.begin(9600); 
}

void loop()
{
	float Volt = battery.Get_Volt();

	Serial.println(Volt);                   //串口输出温度数据
	delay(2000);                           //等待2秒，控制刷新速度
}
