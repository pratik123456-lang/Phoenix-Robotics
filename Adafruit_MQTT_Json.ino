#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h>
#define ssid "ANDRIOD 540"
#define pass "tiger300"
#define server "io.adafruit.com"
#define port 1883
#define user "pratik12345"
#define key "aio_rZxz83OiFVDNisIS72dEj3QIeJtQ"
int t=50;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client,server,port,user,key);
Adafruit_MQTT_Publish test=Adafruit_MQTT_Publish(&mqtt,user "/groups/home/json");
//Adafruit_MQTT_Publish test1=Adafruit_MQTT_Publish(&mqtt,user "/feeds/ultrasonic sensor/json");
void connect_MQTT(){
  if(mqtt.connected()){
    return;
    }
  Serial.println("Connecting to MQTT");
  int ret,retries=3;
  while((ret=mqtt.connect()!=0)){
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying the connect after 5 seconds..");
    mqtt.disconnect();
    retries--;
    if(retries==0){
      while(1);
      }
    }
   Serial.println("MQTT Connected"); 
}
void connect_MQTT();
void setup() {
 Serial.begin(9600);
 Serial.println("Connecting to Wifi");
 WiFi.begin(ssid,pass);
 while(WiFi.status()!= WL_CONNECTED){
  Serial.print(".");
  delay(500);
  }
 Serial.println("Wifi Connected");
 
}
void loop() {
  connect_MQTT();
  
  
  
    t--;
    StaticJsonDocument<300> doc;
    JsonArray ok = doc.createNestedArray("feeds");
    
    //JsonArray ok = doc.createNestedArray("feeds");   
    JsonObject JSON_encoder = ok.createNestedObject();
    JsonObject JSON_encoder1 = ok.createNestedObject();
    
    
    JSON_encoder["key"]="hum";
    JSON_encoder["value"]=57;
    JSON_encoder1["key"]="temp";
    JSON_encoder1["value"]=54;
    
    //JSON_encoder["ultrasonic sensor"]=35;
    
    serializeJson(doc,Serial);
    //Serial.println(t);
    char Z[300];
    serializeJson(doc,Z);
    
    if(test.publish(Z))

  {
    Serial.print("data is published");
    //serializeJsonPretty(doc, Serial);
    
  }
  else{
    Serial.println("data is not published");
  }
   //test1.publish(Z);
  
  
  delay(5000);
  
}
 
 
