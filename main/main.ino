
#include "TinyWireS.h"
#include "PinState.h"

bool led_on = true;

PinState currentPinStates[6];
PinState setPinStates[6];

void setup()
{
    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    
    TinyWireS.begin(36);
    TinyWireS.onRequest(requestEvent);
    TinyWireS.onReceive(receiveEvent);
}

void loop()
{
    for (int i = 0; i < 6; i++)
    {
        if (setPinStates[i] != currentPinStates[i])
        {
            switch(setPinStates[i].getPinMode())
            {
            case DIGITAL:
                digitalWrite(i, setPinStates[i].getDigitalValue());
                break;

            case PWM:
                analogWrite(i, setPinStates[i].getPwmValue());
                break;
            }

            currentPinStates[i] = setPinStates[i];
        }
    }

    int time = millis();
    
    for (int i = 0; i < 6; i++)
    {
        switch(currentPinStates[i].getPinMode())
        {
        case DIGITAL_BLINK:
            uint8_t onTime = currentPinStates[i].getOnTime();
            uint8_t offTime = currentPinStates[i].getOffTime();
            
            if (time % (((unsigned long)offTime + (unsigned long)onTime) * 100)  >= (unsigned long)offTime * 100)
            {
                digitalWrite(i, HIGH);
            }
            else
            {
                digitalWrite(i, LOW);
            }
            break;
        }
    }
}

volatile const uint8_t* response;

const uint8_t pingResponse[] = { 0x01 };
const uint8_t protocolVersionResponse[] = { 0x00, 0x00, 0x00, 0x01 };
const uint8_t listPinsResponse[] = { 0x01, 0x01, 0x03, 0x05 };
const uint8_t listPinsLengthResponse[] = { sizeof(listPinsResponse) };
const uint8_t listCapabilitiesResponse[] = { 0x00, 0xFE, 0x01, 0xFE, 0xFF, 0x07, 0xFF, 0x01, 0xFE, 0x01, 0x02, 0xFE, 0x01, 0xFE, 0x01, 0x04, 0xFF, 0xFF, 0xFF};
const uint8_t listCapabilitiesLengthResponse[] = { 0x00, sizeof(listCapabilitiesResponse) };
const uint8_t deviceIdentifierResponse[] = { 0x00, 0x01 };
const uint8_t deviceVersionResponse[] = { 0x00, 0x00, 0x00, 0x01 };

volatile byte responsePosition = 0;
volatile byte responseLength = 0;


void requestEvent()
{
    if (responsePosition < responseLength)
    {
        TinyWireS.send(response[responsePosition]);
        responsePosition++;
    }
    else
    {
        TinyWireS.send(0x00);
    }
}

void receiveEvent(uint8_t howMany)
{
    responseLength = 0;

    howMany--;
    switch (TinyWireS.receive())
    {
        case 0x00:
            if (howMany < 1)
            {
                return;
            }
            howMany--;
            switch (TinyWireS.receive())
            {
                case 0x01:
                    response = pingResponse;
                    responseLength = sizeof(pingResponse);
                    responsePosition = 0;
                    break;
                case 0x02:
                    response = protocolVersionResponse;
                    responseLength = sizeof(protocolVersionResponse);
                    responsePosition = 0;
                    break;
                case 0x03:
                    response = listPinsLengthResponse;
                    responseLength = sizeof(listPinsLengthResponse);
                    responsePosition = 0;
                    break;
                case 0x04:
                    response = listPinsResponse;
                    responseLength = sizeof(listPinsResponse);
                    responsePosition = 0;
                    break;
                case 0x05:
                    response = listCapabilitiesLengthResponse;
                    responseLength = sizeof(listCapabilitiesLengthResponse);
                    responsePosition = 0;
                    break;
                case 0x06:
                    response = listCapabilitiesResponse;
                    responseLength = sizeof(listCapabilitiesResponse);
                    responsePosition = 0;
                    break;
                case 0x07:
                    response = deviceIdentifierResponse;
                    responseLength = sizeof(deviceIdentifierResponse);
                    responsePosition = 0;
                    break;
                case 0x08:
                    response = deviceVersionResponse;
                    responseLength = sizeof(deviceVersionResponse);
                    responsePosition = 0;
                    break;
                default:
                    // unknown command
                    break;
            }
            break;
            
        case 0x01:
            if (howMany < 1)
            {
                return;
            }
            howMany--;
            switch (TinyWireS.receive())
            {
                case 0x01:
                {
                    if (howMany < 2)
                    {
                        return;
                    }
                    howMany--;
                    howMany--;
                    uint8_t pin = TinyWireS.receive();
                    uint8_t value = TinyWireS.receive();

                    if (pin == 0 || pin == 2 || pin > 5 || (value != 0 && value != 1))
                    {
                        return;
                    }

                    setPinStates[pin].setDigitalValue(value == 1 ? HIGH : LOW);
                    break;
                }
                case 0x02:
                {
                    if (howMany < 3)
                    {
                        return;
                    }
                    howMany--;
                    if (TinyWireS.receive() != 0x02)
                    {
                        return;
                    }

                    howMany--;
                    howMany--;
                    uint8_t pin = TinyWireS.receive();
                    uint8_t value = TinyWireS.receive();

                    if (pin != 1 && pin != 4)
                    { 
                        return;
                    }

                    setPinStates[pin].setPwmValue(value);
                    break;
                }
                case 0x04:
                {
                    if (howMany < 4)
                    {
                        return;
                    }
                    howMany--;
                    if (TinyWireS.receive() != 0x01)
                    {
                        return;
                    }

                    howMany--;
                    howMany--;
                    howMany--;
                    uint8_t pin = TinyWireS.receive();
                    uint8_t onTime = TinyWireS.receive();
                    uint8_t offTime = TinyWireS.receive();

                    if (pin == 0 || pin == 2 || pin > 5)
                    { 
                        return;
                    }

                    setPinStates[pin].setDigitalBlink(onTime, offTime);
                    break;
                }
                default:
                {
                    // unknown command
                    break;
                }
            }
            
            break;
        default:
            // unknown command
            break;
    }

    for (int i = 0; i < howMany; i++)
    {
        TinyWireS.receive();
    }
}

