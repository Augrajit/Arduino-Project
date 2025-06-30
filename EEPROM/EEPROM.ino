#include<EEPROM.h>
int sw=12,light=13;
void setup() {
   pinMode(sw,INPUT_PULLUP);
   pinMode(light,OUTPUT);
   Serial.begin(9600);
   state=EEPROM.read(1);
  
}

void loop() {
  int r=button_press();
  if(r==1){
    state=1;
    EEPROM.write(1,0);
  }
  else if(r==2){
    state=0;
    EEPROM.write(1,1);
  }
  (state>1000)? digitalWrite(light,1) : digitalWrite(light,0);//Ternery function (used instead of if else)
}
//Button press,sw=1; not pressed sw=0
int button_press(){
  int count=0;
  p: int t=0;
  if(digitalRead(sw)==0){
    digitalWrite(light,1);
    while(digitalRead(sw)==0){
      delay(1);t++;
    }
    digitalWrite(light,0);
    if(t>15){
      count ++;
      t=0;//Make the function wait for the next push 
      while(digitalRead(sw)==1){
        delay(1);t++;
        if (t>1000) return count;
      }
      goto p;
    }
  }
  return count;//If not pressed count=0
}