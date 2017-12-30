//
// This file is governed by the MITA license
// which can be found as MITA.LICENSE in the root of this project
// (or alternative at mita.jasperhorn.nl)
//

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
