#include<ESP8266WiFi.h>
#include<ArduinoJson.h>
#define ssid  "ANDRIOD 540"         // your network SSID (name)
#define pass  "tiger300"
#define server  "io.adafruit.com"
#define user "pratik12345"
#define key "aio_rZxz83OiFVDNisIS72dEj3QIeJtQ"
#define IO_GROUP "home"

unsigned long lastConnectionTime = 0;              // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 7000;  
WiFiClient client;    
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Connecting to Wifi");
 WiFi.begin(ssid,pass);
 while(WiFi.status()!= WL_CONNECTED){
  Serial.print(".");
  delay(500);
  }
 Serial.println("Wifi Connected");
 
  
  

}
void httpRequest() 
{
  
/*
 * https://io.adafruit.com/api/docs/#operation/createGroupData
 * 
 * POST /{username}/groups/{group_key}/data
 * 
 * JSON:
 * 
{
  "location": {
    "lat": 0,
    "lon": 0,
    "ele": 0
  },
  "feeds": [
    {
      "key": "string",
      "value": "string"
    }
  ],
  "created_at": "string"
}
 */
  const size_t capacity = 300;
  //StaticJsonDocument<capacity> doc;
   // Add the "location" object
  //JsonObject test1 = doc.to<JsonObject>();
  //test1["test"] = 40;
  StaticJsonDocument<300> doc;
  JsonArray ok = doc.createNestedArray("feeds");
  JsonObject feed1 = ok.createNestedObject();
  feed1["key"] = "hum";
  feed1["value"] = 22;
  JsonObject feed2 = ok.createNestedObject();
  feed2["key"] = "temp";
  feed2["value"] = 34;
  
  // Add the "feeds" array
 
  
  
  
  // Add the "feeds" array
  
 
  
  // close any connection before send a new request.
  // This will free the socket on the Nina module
  client.stop();
  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 80)) 
  {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("POST /api/v2/" user "/groups/" IO_GROUP "/data HTTP/1.1"); 
    client.println("Host: io.adafruit.com");  
    client.println("Connection: close");  
    client.print("Content-Length: ");  
    client.println(measureJson(ok));  
    client.println("Content-Type: application/json");  
    client.println("X-AIO-Key: " key); 
    // Terminate headers with a blank line
    client.println();
    // Send JSON document in body
    serializeJson(doc, client);
    serializeJson(doc, Serial);
    // note the time that the connection was made:
    lastConnectionTime = millis();
    
    Serial.println("data sent!");
  }
    
   else {
    // if you couldn't make a connection:
    
    Serial.println("connection failed!");
  }
}


void loop() {
  // put your main code here, to run repeatedly:
   
   if (millis() - lastConnectionTime > postingInterval) 
  {
    
    httpRequest(); // send data to Cloud
  }
     

}
