### Overview
This simple demo shows how to perform two-way communication between two nodes (in this case two NodeMCU ESP8266 boards) using the SoftwareSerial library. I have seen many demos and tutorial videos showing how to send information across the TX/RX interface, treating one node as sender and the other as receiver.
This demo shows communication between two nodes that can both initiate messages. 
The pins used for RX and TX in the code (D1, D2) are NodeMCU pins GPIO5 and 4 respectively. You can use different GPIO pins if you want. 

My original reason for this two-way async communication between controllers was to create a bridge between a mesh network and a wifi network using two NodeMCU boards wired together. I thought a single device could not be on both networks at the same time, but it turns out it's no big deal. If having a PainlessMesh network make/receive web requests is the reason for your interest, this post over on GitLab shows how to do it all on one node: https://gitlab.com/painlessMesh/painlessMesh/-/issues/368

### Circuit
- Connect D1 and D2 on one ESP to D2 and D1 on the other, respectively. These are the serial communications lines.
- On each controller connect the positive side of a LED to pin D3, and the negative side to a 220-ohm resistor which then goes to GND.
- On Node2 connect a pushbutton between pin D4 and GND.

### Code
Node1.ino should be uploaded to one ESP controller. Node2.ino should be uploaded to the other. 

Node 1 sends a message to Node 2 every 3 seconds, alternating between "daylight" and "nighttime". Every message is terminated with an "\n" character. Node 2 receives messages by calling the SoftwareSerial method readStringUntil('\n'). This reads from the serial buffer up until the '\n' character and returns just the string, without the terminator. If the message is "nighttime" the code turns on the led at D3, and turns it off if the message is "daytime". The code then sends Node 1 a serial message that says either "ON" or "OFF" to indicate what it did. Node 1 turns the led at its D3 to show that it received the message. 

The button attached to D4 on Node 2 simulates a motion detector. When the button is pressed Node 2 sends the message "MOTION" to Node 1. When the button is released it sends the message "NOMOTION". The checkButton() function debounces the button by setting a bool isDown when the button's state is read by digitalRead, and comparing it with a global bool isMotion. When they are different it means the button state has changed. 

For additional confirmation of what is going on, both nodes also display all received messages in the serial monitor. 

When Node 1 receives the message "MOTION" or "NOMOTION" it turns the led on its pin D4 on or off, respectively.

### No Collision Checking
The method shown here is not robust for high-speed asynchronous communication, because it has no provision for handling collisions (receiving a message while another message is being processed). But it should be fine for home automation applications where a low volume of messages is expected. 

#### IDE tip
To open a separate serial monitor for each node, start the Arduino IDE twice: with one IDE instance running, open another by holding the SHIFT key down while you click the IDE icon. Note that all files that are open 
in the first IDE instance will be opened again by the second, so after opening your desired file you should close the duplicate IDE windows to avoid confusion. You can actually 
open as many IDE instances as you want. Each one will have its own Port assignment and its own serial monitor.

