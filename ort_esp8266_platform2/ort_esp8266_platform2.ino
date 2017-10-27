// import libraries for esp8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "FS.h"
#include <Ticker.h>
float temp;






Ticker sample;
Ticker timesample;
// start server


void takeSample(){
  temp = analogRead(A0);
  temp = (temp /1024.0) * 3300 / 10;
  }







 /*option to use static ip*/
//IPAddress ip(192, 168, 1, 150);


// fill in network name
const char* ssid = "nrg";

// fill in network password
const char* password = "aaaaabbbbb";


// start server at port 80
ESP8266WebServer server(80);



void setup(void){
  SPIFFS.begin();
  server.serveStatic("/", SPIFFS, "/index.html");

    server.begin();

  takeSample();

  sample.attach(45, takeSample);
  
  // prepare pins as outputs 
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(16, OUTPUT);
 
  Serial.begin(115200);


  

  // connect to router
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  // print to serial monitor the local IP
  Serial.println(WiFi.localIP());


  // response to post request example: 192.168.1.17/1
  server.on("/1", [](){
    // send response ok/200, blank text
    server.send(200, "text/plain", "");
    //toggle pin number 2
    digitalWrite(2, !digitalRead(2));
  });

  // response to post request example: 192.168.1.17/2
  server.on("/2", [](){
    server.send(200, "text/plain", "");
    digitalWrite(4, !digitalRead(4));
  });

  server.on("/3", [](){
    server.send(200, "text/plain", "");
    digitalWrite(5, !digitalRead(5));
  });

  server.on("/4", [](){
    server.send(200, "text/plain", "");
    digitalWrite(16, !digitalRead(16));
  });

  server.on("/5", [](){
    server.send(200, "text/plain", String(temp));
   // digitalWrite(16, !digitalRead(16));
  });
  
  
  Serial.println("HTTP server started");
}

void loop(void){
 

  // always wait in loop for incoming requests. 
 server.handleClient();
}















