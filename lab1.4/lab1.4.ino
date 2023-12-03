const int LED_PIN = 32;
const int PWM_CHANNEL = 0; 
const int PWM_FREQ = 5000; 

void setup() {
  Serial.begin(115200);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, 8);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
}

void loop() {
  for (int dutyCycle = 0; dutyCycle <= 255; ++dutyCycle) {
    ledcWrite(PWM_CHANNEL, dutyCycle);
    delay(10);
  }

  for (int dutyCycle = 255; dutyCycle >= 0; --dutyCycle) {
    ledcWrite(PWM_CHANNEL, dutyCycle);
    delay(10);
  }
}
