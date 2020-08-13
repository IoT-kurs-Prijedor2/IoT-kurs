//***
//ArduinoJson biblioteka treba biti verzija 6.0 i više
//Struktuiranje json dokumenta se može uraditi na: https://jsonlint.com/
//***
int timeZone = 2;
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>

const char* ssid = "Gosti";
const char* password =  "preda2020";
 
const String server = "http://api.openweathermap.org/data/2.5/weather?q=Prijedor,ba&units=metric&appid=2ba02e990e66e60cc5089be1508137e9";
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin(server); //Specify the URL
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { //Check for the returning code

        DynamicJsonDocument doc(2048);
        
        String input = http.getString();
        Serial.println(httpCode);
        //Serial.println(input);

        deserializeJson(doc, input);
        //JsonObject obj = doc.as<JsonObject>();

  // You can use a String to get an element of a JsonObject
  // No duplication is done.
  String temp = doc["main"]["temp"];
  String updateTime = doc["dt"];
  
  //time
  static const time_t unixtimestamp = updateTime.toInt();;
  struct tm *tmp = gmtime(&unixtimestamp);

  //printf("%02d:%02d:%02d\n", tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
  int h = tmp->tm_hour + timeZone;
  int m = tmp->tm_min;
  int s = tmp->tm_sec;

  Serial.print ("Last updated at: ");
  Serial.print (h);
  Serial.print (":");
  Serial.print (m);
  Serial.print (":");
  Serial.println (s);
  Serial.print("Trenutna temperatura u Prijedoru: ");
  Serial.print(temp);
  Serial.println(" °C"); 

  //Konverzija u integer varijablu ako želimo manipulisati sa vrijednošću (sabirati, oduzimati i sl.)
  //int padavine = weather.toInt();
  //Serial.println(padavine);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
  delay(30000);
 
}
