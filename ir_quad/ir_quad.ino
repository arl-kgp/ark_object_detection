
// Use with GP2Y0A21YK Sensors
#define iter 4
#define Kp 3
#include <Servo.h>
Servo roll,pitch;
int setpoint=150;
void setup()
{
  Serial.begin(9600);
  roll.attach(9);
  pitch.attach(10);

pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
}
void loop()
{
 // setpoint=map(setpoint,50,550,0,1023);
  int left,right,front,back;
  int d1,d2,d3,d4;
  int temp,temp1,temp2,temp3;
  int e1,e2,e3,e4;
  int op1,op2,op3,op4,opx,opy;
  int CH1=1500,CH2=1500;

  temp=0;
  temp1=0;
  temp2=0;
  temp3=0;
  for(int i=0;i<iter;i++)
  {
    left = analogRead(A0);
    delay(1);
    temp=temp+left;
  }

  d1=temp/10;
  for(int i=0;i<iter;i++)
  {
    right = analogRead(A1);
    delay(1);
    temp1=temp1+right;
  }
  d2=temp1/10;
  for(int i=0;i<iter;i++)
  {
    front = analogRead(A2);
    delay(1);
    temp2=temp2+front;
  }
  d3=temp2/10;
  for(int i=0;i<iter;i++)
  {
    back = analogRead(A3);
    delay(1);
    temp3=temp3+back;
  }
  d4=temp3/10;
  

 if(d1<setpoint && d2<setpoint && d3<setpoint && d4<setpoint){
  CH1 = pulseIn(2,HIGH,30000); 
  CH2 = pulseIn(3,HIGH,30000);
  opx=CH1;
  opy=CH2;
 }
  else{
  
//  e1=d1-setpoint;
//  e2=d2-setpoint;
//  e3=d3-setpoint;
//  e4=d4-setpoint;
//  
//  op1=e1*Kp;
//  op2=e2*Kp;
//  op3=e3*Kp;
//  op4=e4*Kp;

  op1=d1*Kp;
  op2=d2*Kp;
  op3=d3*Kp;
  op4=d4*Kp;
  
  opx=CH1-op1+op2;
  opy=CH2-op3+op4;
  }
  
  roll.writeMicroseconds(opx);
  pitch.writeMicroseconds(opy);

  Serial.print(CH1);
  Serial.print("\t");
  Serial.print(opx);
  Serial.print("\t \t");
  Serial.print(CH2);
  Serial.print("\t");
  Serial.println(opy);
   
}
