/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;

int redLed = 8;
int yellowLed = 9;
int greenLed = 10;

int onoff,redLedState, yellowLedState, greenLedState = 0;


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(redLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  
  digitalWrite(redLed,LOW);
  digitalWrite(yellowLed,LOW);
  digitalWrite(greenLed,LOW);

 
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    
    switch(results.value){


      case 0xFF0000FF:

         onoff = !onoff;

         if(onoff){
            digitalWrite(redLed,HIGH);
            digitalWrite(yellowLed,HIGH);
            digitalWrite(greenLed,HIGH);
            redLedState = HIGH;
            yellowLedState = HIGH;
            greenLedState = HIGH;
          }else{
            digitalWrite(redLed,LOW);
            digitalWrite(yellowLed,LOW);
            digitalWrite(greenLed,LOW);
            redLedState = LOW;
            yellowLedState = LOW;
            greenLedState = LOW;
            }
               
          break;
      
      case 0xFF00A05F:
         redLedState = !redLedState;
         digitalWrite(redLed,redLedState);

      break;

      case 0xFF00609F:
         yellowLedState = !yellowLedState;
         digitalWrite(yellowLed,yellowLedState);
      break;
      

      case 0xFF0020DF:
          greenLedState = !greenLedState;
          digitalWrite(greenLed,greenLedState);
      break;
      
      }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
