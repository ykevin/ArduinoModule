

void setup()
{
	Serial.begin(9600); 
}

void loop()
{
	int n = analogRead(A0);    //读取A0口的电压值
	Serial.print("adc value is : ");                   //串口输出温度数据
	Serial.println(n);                   //串口输出温度数据

	double vol = (n * 5.0 * 11) / 1024.0;   //使用双精度浮点数存储温度数据，温度数据由电压值换算得到

	Serial.println(vol);                   //串口输出温度数据
	delay(2000);                           //等待2秒，控制刷新速度
}
