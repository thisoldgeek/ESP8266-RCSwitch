# **ESP8266-RCSwitch**
## *Description:*
This is an Arduino IDE project that targets the cheap ESP8266 WiFi module. The example program 
will turn a 433MHz remote power outlet on or off from a web page served by the ESP8266.

This is a very quick-and-dirty demonstration to get you started!

## *Configuration:*
* Download, Install and test the IDE per instructions at http://makezine.com/2015/04/01/installing-building-arduino-sketch-5-microcontroller/
* Download and Install the ESP8266-RCSwitch from this git into your sketchbook
* Add the RCSwitch Library from xxxxxx to your Arduino IDE
* Find the codes for your RC Switch using https://github.com/ninjablocks/433Utils (RF_Sniffer.ino)
* Modify the ESP8266-RCSwitch sketch, changing the on and off codes to the codes you sniffed using the RF_Sniffer and the outlet-supplied remote control
* NOTE: EtekCity Remote Outlets use pulselength = 189
* Modify the SSID and PASSWD values in the sketch to look for your WiFi router

## *Testing:*
* Run the Serial Monitor from the new IDE to find the IP address or use your router's client tools to find it
* http://"ESP8266ip"/sw1/0 = OFF; http://"ESP8266ip"/sw1/1 = ON

