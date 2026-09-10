#include <Arduino.h>

constexpr uint8_t LED = 9;
constexpr uint8_t BRIGHTNESS_MIN = 15;
constexpr uint8_t BRIGHTNESS_MAX = 240;
constexpr uint8_t STEP_DELAY_MS = 10;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    for (uint8_t brightness = BRIGHTNESS_MIN; brightness <= BRIGHTNESS_MAX; brightness++)
    {
        analogWrite(LED, brightness);
        delay(STEP_DELAY_MS);
    }
    for (uint8_t brightness = BRIGHTNESS_MAX; brightness >= BRIGHTNESS_MIN; brightness--)
    {
        analogWrite(LED, brightness);
        delay(STEP_DELAY_MS);
    }
}
