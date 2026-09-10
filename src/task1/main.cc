#include <Arduino.h>

#include <morse.hh>

constexpr uint8_t unit_time_ms = 150;

constexpr uint8_t led = 12;

constexpr char message[] = "Lyt";

constexpr uint16_t GetMsDelay(morse::MorseUnit morse_unit)
{
    return morse_unit == morse::MorseUnit::DOT ? unit_time_ms : unit_time_ms * 3;
}

void setup()
{
    pinMode(led, OUTPUT);
}

void loop()
{
    for (size_t index = 0; index + 1 < sizeof(message); index++)
    {
        for (morse::MorseUnit unit : morse::GetMorseCode(message[index]))
        {
            digitalWrite(led, HIGH);
            delay(GetMsDelay(unit));
            digitalWrite(led, LOW);
            delay(unit_time_ms);
        }
        delay(unit_time_ms * 2);
    }
    delay(unit_time_ms * 4);
}
