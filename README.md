This simple demo shows how to perform two-way communication between two nodes (in this case two NodeMCU ESP8266 boards) using the SoftwareSerial library. Hopefuly the code is self-explanatory. The pins used for RX and TX in the code (D1, D2) are NodeMCU pins GPIO5 and 4 respectively. You can use different GPIO pins if you want. The circuit is simple - just connect D2 on each node to RX on the other. Each node receives communication by checking for Serial input, which uses the default RX pin. If you want you can simply wire TX to RX and RX to TX, and instantiate the SoftwareSerial object with (RX,TX). I used D1,D2 to illustrate that it would work 

I have seen many demos and tutorial videos showing how to send information across the TX/RX interface, treating one node as sender and the other as receiver.
This demo shows communication in both directions. The method shown here is not robust for high-speed asynchronous communication, because it has no provision for handling collisions (when both nodes
happen to send messages at the same time). But it should be fine for a master/slave application where one node initiates communication and the other responds, or for simple applications
where messages are not being sent every second.

One thing I found out the hard way is that the Arduino IDE will not upload to a node whose TX/RX pins are physically wired to another. You must disconnect these wires to upload code. 
This is an important consideration if you are creating a soldered circuit - you would need to include a disconnect switch on the TX and RX lines (or a normally-closed button you can 
hold down while uploading to keep those lines disconnected. The same problem exists for opening the Serial Monitor - the TX/RX pins must not be connected to another running controller.
If you want to use Serial Monitor for debugging, open it before you hook up the wires. 

Another tip about using Serial Monitor when developing apps that communicate between two devices: you can open separate serial monitors for them if you start the Arduino IDE twice. 
After you have an instance running, simply open the other by holding the SHIFT key down while you click the icon to start the IDE a second time. Note that all files that are open 
in the first IDE instance will be opened again by the second, so after opening your desired file you should close the duplicate IDE windows to avoid confusion. You can actually 
open as many IDE instances this way as you want. Each one will have its own Port assignment and its own serial monitor, which can be open side by side.

