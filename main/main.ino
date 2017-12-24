
#include "TinyWireS.h"

bool led_on = true;

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
}

volatile const uint8_t* response;

const uint8_t pingResponse[] = { 0x01 };
const uint8_t listPinsResponse[] = { 0x01, 0x01, 0x03, 0x05 };
const uint8_t listPinsLengthResponse[] = { sizeof(listPinsResponse) };
const uint8_t listCapabilitiesResponse[] = { 0x00, 0xFE, 0x01, 0xFE, 0xFF, 0x07, 0xFF, 0x01, 0xFE, 0x01, 0x02, 0xFE, 0x01, 0xFE, 0x01, 0x04, 0xFF, 0xFF, 0xFF};
const uint8_t listCapabilitiesLengthResponse[] = { 0x00, sizeof(listCapabilitiesResponse) };
const uint8_t deviceIdentifierResponse[] = { 0x00, 0x01 };
const uint8_t deviceVersionResponse[] = { 0x80 };

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
                    response = listPinsLengthResponse;
                    responseLength = sizeof(listPinsLengthResponse);
                    responsePosition = 0;
                    break;
                case 0x03:
                    response = listPinsResponse;
                    responseLength = sizeof(listPinsResponse);
                    responsePosition = 0;
                    break;
                case 0x04:
                    response = listCapabilitiesLengthResponse;
                    responseLength = sizeof(listCapabilitiesLengthResponse);
                    responsePosition = 0;
                    break;
                case 0x05:
                    response = listCapabilitiesResponse;
                    responseLength = sizeof(listCapabilitiesResponse);
                    responsePosition = 0;
                    break;
                case 0x06:
                    response = deviceIdentifierResponse;
                    responseLength = sizeof(deviceIdentifierResponse);
                    responsePosition = 0;
                    break;
                case 0x07:
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

                    digitalWrite(pin, value == 1 ? HIGH : LOW);
                    break;
                }
                case 0x02:
                {
                    if (howMany < 3)
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
                    uint8_t pin = TinyWireS.receive();
                    uint8_t value = TinyWireS.receive();

                    if (pin != 1 && pin != 4)
                    { 
                        return;
                    }

                    analogWrite(pin, value);
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

