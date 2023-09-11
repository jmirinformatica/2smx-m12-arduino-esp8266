#include "ArduinoESPAT.h"

#define SERVER_IP "192.168.86.32"
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
  
  //led que encendrem
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Setup finished");
}

void loop(){
  String response = espat.get(SERVER_IP, "/led.php", 8888);

  if (response == "[ON]") {
    Serial.println("LED ON because response from server was: " + response);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    Serial.println("LED OFF because response from server was: " + response);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

