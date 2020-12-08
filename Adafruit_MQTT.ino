#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#define ssid "ANDRIOD 540"
#define pass "tiger300"
#define server "io.adafruit.com"
#define port 1883
#define user "pratik12345"
#define key "aio_rZxz83OiFVDNisIS72dEj3QIeJtQ"
int t=40;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client,server,port,user,key);
Adafruit_MQTT_Publish test=Adafruit_MQTT_Publish(&mqtt,user "/feeds/test");
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
  
  while(t!=0){
    t--;
    
  
  if(test.publish(t))
  {
    Serial.print("data is published");
    Serial.println(t);
  }
  else{
    Serial.println("data is not published");
  }
  delay(5000);
  }
}
 
 
