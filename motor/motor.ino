#define AIN1	9 
#define AIN2	10 
#define BIN1	11 
#define BIN2	12 
#define PWMA  	5
#define PWMB  	6 
 
#define STBY	4  
  
void setup() {  
//  Serial.begin (9600);  
//初始化各IO,模式为OUTPUT 输出模式  
  pinMode(AIN1,OUTPUT);  
  pinMode(AIN2,OUTPUT); 
  pinMode(BIN1,OUTPUT);  
  pinMode(BIN2,OUTPUT); 
  pinMode(PWMA, OUTPUT); 
  pinMode(PWMB, OUTPUT); 

  pinMode(STBY, OUTPUT); 

  digitalWrite(STBY, HIGH);  
}  
  
void loop() {  
  //forward 向前转  
  digitalWrite(AIN1,HIGH); //给高电平  
  digitalWrite(AIN2,LOW);  //给低电平 
  digitalWrite(BIN1,HIGH); //给高电平  
  digitalWrite(BIN2,LOW);  //给低电平 

  analogWrite(PWMA, 150); 
  analogWrite(PWMB, 150);
  delay(2000);   //延时2秒  
  
  //stop 停止  
  digitalWrite(STBY, LOW);  
  delay(2000);
  digitalWrite(STBY, HIGH);  
 
  
    
  //back 向后转  
  digitalWrite(AIN1,LOW);  
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);   //给高电平  
  digitalWrite(BIN2,HIGH);  //给低电平 

  analogWrite(PWMA, 150); 
  analogWrite(PWMB, 150); 
  delay(2000);  

  digitalWrite(STBY, LOW);  
  delay(2000);
  digitalWrite(STBY, HIGH);    
  
}  


