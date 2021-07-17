// node1
#include <SoftwareSerial.h>
SoftwareSerial sender(D1,D2);   // connect to TX/RX on the other node;
// NOTE: these pins must be disconnected during upload to avoid a port error

uint32_t interval = 3000;
uint32_t previousTime = 0;
bool isDay = false;

void checkSerial() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    Serial.println("Node 1 received " + msg);
  }
}

void setup() {
  delay(10000);  // connecting wires
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Node 1 Active");
  sender.begin(9600);
}

void loop() {
  checkSerial();
  uint32_t msNow = millis();
  if (msNow - previousTime >= interval) {
    previousTime = msNow;
    isDay = !isDay;
    if (isDay) {
      sender.write("daytime\n");
    } else {
      sender.write("nighttime\n");
    }
  }
}
