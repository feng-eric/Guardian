#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_CCS811.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VEML6070.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include <SparkFunBME280.h>
#include <SparkFunCCS811.h>
#include <SPI.h>
#include <WifiLocation.h>
#include <Wire.h>

#include "Credentials.h"

//#define TEST
#define DHT_TEST
//#define ULTRASONIC_TEST
#define CCS811_TEST
#define BME280_TEST
#define VEML6070_TEST

// DHT11
#define DHT_PIN D3
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

long duration;
long distance;

// CSS811 CO2 and TVOC
#define CSS811_ADDR 0x5B
CCS811 ccs811(CSS811_ADDR);

// BME280 Pressue Sensor
#define SEALEVELPRESSURE_HPA 1013.25
Adafruit_BME280 bme;
unsigned long delayTime;

// VEML6070
Adafruit_VEML6070 uv = Adafruit_VEML6070();

void ConnectToWiFi()
{
    delay(100);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.print(SSID);
    /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
    would try to act as both a client and an access-point and could cause
    network-issues with your other WiFi-devices on your WiFi-network. */
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    Serial.println("Begin connecting to wifi");
    //start connecting to WiFi
    WiFi.begin(SSID, PASSWORD);
    //while client is not connected to WiFi keep loading
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("WiFi connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("");
}

void setup() 
{
  Serial.begin(115200);
  Wire.begin();

  // ESP8266
  ConnectToWiFi();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // DHT
  dht.begin();
  pinMode(D0, OUTPUT);

  //CCS811
  ccs811.begin();

  // BME280
  while(!Serial);    // time to get serial running
    unsigned status;
  
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1);
    }
    delayTime = 1000;
    Serial.println();

    // VEML6070
    uv.begin(VEML6070_1_T);
}

void loop() 
{
#ifdef TEST
  // === Push temperature value to Firebase ===
  String tempValueID = Firebase.pushInt("dht11/temperature", random(20, 30));
  Serial.print("[INFO] temperature: ");
  Serial.println(random(0, 80));
  if (Firebase.failed()) 
  {
      Serial.print("[ERROR] pushing /dht11/temperature failed:");
      Serial.println(Firebase.error());
      return;
  }
  Serial.print("[INFO] pushed: /dht11/temperature \tkey: ");
  Serial.println(tempValueID);
  
  // === Push humidity value to Firebase ===
  String humValueID = Firebase.pushInt("dht11/humidity", random(0, 80));
  Serial.print("[INFO] humidity: ");
  Serial.println(random(0, 80));
  if (Firebase.failed())
  {
      Serial.print("[ERROR] pushing /dht11/humidity failed:");
      Serial.println(Firebase.error());
      return;
  }
  Serial.print("[INFO] pushed: /dht11/humidity    \tkey: ");
  Serial.println(humValueID);
  Serial.println();

#endif
#ifdef DHT_TEST

  // DHT11 Temperature and Humidity Sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("[INFO] Current Humidity = ");
  Serial.print(h);
  Serial.println(" %");
  Serial.print("[INFO] Current Temperature = ");
  Serial.print(t);
  Serial.println(" °C");
  
  // Eliminate abnormal values
  if ((t >= -15 && t <= 80) && (h >= 0 && h <= 100)) 
  {
    // === Push temperature value to Firebase ===
    String tempValueID = Firebase.pushFloat("DHT11/temperature", t);
    if (Firebase.failed()) 
    {
        Serial.print("[ERROR] pushing /DHT11/temperature failed:");
        Serial.println(Firebase.error());
        return;
    }

    Serial.print("[INFO] pushed: /DHT11/temperature \tkey: ");
    Serial.println(tempValueID);

    // === Push humidity value to Firebase ===
    String humValueID = Firebase.pushFloat("DHT11/humidity", h);
    if (Firebase.failed()) 
    {
        Serial.print("[ERROR] pushing /DHT11/humidity failed:");
        Serial.println(Firebase.error());
        return;
    }

    Serial.print("[INFO] pushed: /DHT11/humidity    \tkey: ");
    Serial.println(humValueID);
    Serial.println();
  } 
  else 
  {
      Serial.println("[ERROR] Wrong values!");
  }
#endif
#ifdef ULTRASONIC_TEST
  // Ultrasonic Range Finder 

  // clear the trigger pin
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);  

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);

  distance = duration * 0.034/2;
  Serial.print("[INFO] Distance = ");
  Serial.print(distance);
  
  #endif

#ifdef CCS811_TEST
  if (ccs811.dataAvailable())
  {
    ccs811.readAlgorithmResults();
    int tempCO2 = ccs811.getCO2();
    int tempTVOC = ccs811.getTVOC();
    Serial.print("[INFO] CO2: ");
    Serial.print(tempCO2);
    Serial.println();
    Serial.print("[INFO] TVOC: ");
    Serial.print(tempTVOC);
    Serial.println();

    // Push CO2 reading to Firebase
    String CO2ValueID = Firebase.pushFloat("CCS811/CO2", tempCO2);
    if (Firebase.failed()) 
    {
        Serial.print("[ERROR] pushing /CCS811/CO2 failed:");
        Serial.println(Firebase.error());
        return;
    }
    Serial.print("[INFO] pushed: /CCS811/CO2 \tkey: ");
    Serial.println(CO2ValueID);

    // Push TVOC reading to Firebase
    String TVOCValueID = Firebase.pushFloat("CCS811/TVOC", tempTVOC);
    if (Firebase.failed()) 
    {
        Serial.print("[ERROR] pushing /CCS811/TVOC failed:");
        Serial.println(Firebase.error());
        return;
    }
    Serial.print("[INFO] pushed: /CCS811/TVOC \tkey: ");
    Serial.println(TVOCValueID);
  }
  else if (ccs811.checkForStatusError())
  {
    Serial.print("[ERROR] Cannot print values");
    Serial.println();
  }
#endif
#ifdef BME280_TEST
  Serial.print("[INFO] Pressure: ");
  float tempPressure = bme.readPressure() / 100.0F;
	Serial.print(tempPressure);
	Serial.println("hPa");

	Serial.print("[INFO] Approx. Altitude: ");
  float tempAltitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
	Serial.print(tempAltitude);
	Serial.println("m");

  // Push pressure reading to Firebase
  String PressureValueID = Firebase.pushFloat("BME280/Pressure", tempPressure);
  if (Firebase.failed()) 
  {
      Serial.print("[ERROR] pushing /BME280/Pressure failed:");
      Serial.println(Firebase.error());
      return;
  }
  Serial.print("[INFO] pushed: /BME280/Pressure \tkey: ");
  Serial.println(PressureValueID);

  // Push Altitude reading to Firebase
  String AltitudeValueID = Firebase.pushFloat("BME280/Altitude", tempAltitude);
  if (Firebase.failed()) 
  {
      Serial.print("[ERROR] pushing /BME280/Altitude failed:");
      Serial.println(Firebase.error());
      return;
  }
  Serial.print("[INFO] pushed: /BME280/Altitude \tkey: ");
  Serial.println(AltitudeValueID);
#endif
#ifdef VEML6070_TEST
  Serial.print("[INFO] UV light level: ");
  int UV = uv.readUV();
  Serial.print(UV);

  // Push UV index reading to Firebase
  String UVValueID = Firebase.pushFloat("VEML6070/UV", UV);
  if (Firebase.failed()) 
  {
      Serial.print("[ERROR] pushing /VEML6070/UV failed:");
      Serial.println(Firebase.error());
      return;
  }
  Serial.println();
  Serial.print("[INFO] pushed: /VEML6070/UV \tkey: ");
  Serial.println(UVValueID);
#endif

  delay(500);

}