// IR Remote Automation Version 0.1
// Made by Muhammed Fasil K
// Ir library by shirriff-https://github.com/z3t0/Arduino-IRremote
#include <IRremote.h>
int RECV_PIN = 13; // the pin where you connect the output pin of TSOP4838
int led1 = 23; // Pin were devices can be connected
int led2 = 22; // Pin were devices can be connected
int led3 = 21; // Pin were devices can be connected
int led4 = 20; // Pin were devices can be connected
int led5 = 19; // Pin were devices can be connected
int itsONled[] = {0,0,0,0,0,0}; // Setting the initial condition of LED Off
#define code1  33444015 // code received from button A
#define code2  33478695 // code received from button B
#define code3  33486855 // code received from button C
#define code4  33435855 // code received from button D
#define code5  33468495 // code received from button E
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  Serial.begin(9600);   // Can delete this line if serial communication is not needed
  irrecv.enableIRIn();  // Start the receiver
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}
 
void loop() {
  if (irrecv.decode(&results)) {
    unsigned int value = results.value;
    switch(value) {
       case code1:
         if(itsONled[1] == 1) {        // if first led is on then
            digitalWrite(led1, LOW);   // turn it off when button is pressed
            itsONled[1] = 0;           // and set its state as off
         } else {                      // else if first led is off
             digitalWrite(led1, HIGH); // turn it on when the button is pressed
             itsONled[1] = 1;          // and set its state as on
         }
          break; 
       case code2:
         if(itsONled[2] == 1) {
            digitalWrite(led2, LOW);
            itsONled[2] = 0;
         } else {
             digitalWrite(led2, HIGH);
             itsONled[2] = 1;
         }
          break;
       case code3:
         if(itsONled[3] == 1) {
            digitalWrite(led3, LOW);
            itsONled[3] = 0;
         } else {
             digitalWrite(led3, HIGH);
             itsONled[3] = 1;
         }
         break;
          case code4:
         if(itsONled[4] == 1) {
            digitalWrite(led4, LOW);
            itsONled[4] = 0;
         } else {
             digitalWrite(led4, HIGH);
             itsONled[4] = 1;
         }
          break;
           case code5:
         if(itsONled[5] == 1) {
            digitalWrite(led5, LOW);
            itsONled[5] = 0;
         } else {
             digitalWrite(led5, HIGH);
             itsONled[5] = 1;
         }
          break;
                    
    }
    Serial.println(value); // Can delete this line if serial communication is not needed
    irrecv.resume(); // Receive the next value
  }
}


