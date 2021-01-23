#include "pitches.h"

int yellowPin = 5;
int greenPin = 6;
int buttonApin = 9;
int buttonBpin = 10;

//https://forum.arduino.cc/index.php?topic=424068.0
unsigned long previousMillis = 0;        // will store last time LED was updated
const unsigned long interval = 15UL*1000UL;   // Change the LED every 12 hours

void setup()
{
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  //  Serial.println(" Button: " + LOW);
  if (digitalRead(buttonApin) == LOW)
  {
    startBlink();
  }


  // turn off led after end
    unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the time you should have toggled the LED
    previousMillis += interval;
    digitalWrite(greenPin, LOW);
  }

  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
  }
}

void startBlink() {
  for (int counter = 1; counter <= 3; counter++) {
    digitalWrite(yellowPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(8, NOTE_F5, 900);
    delay(1000);              // wait for a second
    digitalWrite(yellowPin, LOW);    // turn the LED off by making the voltage LOW
    delay(200);              // wait for a second
    Serial.println("Beep.");
  }
  delay(200);
  digitalWrite(greenPin, HIGH);
  tone(8, NOTE_A5, 900);
  Serial.println("Beep!!!");

}
