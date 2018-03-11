int ldrpin=A0;
int dstpin=12;
int ledpin=10;
int light=0;
int dist=0;
void setup() {
pinMode(A0,INPUT);
pinMode(12,INPUT);
pinMode(10,OUTPUT);
}

void loop() {
  light=analogRead(ldrpin);
  dist=digitalRead(dstpin);
  if(light<700)
  { 
    analogWrite(ledpin,128);
    if(dist==HIGH)
    {
      analogWrite(ledpin,255);
    }
   else
   {
    analogWrite(ledpin,0);
    }
  }
}
