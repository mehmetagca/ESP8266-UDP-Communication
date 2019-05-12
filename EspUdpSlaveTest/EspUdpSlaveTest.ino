// udp client

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>
#include <Ticker.h>
Ticker ticker;
WiFiUDP Udp;
const char *ssid = "ESP8266UdpTest";
const char *password = "esp8266udp";
bool tickerOccured = false;
char packetBuffer[255];
unsigned int localPort = 9999;
IPAddress ipServer(192, 168, 4, 1);
IPAddress ipClient1(192, 168, 4, 10);
IPAddress ipClient2(192, 168, 4, 11);
IPAddress ipClient3(192, 168, 4, 12);
IPAddress Subnet(255, 255, 255, 0);

void ticker_handler(){
  tickerOccured = true;
}


void setup() {
  Serial.begin(115200);
  ticker.attach(1, ticker_handler);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA); // STA important !!!
  WiFi.config(ipClient2, ipServer, Subnet);
  Udp.begin(localPort);
  delay(1000);
}

void loop() {
 
//**************** Send to server**********************************************************
    Udp.beginPacket(ipServer,9999);
    char sbuf[128];
    int serialKontrol = 1;
    
    char testData[255];
    if(Serial.available() < 1)//Is Serial Available?
      serialKontrol = 0;
      //strcpy(testData,"Test"); //millis();
    else
    {
      int len = Serial.readBytes(testData, 255);
      if (len > 0)
         testData[len] = 0;
    }

    if(serialKontrol == 1)
    {
      //sprintf(sbuf, "%lu", testData);
      sprintf(sbuf, "%s", testData);   
      Udp.write(sbuf);
      Udp.write("\r\n");
      Udp.endPacket();
      Serial.print("S : ");Serial.println(sbuf);
      delay(70);
    }
 
//***************** Receive from server ****************************************************
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len-1] = 0;
    Serial.print("R : ");   
    Serial.println(packetBuffer);
  }
//Serial.println();
if (tickerOccured) {
  Serial.println ("ticker occured"); // Testing ticker
  tickerOccured = false;
}

delay(100);
//delay(2);
} 
