# Guardian
This repository contains all source code and dependencies for Guardian.

Guardian is a novel approach to firefighter safety by utilizing the power of IOT to track environmental vitals and transmitting this data in an easy, readable format to Google Firebase where it is then retrieved and processed in an innovative user interface.

Various sensors such as temperature/humidity sensors, atmospheric sensors, UV, and air quality sensors have been mounted on a helmet and interface with a NodeMCU ESP8266 board running on the Arduino framework. The board connects to a 2.4 GHz WiFi network to send the sensor information over Internet of Things to Google Firebase where it is fetched and piped into a web interfaced based on the web application developed using Vue.js framework. 

The data that is stored in Firebase appears on the user interface where values for each type of data is displayed in real time. Users can choose to display the most recent data or see a collection of past data visualized on a chart. When the threshold exceeds for a certain type of data, the UI will turn red and an alert will appear indicating that the firefighter is in critical conditions.

Link to Devpost: https://devpost.com/software/guardian-2n7q3s
