// C++ code
// Digital Dustbin 
#include<Servo.h>
int distance_value(int echo,int trig);//pre declaration of the function
Servo myservo;
int echo=6,trig=7;//trig will generate the sound wave

void setup()
{
 Serial.begin(9600);
 myservo.attach(4);
 pinMode(trig,OUTPUT);
 pinMode(echo,INPUT);
}

void loop()
{
  //myservo.write(90);
  //Serial.println(distance_value(echo,trig));
  if(distance_value(echo,trig)<30){
    myservo.write(90);
  
  }
  if((distance_value(echo,trig))>30 && (distance_value(echo,trig))<=330){
    myservo.write(0);
  }
}
int distance_value(int echo,int trig){
  
 digitalWrite(trig,LOW);//to ensure there is no garbage value
 delayMicroseconds(2);
 digitalWrite(trig,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig,LOW);
  
 int duration= pulseIn(echo,HIGH);
   
 int distance = (0.034*duration)/2;
 return distance;
 

}

