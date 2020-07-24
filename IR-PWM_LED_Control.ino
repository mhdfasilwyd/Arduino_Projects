#include <IRremote.h> 

#define RECV_PIN 3 
#define LED_PIN 5
#define LED_PWM 255
#define CODE_A  33444015 
#define CODE_B  33478695 

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  irrecv.enableIRIn();  
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN,LED_PWM); 
} 

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    unsigned int value = results.value;
    switch(value) 
    {
      case CODE_A:
      { 
        LED_PWM = LED_PWM + 5;      
        analogWrite(LED_PIN,LED_PWM);             
      } 
    break; 
      case CODE_B:
      {
        LED_PWM = LED_PWM - 5;     
        analogWrite(LED_PIN,LED_PWM);
      } 
    break;           
    }
  irrecv.resume(); 
  }
}
