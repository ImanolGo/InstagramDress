
 /*
  
  Insragram Dress
     
 Description:
 * Firmware receiving parsing Instagram hashtags and changing them into light patterns

 Software:
 * Adafruit_NeoPixel Library 
 * Wifi Library 
 * WifiUdp Library
 
 Hardware:
* Adafruit Feather HUZZAH – ESP8266 Feather Board
* NeoPixels Led Strip

 created 13 March 2018
 This code is under A Creative Commons Attribution/Share-Alike License http://creativecommons.org/licenses/by-sa/4.0/
   (2018) by Imanol Gómez

 */
 

#include "WifiManager.h"


WifiManager wifiManager;

void setup() {
  
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting Software!!!!");
    
    wifiManager.setup();
}

void loop() 
{
    wifiManager.update();
    
  // put a delay so it isn't overwhelming
  //delay(10);
}
