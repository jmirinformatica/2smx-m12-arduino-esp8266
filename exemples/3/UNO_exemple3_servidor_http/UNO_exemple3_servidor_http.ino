#include "ArduinoESPAT.h"

ESPAT espat(2, 3, "SSID", "password"); 
String ip;

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

  ip = espat.clientIP();
  Serial.println("-----------------------------------");
  Serial.println("IP: " + ip);
  Serial.println("-----------------------------------");
  
  //led que encendrem
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Setup finished");
}

void on_callback() {
  Serial.println("LED ON!");
  digitalWrite(LED_BUILTIN, HIGH);
}

void off_callback() {
  Serial.println("LED OFF!");
  digitalWrite(LED_BUILTIN, LOW);
}

void loop(){

  espat.setGetRecieveEvents("/on", "ON OK!", on_callback);
  espat.setGetRecieveEvents("/off", "OFF OK!", off_callback);
  

  Serial.println("Per encendre el led, ves a http://" + ip + "/on");
  Serial.println("Per apagar el led, ves a http://" + ip + "/off");

  //bucle infinit
  espat.openServer(80);
}

