//
// +--------------------------------+
// | Wi-Fi Controlled 4WD Robot Car |
// +--------------------------------+
//
// (c) 2021 Daniel Faria Muniz (a.k.a. doctorxyz)
//
// Based on the following work:
// Guia de montagem da plataforma robótica 4WD (https://blog.eletrogate.com/guia-de-montagem-da-plataforma-robotica-4wd/)
// ESP Motor Shield: controlando motores via WiFi (https://blog.eletrogate.com/esp-motor-shield-controlando-motores-via-wifi/)
// 11 Simple Steps to Make WiFi car Using NodeMCU (https://circuitbest.com/arduino-smartphone-controlled-wifi-car-using-nodemcu-esp8266/)
// Smartphone Controlled Arduino 4WD Robot Car (https://www.hackster.io/andriy-baranov/smartphone-controlled-arduino-4wd-robot-car-14d239)
// Turning 360 degrees a 4WD chassis without any encoder (https://www.codeproject.com/Articles/1255314/Turning-360-degrees-a-4WD-chassis-without-any-enco)
// What is the Difference Between L293D and L298N Motor Driver? (https://robu.in/what-is-the-difference-between-l293d-and-l298n-motor-driver/)
//

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2

char auth[] = "mxW2l5GuKcS_xO5KQJstrjpkl-iEWBNi";
char network[] = "LAFD-2.4";
char password[] = "Lafd310103!";

int minRange = 256;
int maxRange = 767;
int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;


void drive(int x, int y){
  
  // Forward
  if(y >= maxRange && x >= minRange && x <= maxRange){
    digitalWrite(RightMotorDir,HIGH); 
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // Forward and right
  else if(x >= maxRange && y >= maxRange){
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // Forward and left
  else if(x <= minRange && y >= maxRange){
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
  }

  // Neutral
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange){
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
  }

  // Backward
  else if(y <= minRange && x >= minRange && x <= maxRange){
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
   analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  // Backward and right
  else if(y <= minRange && x <= minRange){
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
  }

  // Backward and left
  else if(y <= minRange && x >= maxRange){
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed); 
  }
}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, network, password);
 
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);
  
  // Initial setup (No speed, Forward)
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir,HIGH);
}

void loop(){
   Blynk.run();
}

BLYNK_WRITE(V1){
  int x = param[0].asInt();
  int y = param[1].asInt();
  drive(x,y);
}
