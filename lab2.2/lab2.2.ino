const int photoresistorPin = A0; 
int timerIntervals[] = {1000, 2000, 5000, 10000, 30000};
unsigned long previousMillis[5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis[i] >= timerIntervals[i]) {
      previousMillis[i] = currentMillis;

      int sensorValue = analogRead(photoresistorPin);
      Serial.print("Timer ");
      Serial.print(i + 1);
      Serial.print(", Light Sensor Value: ");
      Serial.println(sensorValue);
    }
  }
}