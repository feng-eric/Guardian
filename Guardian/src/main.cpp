#include <Arduino.h>
//#include <Adafruit_VEML6070.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

#include "Credentials.h"

#define TEST
//#define DHT_TEST
//#define ULTRASONIC_TEST

// DHT11 Variables
#define DHT_PIN D2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);


// Ultrasonic Range Finder
//#define TRIG_PIN D4
//#define ECHO_PIN D3

const int trig_pin = 0;
const int echo_pin = 2;

long duration;
long distance;

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

  // ESP8266
  ConnectToWiFi();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //DHT
  dht.begin();
  pinMode(D0, OUTPUT);

  
  // Ultrasonic Range Finder
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() 
{
#ifdef TEST
  // === Push temperature value to Firebase ===
  String tempValueID = Firebase.pushInt("dht11/temperature", random(0, 80));
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
    String tempValueID = Firebase.pushFloat("dht11/temperature", t);
    if (Firebase.failed()) 
    {
        Serial.print("[ERROR] pushing /dht11/temperature failed:");
        Serial.println(Firebase.error());
        return;
    }

    Serial.print("[INFO] pushed: /dht11/temperature \tkey: ");
    Serial.println(tempValueID);

    // === Push humidity value to Firebase ===
    String humValueID = Firebase.pushFloat("dht11/humidity", h);
    if (Firebase.failed()) 
    {
        Serial.print("[ERROR] pushing /dht11/humidity failed:");
        Serial.println(Firebase.error());
        return;
    }

    Serial.print("[INFO] pushed: /dht11/humidity    \tkey: ");
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

  delay(1000);

}