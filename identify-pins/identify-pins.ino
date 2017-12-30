void setup() {
    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
}

void loop() {
    for (int i = 1; i < 6; i++)
    {
        for (int pin = i; pin < 6; pin++)
        {
            if (pin != 2)
            {
                digitalWrite(pin, HIGH);
            }
        }

        delay(400);

        for (int pin = i; pin < 6; pin++)
        {
            if (pin != 2)
            {
                digitalWrite(pin, LOW);
            }
        }
        
        delay(400);
    }

    delay(1000);

}
