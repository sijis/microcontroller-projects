#include <FastLED.h>
#include "pitches.h"

int buttonApin = 9;
int buttonBpin = 10;

//https://forum.arduino.cc/index.php?topic=424068.0
unsigned long previousMillis = 0;             // will store last time LED was updated
const unsigned long interval = 15UL * 1000UL; // Change the LED every 15 seconds

// FastLED
#define NUM_LEDS 15
#define DATA_PIN 3
#define LED_TYPE WS2812B
#define CLOCK_PIN 13

#define BRIGHTNESS 96
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup()
{
    pinMode(buttonApin, INPUT_PULLUP);
    pinMode(buttonBpin, INPUT_PULLUP);
    Serial.begin(9600);

    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();
}

void loop()
{
    //  Serial.println(" Button: " + LOW);
    if (digitalRead(buttonApin) == LOW)
    {
        Serial.println("Start Sequence.");
        startBattleSequence();
        previousMillis = millis();
        Serial.println("End Sequence.");
    }

    endTimerSequence();
}

void startBattleSequence()
{
    for (int counter = 1; counter <= 3; counter++)
    {
        fill_solid(leds, NUM_LEDS, CRGB::Yellow);
        tone(8, NOTE_F5, 900);
        FastLED.delay(1000);

        FastLED.clear();
        FastLED.delay(200);
        Serial.println("Beep.");
    }

    delay(200);
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    tone(8, NOTE_A5, 900);
    Serial.println("Beep!!!");
}

void endTimerSequence()
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        // save the time you should have toggled the LED
        previousMillis += interval;
        Serial.println("Shut off time");
        FastLED.clear();
        FastLED.show();
    }

    if (digitalRead(buttonBpin) == LOW)
    {
        FastLED.clear();
        FastLED.show();
    }
}
