// https://github.com/nyampass/ArduinoESPAT-Library

#include "ArduinoESPAT.h"

ESPAT espat("SSID", "password"); 

void setup(){
  Serial.begin(115200);

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

  Serial.println(espat.clientIP());

  Serial.println(espat.get("hogehoge.com", "/", 80));
  Serial.println("Finished");
}

void loop(){
}
