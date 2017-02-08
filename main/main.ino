
#include "TinyWireS.h"

#define LED 1

bool led_on = true;

void setup()
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    
    TinyWireS.begin(36);
    TinyWireS.onRequest(requestEvent);
    TinyWireS.onReceive(receiveEvent);
}

void loop()
{
}

int n = 0;

volatile const uint8_t* response;

const uint8_t pingResponse[] = { 0x01, 0x01 };
const uint8_t listPinsResponse[] = { 0x04, 0x01, 0x01, 0x03, 0x05 };
const uint8_t listCapabilitiesResponse[] = { 0x08, 0x00, 0xEF, 0x01, 0xEF, 0xFF, 0x05, 0xFF, 0xFF };
const uint8_t deviceIdentifierResponse[] = { 0x01, 0x01 };
const uint8_t deviceVersionResponse[] = { 0x01, 0x80 };

volatile byte responsePosition;
volatile byte responseLength;


void requestEvent()
{
    if (responsePosition < responseLength)
    {
        TinyWireS.send(response[responsePosition]);
        responsePosition++;
    }
}

void receiveEvent(uint8_t howMany)
{
    switch (TinyWireS.receive())
    {
        case 0x00:
            if (howMany < 2)
            {
                return;
            }
            switch (TinyWireS.receive())
            {
                case 0x01:
                    response = pingResponse;
                    responsePosition = 0;
                    responseLength = sizeof(pingResponse);
                    break;
                case 0x02:
                    response = listPinsResponse;
                    responsePosition = 0;
                    responseLength = sizeof(listPinsResponse);
                    break;
                case 0x03:
                    response = listCapabilitiesResponse;
                    responsePosition = 0;
                    responseLength = sizeof(listCapabilitiesResponse);
                    break;
                case 0x04:
                    response = deviceIdentifierResponse;
                    responsePosition = 0;
                    responseLength = sizeof(deviceIdentifierResponse);
                    break;
                case 0x05:
                    response = deviceVersionResponse;
                    responsePosition = 0;
                    responseLength = sizeof(deviceVersionResponse);
                    break;
                default:
                    // unknown command
                    break;
            }
            
            break;
        default:
            // unknown command
            break;
    }
}

