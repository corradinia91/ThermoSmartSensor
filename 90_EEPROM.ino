//********************************************************************************************
// EEPROM HANDLING
//********************************************************************************************

//********************************************************************************************
// Configuration
//********************************************************************************************

//********************************************************************************************
// Variables
//********************************************************************************************

//********************************************************************************************
// Methods
//********************************************************************************************
void InitEEPROM()
{
   Serial.println("[InitEEPROM] Getting Data");
   EEPROM.begin(MAX_EEPROM_SIZE);
   
   DynamicJsonDocument doc(MAX_EEPROM_SIZE);
   EepromStream eepromStream(0, MAX_EEPROM_SIZE);
   
   deserializeJson(doc, eepromStream);
   serializeJson(doc, Serial);
   Serial.println("");

    WIFI_FIXED_IP=doc["WIFI_FIXED_IP"];       
    WIFI_IP= (String)doc["WIFI_IP"];
    WIFI_SUBNET= (String)doc["WIFI_SUBNET"];
    WIFI_DNS1= (String)doc["WIFI_DNS1"];
    WIFI_DNS2= (String)doc["WIFI_DNS2"];
    WIFI_GATEWAY= (String)doc["WIFI_GATEWAY"];     
    WIFI_SSID=(String)doc["WIFI_SSID"];       
    WIFI_PASSWORD= (String)doc["WIFI_PASSWORD"];

}

void ExecuteEEPROM()
{
  if (SaveEEPROMRequest)
  {
    Serial.println("[ExecuteEEPROM] Save Requested");
    SaveEEPROMRequest=false;

    DynamicJsonDocument doc(MAX_EEPROM_SIZE);

    doc["WIFI_FIXED_IP"] = (WIFI_FIXED_IP);
    doc["WIFI_IP"] = String(WIFI_IP);
    doc["WIFI_SUBNET"] = String(WIFI_SUBNET);
    doc["WIFI_GATEWAY"] = String(WIFI_GATEWAY);
    doc["WIFI_DNS1"] = String(WIFI_DNS1);     
    doc["WIFI_DNS2"] = String(WIFI_DNS2);     
    doc["WIFI_SSID"] = String(WIFI_SSID);
    doc["WIFI_PASSWORD"]= String(WIFI_PASSWORD);


   EepromStream eepromStream(0, MAX_EEPROM_SIZE);
   serializeJson(doc, eepromStream);
   
   EEPROM.commit();

  deserializeJson(doc, eepromStream);
  serializeJson(doc, Serial);
  Serial.println("");
    
  }
}
