
#include <inttypes.h>

enum PinMode
{
    NONE,
    DIGITAL,
    PWM
};

class PinState
{
private:
    PinMode pinMode;
    uint8_t value1;
    
public:
    PinState()
    {
        pinMode = NONE;
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
    
    bool operator==(const PinState& other)
    {
        return pinMode == other.pinMode && value1 == other.value1;
    }

    bool operator!=(const PinState& other)
    {
        return !(*this == other);
    }

    void operator=(PinState other)
    {
        pinMode = other.pinMode;
        value1 = other.value1;
    }
};

