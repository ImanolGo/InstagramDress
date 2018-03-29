#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "Don't worry, be happy!";
const char* password =  "whyistheskysohigh?";

HTTPClient client;
 
void setup() {
 
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  client.begin("https://www.instagram.com/explore/tags/happy/?__a=1"); //Specify the URL
    int httpCode = client.GET();                                        //Make the request
 
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
     // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }

 
    //http.end(); //Free the resources
  }
 
 // delay(1000);
 
}
