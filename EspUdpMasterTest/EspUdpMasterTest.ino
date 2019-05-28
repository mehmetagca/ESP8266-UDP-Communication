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

char ipInfo[5];
IPAddress ipClient1(192, 168, 4, 10); //For Client1
IPAddress ipClient2(192, 168, 4, 11); //For Client2
IPAddress ipClient3(192, 168, 4, 12); //For Client3
IPAddress ipClient4(192, 168, 4, 13); //For Client4

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
  delay(2000);
  digitalWrite(ledPin, HIGH);
  }

void loop() {
  digitalWrite(ledPin, HIGH);
  
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    digitalWrite(ledPin, LOW);
    
    int len = Udp.read(packetBuffer, 255);
    if (len > 0)
      packetBuffer[len-1] = 0;
    
    //Serial.print("Received : ");   
    Serial.println(packetBuffer);// UDP Packet
    
    ipInfo[0] = '+';
    ipInfo[1] = '9';
    ipInfo[2] = '\r';
    ipInfo[3] = '\n';
    ipInfo[4] = '\0';
    
    if(Udp.remoteIP() == ipClient1)
      ipInfo[1] = '0';
    else if(Udp.remoteIP() == ipClient2)
      ipInfo[1] = '1';
    else if(Udp.remoteIP() == ipClient3)
      ipInfo[2] = '2';
    else if(Udp.remoteIP() == ipClient4)
      ipInfo[3] = '3';
    
    Serial.println(ipInfo);// IP Info

    /* For Acknowledge
    Udp.beginPacket(Udp.remoteIP(),Udp.remotePort());
    Udp.write(packetBuffer);
    Udp.write("\r\n");
    Udp.endPacket();
    */
    }
}
