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
#include <WiFi.h>
#include <WiFiUdp.h>

#define BUFFER_MAX 2048
#define PORT 2390


class WifiManager{

  public:
    
    WifiManager();
    
    void setup();
    void update();

    void WiFiEvent(WiFiEvent_t event);

  private:

    void initializeWifi();

    char ssid[];
    char pass[];
    boolean connected;

    WiFiUDP Udp;
    unsigned char packetBuffer[BUFFER_MAX];
};


void WifiManager::WifiManager()
{
    ssid = "TPH Operations";
    password = "TheFUTURE!Sno3";
    connected = false;

}

void WifiManager::setup()
{
    initializeWifi();
}

void WifiManager::initializeWifi()
{
    WiFi.disconnect(true);
    delay(200);
    WiFi.setAutoReconnect(true);
    WiFi.setAutoConnect(true);

    //Initiate connection
    WiFi.begin(ssid, pwd);

    //register event handlerpin
    WiFi.onEvent(WifiManager::WiFiEvent);

    Serial.println("Waiting for WIFI connection...");
}


void WifiManager::update()
{

}


//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
          Udp.begin(WiFi.localIP(),PORT);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          //software_Reset();
          break;
    }
}