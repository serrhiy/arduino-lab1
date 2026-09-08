#include <Arduino.h>

constexpr uint8_t led = 12;
constexpr uint8_t button = 2;

void setup()
{
    pinMode(button, INPUT);
    pinMode(led, OUTPUT);
}

void loop()
{
    const uint8_t button_state = digitalRead(button);
    digitalWrite(led, button_state);
}
