
#include <inttypes.h>

enum PinMode
{
    NONE,
    DIGITAL,
    PWM,
    DIGITAL_BLINK
};

class PinState
{
private:
    PinMode pinMode;
    uint8_t value1;
    uint8_t value2;
    
public:
    PinState()
    {
        pinMode = NONE;
        value1 = 0;
        value2 = 0;
    }

    PinMode getPinMode()
    {
        return pinMode;
    }

    void setPwmValue(uint8_t value)
    {
        pinMode = PWM;
        value1 = value;
    }

    uint8_t getPwmValue()
    {
        return value1;
    }

    void setDigitalValue(uint8_t value)
    {
        pinMode = DIGITAL;
        value1 = value;
    }

    uint8_t getDigitalValue()
    {
        return value1;
    }

    void setDigitalBlink(uint8_t onTime, uint8_t offTime)
    {
        pinMode = DIGITAL_BLINK;
        value1 = onTime;
        value2 = offTime;
    }

    uint8_t getOnTime()
    {
        return value1;
    }

    uint8_t getOffTime()
    {
        return value2;
    }
    
    bool operator==(const PinState& other)
    {
        return pinMode == other.pinMode && value1 == other.value1 && value2 == other.value2;
    }

    bool operator!=(const PinState& other)
    {
        return !(*this == other);
    }

    void operator=(PinState other)
    {
        pinMode = other.pinMode;
        value1 = other.value1;
        value2 = other.value2;
    }
};

