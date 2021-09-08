//*******************************************************************************************
//                            THERMOSMART
//   
// Rev List:
// R1.0: First release. Project structure
// 
//
//
//*******************************************************************************************



//********************************************************************************************
// Global Variables
//********************************************************************************************
#define FIRMWARE_VERSION   "R1.0"
#define SERIAL_BAUDRATE 9600
#define TAKEOFF_TIME  6000
#define MAX_EEPROM_SIZE  2048

//********************************************************************************************
// Libraries
//********************************************************************************************

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <StreamUtils.h>

//********************************************************************************************
// Globally shared variables
//********************************************************************************************
long LastCommandMillis = millis();
bool SaveEEPROMRequest =false;
bool ConfigMode =false;
bool WifiConnected = false;
