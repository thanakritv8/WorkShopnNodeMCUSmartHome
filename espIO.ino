#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define FIREBASE_HOST "deviceio-fae1f.firebaseio.com"
#define FIREBASE_KEY "t0uMQGkmBqgiEeElcCwRhOkpXAHyoJ4w1YoMggbC"

#define IO1 4
#define IO2 0
#define IO3 14
#define ConfigWiFi_Pin 5 

#define ESP_AP_NAME "SmartHome"

String id = "Thung";

void setup() {
  Serial.begin(115200);
  pinMode(IO1,OUTPUT);
  pinMode(IO2,OUTPUT);
  pinMode(IO3,OUTPUT);
  pinMode(ConfigWiFi_Pin,INPUT_PULLUP);
  
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  /*if(digitalRead(ConfigWiFi_Pin) == LOW) // Press button
  {
    //reset saved settings
    wifiManager.resetSettings(); // go to ip 192.168.4.1 to config
  }*/
  wifiManager.autoConnect(ESP_AP_NAME); 
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(250);
     Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
  //Firebase.set(id + "/IO1/status", false);
  //Firebase.set(id + "/IO2/status", false);
  //Firebase.set(id + "/IO3/status", false);
  // Do something
}

void loop() {
  // Do something

  boolean sIO1 = Firebase.getBool(id + "/IO1/status");
  if (Firebase.failed()) {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());  
    return;
  }else{
    if(sIO1 == true){
      digitalWrite(IO1,HIGH);
      Serial.println("IO1 = ON");
    }else if(sIO1 == false){
      digitalWrite(IO1,LOW);
      Serial.println("IO1 = OFF");
    }
  }
  boolean sIO2 = Firebase.getBool(id + "/IO2/status");
  if (Firebase.failed()) {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());  
    return;
  }else{
    if(sIO2 == true){
      digitalWrite(IO2,HIGH);
      Serial.println("IO2 = ON");
    }else if(sIO2 == false){
      digitalWrite(IO2,LOW);
      Serial.println("IO2 = OFF");
    }
  }
  boolean sIO3 = Firebase.getBool(id + "/IO3/status");
  if (Firebase.failed()) {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());  
    return;
  }else{
    if(sIO3 == true){
      digitalWrite(IO3,HIGH);
      Serial.println("IO3 = ON");
    }else if(sIO3 == false){
      digitalWrite(IO3,LOW);
      Serial.println("IO3 = OFF");
    }
  }
  delay(250);
}
