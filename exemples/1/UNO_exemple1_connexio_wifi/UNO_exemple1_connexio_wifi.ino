#include "ArduinoESPAT.h"

ESPAT espat(2, 3, "SSID", "password"); 

void setup(){
  Serial.begin(9600);

  if(espat.begin()){
    Serial.println("Initialize Ok");
  }else{
    Serial.println("Initialize Fail");
  }

  if(espat.changeMode(1)){ //station mode
    Serial.println("Mode OK");
  }else{
    Serial.println("Mode not OK");
  }

  if(espat.tryConnectAP()){
    Serial.println("Connected");
  }else{
    Serial.println("Connect Failed");
  }

  String ip = espat.clientIP();
  Serial.println("-----------------------------------");
  Serial.println("IP: " + ip);
  Serial.println("-----------------------------------");
  
  String response = espat.get("captive.apple.com", "/", 80, false);
  Serial.println("+++++++++++++++++++++++++++++++++++");
  Serial.println(response);
  Serial.println("+++++++++++++++++++++++++++++++++++");

  Serial.println("Setup finished");
}

void loop(){
}
