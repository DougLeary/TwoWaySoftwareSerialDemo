// node1
#include <SoftwareSerial.h>
SoftwareSerial serial(D1,D2);   // connect to TX/RX on the other node;

int pinLed = D3;
int pinLed2 = D4;

uint32_t interval = 3000;
uint32_t previousTime = 0;
bool isDay = false;

void checkSerial() {
  if (serial.available()) {
    String msg = serial.readStringUntil('\n');
    Serial.println("Received " + msg);
    if (msg == "ON") {
      digitalWrite(pinLed, HIGH);
    } else if (msg == "OFF") {
      digitalWrite(pinLed, LOW);
    } else if (msg == "MOTION") {
      digitalWrite(pinLed2, HIGH);
    } else if (msg == "NOMOTION") {
      digitalWrite(pinLed2, LOW);
    }
  }
}

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  digitalWrite(pinLed, LOW);
  digitalWrite(pinLed2, LOW);
  
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("Node 1 Running");
  serial.begin(9600);
}

void loop() {
  checkSerial();
  uint32_t msNow = millis();
  if (msNow - previousTime >= interval) {
    previousTime = msNow;
    isDay = !isDay;
    if (isDay) {
      Serial.println("Sending daytime");
      serial.write("daytime\n");
    } else {
      Serial.println("Sending nighttime");
      serial.write("nighttime\n");
    }
  }
}
