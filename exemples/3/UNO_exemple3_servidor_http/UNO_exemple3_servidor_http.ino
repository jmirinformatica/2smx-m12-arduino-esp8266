#include "ArduinoESPAT.h"

ESPAT espat(2, 3, "SSID", "password"); 

String ip;
bool led_on = false;

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

String on_callback() {
  Serial.println("S'ha cridat a on_callback");
  digitalWrite(LED_BUILTIN, HIGH);
  led_on = true;

  return "on";
}

String off_callback() {
  Serial.println("S'ha cridat a off_callback");
  digitalWrite(LED_BUILTIN, LOW);
  led_on = false;

  return "off";
}

String status_callback() {
  Serial.println("S'ha cridat a status_callback");

  if(led_on) {
    return "on";
  } else {
    return "off";
  }
}

String hello_callback(String key, String value) {
  Serial.println("S'ha cridat a hello_callback");
  if (key == "nom") {
    return "Hola " + value;
  } else {
    return "Hola desconegut o desconeguda";
  }
}

void loop(){

  espat.addGetCallback("/on", on_callback);
  espat.addGetCallback("/off", off_callback);
  espat.addGetCallback("/status", status_callback);  
  espat.addGetCallback("/hello", hello_callback);  

  Serial.println("Per encendre el led, ves a http://" + ip + "/on");
  Serial.println("Per apagar el led, ves a http://" + ip + "/off");
  Serial.println("Per comprovar l'estat del led, ves a http://" + ip + "/status");
  Serial.println("Per provar els paràmetres, ves a http://" + ip + "/hello?nom=Alfonso");

  //bucle infinit
  espat.openServer(80);
}
