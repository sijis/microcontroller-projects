#include <FastLED.h>
#include "pitches.h"

int buzzerPin = 8;
int buttonStartPin = 9;
int buttonStopPin = 10;

// https://forum.arduino.cc/index.php?topic=424068.0
unsigned long previousMillis = 0;             // will store last time LED was updated
const unsigned long interval = 180UL * 1000UL; // Change the LED every 15 seconds

// FastLED
#define NUM_LEDS 100
#define DATA_PIN 5
#define LED_TYPE WS2812B
#define CLOCK_PIN 13
#define FRAMES_PER_SECOND 120
#define BRIGHTNESS 50
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
uint8_t gHue = 0; // rotating "base color"

void setup()
{
    pinMode(buttonStartPin, INPUT_PULLUP);
    pinMode(buttonStopPin, INPUT_PULLUP);
    Serial.begin(9600);

    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();
}

void loop()
{
    if (digitalRead(buttonStartPin) == LOW)
    {
        Serial.println("Start Sequence.");
        confetti();
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
        tone(buzzerPin, NOTE_F2, 900);
        FastLED.delay(1000);

        noTone(buzzerPin);
        FastLED.clear();
        FastLED.delay(200);
        Serial.println("Beep.");
    }

    delay(200);
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    tone(buzzerPin, NOTE_A5, 900);
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

    if (digitalRead(buttonStopPin) == LOW)
    {
        FastLED.clear();
        FastLED.show();
    }
}

void confetti()
{
    // random colored speckles that blink in and fade smoothly
    for (int counter = 1; counter <= 350; counter++)
    {
        fadeToBlackBy(leds, NUM_LEDS, 10);
        int pos = random16(NUM_LEDS);
        leds[pos] += CHSV(gHue + random8(64), 200, 255);

        FastLED.show();
        FastLED.delay(1000 / FRAMES_PER_SECOND);

        // do some periodic updates
        EVERY_N_MILLISECONDS(5)
        {
            gHue++; // slowly cycle the "base color" through the rainbow
        }
    }

    FastLED.clear();
    FastLED.delay(2000);
}
