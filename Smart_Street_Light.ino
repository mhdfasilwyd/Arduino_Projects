// Smart Street Light Version 0.1
// Made by Muhammed Fasil K-https://github.com/mhdfasilwyd/Arduino_Projects

#define ldrPin A0
#define dstPin 12
#define ledPin 10
#define MIN_VALUE 700 // Change This Value According to Your LDR Value
int light=0;
int dist=0;
void setup() 
{
  pinMode(A0,INPUT);
  pinMode(12,INPUT);
  pinMode(10,OUTPUT);
}

void loop() 
{
  light=analogRead(ldrpin);
  dist=digitalRead(dstpin);
  
  if(light < MIN_VALUE)
  { 
    if(dist == HIGH)
    {
      analogWrite(ledpin,255);
    }
    else
    {
      analogWrite(ledpin,128);
    }
  }
  else
  {
    analogWrite(ledpin,0);
  }
}
