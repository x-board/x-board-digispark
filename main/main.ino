
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
                    responseLength = 2;
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

