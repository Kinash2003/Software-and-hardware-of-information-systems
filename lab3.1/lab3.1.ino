#include <FS.h>
#include <SPIFFS.h>

const int photoresistorPin = 34; 

struct TimerData {
  unsigned long interval;
  unsigned long lastTrigger;
  const char* fileName;
};

TimerData timers[] = {
  {1000, 0, "/timer1.txt"},
  {2000, 0, "/timer2.txt"},
  {5000, 0, "/timer3.txt"},
  {10000, 0, "/timer4.txt"},
  {30000, 0, "/timer5.txt"}
};

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  Serial.println("SPIFFS Initialized");
}

void loop() {
  for (int i = 0; i < sizeof(timers) / sizeof(timers[0]); i++) {
    unsigned long currentMillis = millis();
    if (currentMillis - timers[i].lastTrigger >= timers[i].interval) {
      int sensorValue = analogRead(photoresistorPin);
      Serial.println("Light Sensor Value: " + String(sensorValue));

      File dataFile = SPIFFS.open(timers[i].fileName, "a");
      if (dataFile) {
        dataFile.print("Timestamp: ");
        dataFile.print(millis());
        dataFile.print(", Light Sensor Value: ");
        dataFile.println(sensorValue);
        dataFile.close();
        Serial.println("Data recorded for Timer " + String(i + 1));
      } else {
        Serial.println("Error opening " + String(timers[i].fileName));
      }

      timers[i].lastTrigger = currentMillis;
    }
  }

  delay(1000);  
}