/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a switch depending on the request
 *    http://server_ip/sw1/0 will turn sw1 off
 *    http://server_ip/sw1/1 will turn sw1 on
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */
#include "RCSwitch.h"
#include <ESP8266WiFi.h>

RCSwitch mySwitch = RCSwitch();

const char* ssid = "SSID";
const char* password = "PASSWORD";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  
  // Transmitter is connected to ESP8266 PIN #2
  mySwitch.enableTransmit(2);
  //EtekCity ZAP Remote Outlets use pulse of approximately 189
  mySwitch.setPulseLength(189);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("/sw1/0") != -1) {
      val = 0;
      // Insert your "OFF" code here, before ", 24)"
      mySwitch.send(12345, 24);}
  else if (req.indexOf("/sw1/1") != -1) {
      val = 1;
      // Insert your "ON" code here, before ", 24)"
      mySwitch.send(54321, 24);
  }
  else if (req.indexOf("favicon.ico") != -1) {
      // ignore favicon requests from browser
      val = -1;
  }
  else {
      val = -10;
      Serial.println("invalid request");
  }
  
  client.flush();

  // Prepare the response
  // Handle (ignore) favicon requests with a 404 response
  // https://github.com/esp8266/Arduino/issues/2080
  String s;
  if (val == -1){
    s = "HTTP/1.1 404 \r\n";
  }
  // handle invalid requests
  else if (val == -10){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nInvalid request! ";
    s += "\r\nEnter URL as: \"&lt;ip-address&gt;/sw1/&lt;VAL&gt;\" where &lt;VAL&gt; is 0 or 1";
    s += "</html>\n";
  }
  // correct requests
  else{
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nSwitch 1 is now ";
    s += (val)?"ON":"OFF";
    s += "</html>\n";
  }
  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
