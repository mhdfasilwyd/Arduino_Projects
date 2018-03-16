#include <IRremote.h> 
int RECV_PIN =3; 
int led1 = 5;
int ledpwm = 255; 
#define code1  33444015 
#define code2  33478695 
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
irrecv.enableIRIn();  
pinMode(led1, OUTPUT);
analogWrite(led1,ledpwm); 
} 
void loop() {
if (irrecv.decode(&results)) {
unsigned int value = results.value;
switch(value) {
case code1:
{ 
ledpwm = ledpwm + 5;      
analogWrite(led1,ledpwm);             
} 
break; 
case code2:
{
ledpwm = ledpwm - 5;     
analogWrite(led1,ledpwm);
} 
break;           
}
irrecv.resume(); 
}
}


