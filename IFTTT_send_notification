#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Gosti";
const char* password = "preda2020";

// Domain Name with full URL Path for HTTP POST Request
// REPLACE WITH YOUR EVENT NAME AND API KEY - open the documentation: https://ifttt.com/maker_webhooks
const char* serverName = "http://maker.ifttt.com/trigger/esp_n/with/key/d9GvFVGzDIqYjpKvksChC8";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  // Random seed is a number used to initialize a pseudorandom number generator
  randomSeed(analogRead(33));


    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "value1=" + String(1);           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

void loop() {
}
