/* Udp Server
 * Send back what it receive from client
 */


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


WiFiUDP Udp;
char packetBuffer[128];
unsigned int localPort = 9999;
const char *ssid = "ESP8266UdpTest";
const char *password = "esp8266udp";
bool tickerOccured;

byte ledPin = 2;

void setup() {
  delay(2000);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.print("\nAg kuruldu: ");
  Serial.println(WiFi.softAPIP());
  Udp.begin(localPort);
  Serial.print("Udp basladi Port: ");
  Serial.println(Udp.localPort());

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  delay(1000);
  digitalWrite(ledPin, HIGH);
  }

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0)
      packetBuffer[len-1] = 0;
    
    //Serial.print("Received : ");   
    Serial.println(packetBuffer);
   
    Udp.beginPacket(Udp.remoteIP(),Udp.remotePort());
    Udp.write(packetBuffer);
    Udp.write("\r\n");
    Udp.endPacket();
     }
}
