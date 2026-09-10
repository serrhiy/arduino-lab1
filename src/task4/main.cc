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

constexpr uint8_t LED = 9;
constexpr uint8_t BUTTON = 3;
constexpr uint8_t BRIGHTNESS_MIN = 15;
constexpr uint8_t BRIGHTNESS_MAX = 240;
constexpr uint8_t STEP_DELAY_MS = 10;

enum class LedState : uint8_t
{
    Off,
    RampUp,
    RampDown,
    SolidMax,
};

constexpr LedState NextState(LedState state) noexcept
{
    constexpr uint8_t STATE_COUNT = 4;
    return static_cast<LedState>((static_cast<uint8_t>(state) + 1) % STATE_COUNT);
}

Button button{BUTTON};
LedState state = LedState::Off; // initial state

void setup()
{
    pinMode(LED, OUTPUT);
    button.begin();
}

void loop()
{
    if (!button.isButtonPressed())
    {
        return;
    }

    state = NextState(state);
    switch (state)
    {
    case LedState::RampUp:
        for (uint8_t brightness = BRIGHTNESS_MIN; brightness <= BRIGHTNESS_MAX; brightness++)
        {
            analogWrite(LED, brightness);
            delay(STEP_DELAY_MS);
        }
        break;
    case LedState::RampDown:
        for (uint8_t brightness = BRIGHTNESS_MAX; brightness >= BRIGHTNESS_MIN; brightness--)
        {
            analogWrite(LED, brightness);
            delay(STEP_DELAY_MS);
        }
        break;
    case LedState::SolidMax:
        analogWrite(LED, BRIGHTNESS_MAX);
        break;
    case LedState::Off:
        analogWrite(LED, 0);
        break;
    }
}
