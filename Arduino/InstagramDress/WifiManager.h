///////////////////////////////////////////////////////////////////
// Class controlling the wifi connection
//
//
// This code is under A Creative Commons Attribution/Share-Alike License
// http://creativecommons.org/licenses/by-sa/4.0/
// 2018, Imanol Gomez
///////////////////////////////////////////////////////////////////

#pragma once
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define BUFFER_MAX 255
#define PACKET_SIZE 4

class WifiManager
{

  public:
    
    WifiManager();
    
    void setup();
    void update();

    void WiFiEvent(WiFiEvent_t event);

  private:

    void initializeWifi();
    void parseUdp();
    void readUdp();
    void connectToWiFi(const char * ssid, const char * pwd);
    bool isMessage(char* _buffer, int bufferSize);
    void parseMessage();
    void sendAutodiscovery();
    void checkWifiConnection();
    void connectWifi();

    String ssid;
    String pass;
    boolean connected;

    WiFiUDP Udp;
    char packetBuffer[BUFFER_MAX];
    unsigned int localPort;
    int receivedUdpLength;

    char PACKET_START;
    char PACKET_END;
    unsigned long autodiscovery_timer;
};


WifiManager::WifiManager()
{
    ssid = "TPH Operations";
    pass = "TheFUTURE!Sno3";
    connected = false;
    localPort = 2390 ;

    PACKET_START = 'd';
    PACKET_END = 255;
    autodiscovery_timer=0;
    receivedUdpLength = 0;
}

void WifiManager::setup()
{
    Serial.println("WifiManager::setup");
    initializeWifi();
}

void WifiManager::initializeWifi()
{
  
    Udp.stop();
    Udp.flush();
  
    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
      // don't continue:
      while (true);
    }

  
   IPAddress ip(192, 168, 20, 11); //  Fixed IP
   IPAddress gateway(192, 168, 20, 1); // set gateway to match your network
   IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
   
    WiFi.config(ip, gateway, subnet);

    Serial.println("WifiManager::connect wifi");
    connectWifi();
}


void WifiManager::connectWifi() {
     // attempt to connect to WiFi network:
   //Serial.print("Attempting to connect to SSID: ");
   //Serial.println(ssid);
   WiFi.begin(ssid.c_str(), pass.c_str());

   int attempts = 0;
  
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("WIFI STATUS ");Serial.println(WiFi.status());
      Serial.print("..");
      attempts++;
      if(attempts>=10){
        break;
      }
   }
 
   Serial.print("\nConnected to SSID: ");
   Serial.println(ssid);

   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  
    Serial.print("\nStarting connection to UDP port ");
    Serial.println(localPort);
    // if you get a connection, report back via serial:
    Udp.begin(localPort);
    Udp.flush();
}



void WifiManager::update()
{
    checkWifiConnection();
    parseUdp();
}


void WifiManager::parseUdp()
{
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {   
       Serial.println("Contents:");
      readUdp();
  }
}

void WifiManager::readUdp()
{
  // read the packet into packetBuffer
    receivedUdpLength = Udp.read(packetBuffer, BUFFER_MAX);

      Serial.println("Contents:");
      Serial.println(packetBuffer);
    
    if(isMessage(packetBuffer, receivedUdpLength)){
      parseMessage();
    }
}



void WifiManager::parseMessage() {
  
    if(receivedUdpLength>=PACKET_SIZE)
    {  
        //Send to light manager
        int color = (int) packetBuffer[1];
        int effect = (int) packetBuffer[2];
        Serial.print("Color:" );
        Serial.println(color);
        Serial.print("Effect:" );
        Serial.println(effect);
   }
}

void WifiManager::connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  IPAddress ip(192, 168, 20, 22); //  Fixed IP
  IPAddress gateway(192, 168, 20, 1); // set gateway to match your network
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network

  // delete old config
  WiFi.disconnect(true);
  delay(100);
  //register event handlerpin
  //WiFi.onEvent(WiFiEvent);
  WiFi.config(ip, gateway, subnet);
  WiFi.setAutoReconnect(true);
  WiFi.setAutoConnect(true);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}


void WifiManager::checkWifiConnection(){
  int status = WiFi.status();
  if(status != WL_CONNECTED) {
       connectWifi();
       //printWiFiStatus();
   }
}


//wifi event handler
void WifiManager::WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case WIFI_EVENT_STAMODE_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
          Udp.begin(localPort);
          Serial.print("Listening to port: ");
          Serial.println(localPort); 
          connected = true;
          break;
      case WIFI_EVENT_STAMODE_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          //software_Reset();
          break;
    }
}


bool WifiManager::isMessage(char* _buffer, int bufferSize){
  
   if(bufferSize<PACKET_SIZE){
    return false;
   }

   if(_buffer[0]!=PACKET_START){
    return false;
   }

   if(_buffer[PACKET_SIZE-1]!=PACKET_END){
    return false;
   }

   Serial.println("MESSAGE RECEIVED!!!");
   return true;
}

