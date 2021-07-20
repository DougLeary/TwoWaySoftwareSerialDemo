//node2

#include <SoftwareSerial.h>
SoftwareSerial serial(D1,D2);   // connect to TX/RX on the other node

int pinLed = D3;
int pinButton = D4;
bool isMotion = false;

void checkSerial() {
  if (serial.available()) {
    String msg = serial.readStringUntil('\n');
    Serial.println("Received " + msg);
    if (msg == "daytime") {
      digitalWrite(pinLed, LOW);
      Serial.println("Sending OFF");
      serial.write("OFF\n");
    } else if (msg == "nighttime") {
      digitalWrite(pinLed, HIGH);
      Serial.println("Sending ON");
      serial.write("ON\n");
    }
  }
}

void checkButton() {
  bool isDown = (digitalRead(pinButton) == LOW);
  if (isDown != isMotion) {
    isMotion = isDown;
    if (isMotion) {
      Serial.println("Sending MOTION");
      serial.write("MOTION\n");
    } else {
      Serial.println("Sending NOMOTION");
      serial.write("NOMOTION\n");
    }
  }
}

void setup() {
  pinMode(D3, OUTPUT);
  pinMode(D4, INPUT_PULLUP);

  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("Node 2 Running");
  serial.begin(9600);
}

void loop() {
  checkSerial();
  checkButton();
}
