//
// This file is governed by the MITA license
// which can be found as MITA.LICENSE in the root of this project
// (or alternative at mita.jasperhorn.nl)
//

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
    uint8_t value3;
    
public:
    PinState()
    {
        pinMode = NONE;
        value1 = 0;
        value2 = 0;
        value3 = 0;
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

    void setDigitalBlink(uint8_t onTime, uint8_t offTime, uint8_t shiftTime)
    {
        pinMode = DIGITAL_BLINK;
        value1 = onTime;
        value2 = offTime;
        value3 = shiftTime;
    }

    uint8_t getOnTime()
    {
        return value1;
    }

    uint8_t getOffTime()
    {
        return value2;
    }

    uint8_t getShiftTime()
    {
        return value3;
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
        value3 = other.value3;
    }
};

