#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>

int status = WL_IDLE_STATUS;
char ssid[] = "TPH Operations"; //  your network SSID (name)
char pass[] = "TheFUTURE!Sno3";    // your network password (use for WPA, or use as key for WEP)


void setup() {

  Serial.begin(115200);
  delay(200);
  
  WiFi.disconnect();
  delay(200); 

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  //udp_comm.begin(5005);
  //udp_comm.beginMulticast(broadcast, (uint16_t)8888);
  //server.beg
  Serial.println();
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  
  Serial.println("Connected to wifi");
  printWifiStatus();

}


void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    Serial.println("GET");
    
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("https://www.instagram.com/explore/tags/happy/?__a=1");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println(httpCode);   
    
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(3000);    //Send a request every 30 seconds
 
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

