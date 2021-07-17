//node2

#include <SoftwareSerial.h>
SoftwareSerial sender(D1,D2);   // connect to TX/RX on the other node
// NOTE: these pins must be disconnected during upload to avoid a port error

void checkSerial() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    Serial.println("Node2 received " + msg);
    if (msg == "daytime") {
      sender.write("Node 2 turning lights OFF\n");
    } else if (msg == "nighttime") {
      sender.write("Node2 turning lights ON\n");
    }
  }
}

void setup() {
  delay(10000);  // connecting wires
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Node 2 Active");
  sender.begin(9600);
}

void loop() {
  checkSerial();
  delay(100);
}
