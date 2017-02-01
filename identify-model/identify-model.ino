
#define LED_MODEL_A 1
#define LED_MODEL_B 0

void setup()
{
  pinMode(LED_MODEL_A, OUTPUT);
  pinMode(LED_MODEL_B, OUTPUT);

  digitalWrite(LED_MODEL_B, HIGH);
}

void loop()
{
  digitalWrite(LED_MODEL_A, HIGH);
  delay(500);

  digitalWrite(LED_MODEL_A, LOW);
  delay(500);
}
