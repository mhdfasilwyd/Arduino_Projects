#include<LiquidCrystal.h>

#define INPUT_MOT 6
#define INPUT_INC 7
#define INPUT_DEC 8
#define OUTPUT_MOT A1
#define OUTPUT_BUZ 10
#define INPUT_SENSOR A0
#define INPUT_REL 9
#define MAX_TEMP 80

int tempValue,maxTemp;
bool MOT_FLAG,motPin,incPin,decPin,relState;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(INPUT_MOT, INPUT);
  pinMode(INPUT_SENSOR, INPUT);
  pinMode(INPUT_INC, INPUT);
  pinMode(INPUT_DEC, INPUT);
  pinMode(INPUT_REL, INPUT);
  pinMode(OUTPUT_MOT, OUTPUT);
  pinMode(OUTPUT_BUZ, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600); // GSM Baud Rate
  tempValue = 0;
  maxTemp = MAX_TEMP;
  MOT_FLAG = LOW;
  motPin = LOW;
  incPin = LOW;
  decPin = LOW;
}

void loop()
{
  motPin = digitalRead(INPUT_MOT);
 
  if(motPin == HIGH)
  {
    MOT_FLAG = !(MOT_FLAG);
    digitalWrite(OUTPUT_MOT,MOT_FLAG);
  }
  
  while(MOT_FLAG == HIGH)
  {
    incPin = digitalRead(INPUT_INC);
    decPin = digitalRead(INPUT_DEC);
    
    if(incPin == HIGH)
    {
      if(maxTemp <= 99)
      {
        maxTemp++;
        delay(2);
      }
    }

    if(decPin == HIGH)
    {
      if(maxTemp >= 1)
      {
        maxTemp--;
        delay(2);
      }
    }
    
    lcd.setCursor(0,0);
    lcd.print("ST ");
    lcd.print(maxTemp);
    checkSensor();
  
  }
}

void checkSensor(void)
{
  tempValue = analogRead(INPUT_SENSOR); // LM35 Sensor Pin
  tempValue = (tempValue*500)/1023;
  
  lcd.setCursor(8,0);
  lcd.print("CT ");
  lcd.print(tempValue);
  
  if(tempValue > maxTemp)
  {
    digitalWrite(OUTPUT_MOT,LOW);
    digitalWrite(OUTPUT_BUZ,HIGH);
    lcd.setCursor(0,1);
    lcd.print("HIGH TEMPERATURE");
    sendMsgTemp();
  }

  relState = digitalRead(INPUT_REL); // Relay Pin
  
  if(relState == LOW)
  {
    digitalWrite(OUTPUT_MOT,LOW);
    digitalWrite(OUTPUT_BUZ,HIGH);
    lcd.setCursor(0,1);
    lcd.print("PHASE FAILURE");
    sendMsgPhase();
  }
}

void sendMsgTemp()
{
  Serial.println("AT+CMGF=1"); // Set SMS Mode to Text
  delay(1000);
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
  delay(1000);
  Serial.println("MOTOR OFF : HIGH TEMPERATURE");
  delay(100);
  Serial.println((char)26);
}

void sendMsgPhase()
{
  Serial.println("AT+CMGF=1"); // Set SMS Mode to Text
  delay(1000);
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
  delay(1000);
  Serial.println("MOTOR OFF : PHASE FAILURE");
  delay(100);
  Serial.println((char)26);
}
