#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial   
#include <BlynkSimpleEsp8266.h>
char auth[] = "6412eab907bc4e7f800ace5f8d6bd87d";
char ssid[] = "esphome";
char pass[] = "12345678";
#define LED_PIN1 4
#define LED_PIN2 5
#define INPUT_PIN1 12
#define INPUT_PIN2 14
bool oldinputstate1;
bool oldinputstate2;
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(INPUT_PIN1,INPUT_PULLUP);
  pinMode(INPUT_PIN2,INPUT_PULLUP);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  oldinputstate1=!digitalRead(INPUT_PIN1);
  oldinputstate2=!digitalRead(INPUT_PIN2);
}

void loop()
{
  getValue1();
  getValue2();
  Blynk.run();
}
void getValue1(void)
{
  int inputstate1 = digitalRead(INPUT_PIN1);;
  if (inputstate1!=oldinputstate1) 
  { 
    Serial.println("Motion detected");
    Blynk.notify("Motion detected"); 
    digitalWrite(LED_PIN1,HIGH);
    oldinputstate1=inputstate1;
  }
}
void getValue2(void)
{
  int inputstate2 = digitalRead(INPUT_PIN2);;
  if (inputstate2!=oldinputstate2) 
  { 
    Serial.println("Gas Detected");
    Blynk.notify("Gas Detected"); 
    digitalWrite(LED_PIN2,HIGH);
    oldinputstate2=inputstate2;
  }
}  


