#include <Arduino.h>

class Button final
{
    static constexpr unsigned long DEBOUNCE_MS = 5;

    uint8_t button_pin;
    int idle_status;
    int last_button_status;
    unsigned long last_time_called;

  public:
    explicit Button(uint8_t button_pin, int idle_status = LOW) noexcept
        : button_pin{button_pin}, idle_status{idle_status}, last_button_status{idle_status}, last_time_called{0}
    {
    }

    void begin() const noexcept
    {
        pinMode(button_pin, INPUT);
    }

    bool isButtonPressed() noexcept
    {
        if (last_time_called == 0)
        {
            const int current_button_status = digitalRead(button_pin);
            if (current_button_status != last_button_status)
            {
                last_time_called = millis();
            }
            return false;
        }
        else if (millis() - last_time_called <= DEBOUNCE_MS)
        {
            return false;
        }
        last_time_called = 0;
        const int current_button_status = digitalRead(button_pin);
        if (current_button_status != last_button_status)
        {
            last_button_status = current_button_status;
            return current_button_status != idle_status;
        }
        return false;
    }
};

constexpr uint8_t led = 2;
Button button{3};

void setup()
{
    pinMode(led, OUTPUT);
    button.begin();
}

void loop()
{
    if (button.isButtonPressed())
    {
        const int led_status = digitalRead(led);
        const int target_led_status = led_status == LOW ? HIGH : LOW;
        digitalWrite(led, target_led_status);
    }
}
