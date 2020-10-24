/*  ETHERNET SHIELD / JSON */
#include <Ethernet.h>
#include <SPI.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include "RestClient.h"
/*-------------------------*/

/*  PULSO CARDIACO  */
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
/*--------------------------------*/

/*    OXIMETRÍA    */
#include <Arduino.h>
#include <math.h>
#include <Wire.h>
#include "MAX30100.h"
/*------------------*/

/*  TEMPERATURA CORPORAL  */
#include <OneWire.h>
#include <DallasTemperature.h>
/*--------------------------*/

/*Ip y puerto de aplicación*/
#define IP "192.168.1.118"
#define PORT 80
/*-------------------------*/

/*  TEMPERATURA CORPORAL  ->  PINES / JSON  */
const int pinDatosDQ = 24;
String jsonTemperatura = "";

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature temperaturaCorporal(&oneWireObjeto);
/*--------------------------------------------------*/

/*  OXIMETRÍA   ->    PINES / JSON  */
String jsonSaturacion = "";
MAX30100* pulseOxymeter;
/*----------------------------------*/

/*  PULSO CARDIACO   ->    PINES / JSON */
PulseSensorPlayground pulseSensor;

String jsonPulsoCardiaco = "";
const int PulseWire = 0;
const int LED = 4;
int Threshold = 550;
/*--------------------------------------*/

RestClient client = RestClient(IP, PORT);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//byte ip[] = { 192, 168, 0, 102 };
byte gateway[] = { 192, 168, 1, 100 };
byte subnet[] = { 255, 255, 255, 0 };

void setup(){
  Serial.begin(115200);

  //Ethernet.begin(mac, ip, gateway, subnet);

  Ethernet.begin(mac, gateway, subnet);

  client.dhcp();

  Serial.print("IP Ethernet Shield: ");
  Serial.println(Ethernet.localIP());

  /*  TEMPERATURA CORPORAL  */
  temperaturaCorporal.begin();
  Serial.println("Sensor Temperatura DSB18D20      --->    [OK]");
  /*------------------------------------------------------------*/

  /*  OXIMETRÍA */
  Wire.begin();
  //pulseOxymeter = new MAX30100( DEFAULT_OPERATING_MODE, DEFAULT_SAMPLING_RATE, DEFAULT_LED_PULSE_WIDTH, DEFAULT_IR_LED_CURRENT, true, true );
  pulseOxymeter = new MAX30100();
  pinMode(28, OUTPUT);
  Serial.println("Sensor Oximetría MAX30100        --->    [OK]");
  /*------------------------------------------------------------*/

  /*  PULSO CARDIACO  */
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()){
    Serial.println("Sensor Pulso Cardíaco SEN_0386   --->  [OK]");
  }
  /*------------------------------------------------------------*/
}

void loop(){

pulseoxymeter_t result = pulseOxymeter->update();

  if(result.pulseDetected == true){
    Serial.println("");
    Serial.print("SpO2: ");
    Serial.print(result.SaO2);
    Serial.print(" %");
    Serial.println("");

    client.setHeader("Content-Type: application/json");

    StaticJsonBuffer<200> jsonBuffer;
    char json[256];  
    JsonObject& root2 = jsonBuffer.createObject();
    root2["saturacion"] = result.SaO2;
    root2.printTo(json, sizeof(json));
    Serial.println(json);
    
    int statusCode = client.post("http://192.168.1.118/api/oximetria", json, &jsonSaturacion);
    
    Serial.println("API route [%Saturación Oxígeno] -> http://192.168.1.118/api/oximetria");
    Serial.println("");
    Serial.print("Server response: ");
    Serial.print("[");
    Serial.print(statusCode);
    Serial.print("[");
    Serial.println("");
    Serial.print("MongoDB response -> " +jsonSaturacion);
    Serial.println("");
  }

  jsonSaturacion = "";

  delay(10);

  digitalWrite(28,!digitalRead(28));

int lpm = pulseSensor.getBeatsPerMinute();

  if (pulseSensor.sawStartOfBeat()){
    Serial.println("");
    Serial.println("♥  Se a detectado una pulsación ♥ ");
    Serial.print("LPM: ");
    Serial.println(lpm);
    Serial.println("");

    client.setHeader("Content-Type: application/json");

    StaticJsonBuffer<200> jsonBuffer;
    char json[256];
    JsonObject& root = jsonBuffer.createObject();
    root["lpm"] = lpm;
    Serial.println("Estructura JSON:");
    root.printTo(json, sizeof(json));
    Serial.println("");
    Serial.println(json);

    int statusCode2 = client.post("http://192.168.1.118/api/pulso-cardiaco", json, &jsonPulsoCardiaco);

    Serial.println("API route [Pulso Cardiaco] -> http://192.168.1.118/api/pulso-cardiaco");
    Serial.println("");
    Serial.print("Server response: ");
    Serial.print("[");
    Serial.print(statusCode2);
    Serial.print("[");
    Serial.println("");
    Serial.print("MongoDB response -> " +jsonPulsoCardiaco);
    Serial.println("");

    jsonPulsoCardiaco = "";
  }
  
  delay(20);

temperaturaCorporal.requestTemperatures();

  int temp = temperaturaCorporal.getTempCByIndex(0);

  if(temp >= 35){
    Serial.println("");
    Serial.print("☀ Temperatura: ");
    Serial.print(temp);
    Serial.println(" °C ☀");
    Serial.println("");
  }
  else{
    Serial.println("");
    Serial.print("☃  Temperatura: ");
    Serial.print(temp);
    Serial.println(" °C  ☃");
    Serial.println("");
  }
  
  delay(20);

  client.setHeader("Content-Type: application/json");

  StaticJsonBuffer<200> jsonBuffer3;
  char json3[256];  
  JsonObject& root3 = jsonBuffer3.createObject();
  root3["temperatura"] = temp;
  root3.printTo(json3, sizeof(json3));
  Serial.println("");
  Serial.println(json3);

  int statusCode3 = client.post("http://192.168.1.118/api/temperatura-corporal", json3, &jsonTemperatura);
  
  Serial.println("API route [Temperatura Corporal] -> http://192.168.1.118/api/temperatura-corporal");
  Serial.println("");
  Serial.print("Server response: ");
  Serial.print("[");
  Serial.print(statusCode3);
  Serial.print("[");
  Serial.println("");
  Serial.print("MongoDB response -> " +jsonTemperatura);
  Serial.println("");

  jsonTemperatura = "";
}
