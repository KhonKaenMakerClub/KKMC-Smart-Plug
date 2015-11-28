//=================================//
//        KKMC Smart Plug          //
// Copyright Khon Kaen Maker Club  //
// By Comdet Phaudphut             // 
//=================================//

//---- wifi connector by CMMC
//https://github.com/cmmakerclub/WiFiConnector/
#include <ESP8266WiFi.h>
#include <WiFiConnector.h>

#define WIFI_SSID        ""
#define WIFI_PASSPHARSE  ""

WiFiConnector wifi;
//---- Blynk
#include <SimpleTimer.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
char auth[] = "......................."; //<<<<<<< Blynk auth here
SimpleTimer timer;
//================================//
void init_wifi()
{  
  wifi = WiFiConnector(WIFI_SSID, WIFI_PASSPHARSE);
  Serial.print("CONNECTING TO ");
  Serial.println(wifi.SSID() + ", " + wifi.psk());
  
  wifi.on_connecting([&](const void* message)
  {
    char buffer[70];
    sprintf(buffer, "[%d] connecting -> ", wifi.counter);
    Serial.print(buffer);
    Serial.println((char*) message);
    delay(500);
  });
  wifi.on_connected([&](const void* message)
  {    
    Serial.print("WIFI CONNECTED => ");
    Serial.println(WiFi.localIP());
    ///------------------//
    Blynk.begin(auth);    
    //-------------------//
  });  
  Serial.println("WIFI Connecting");
  wifi.connect();
}
void init_serial()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("ESP-Stack");
}
void init_timer()
{
  timer.setInterval(500L, processWifi);
}
//================================//
void processWifi()
{
  wifi.loop();
}
//================================//
void setup() {
  init_serial();
  init_wifi();
  init_timer();
}

void loop() {
  Blynk.run();
  timer.run();
}
