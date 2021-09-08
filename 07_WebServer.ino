//********************************************************************************************
// Webserver Handling
//********************************************************************************************

//********************************************************************************************
// Configuration
//********************************************************************************************
uint8_t WEBSEWRVER_PORT =  200;
char* WEBSERVER_USERNAME  = "Admin";
char* WEBSERVER_PASSWORD  = "Admin";

//********************************************************************************************
// Variables
//********************************************************************************************
ESP8266WebServer server(WEBSEWRVER_PORT);


//********************************************************************************************
// Methods
//********************************************************************************************

void InitWebServer()
{   
  if (ConfigMode)
  {
    WEBSERVER_USERNAME ="Admin";
    WEBSERVER_PASSWORD="Admin";
  }
  Serial.printf("[InitWebserver] Configuring WebServer ");
  Serial.printf("Username = %s ",(String)WEBSERVER_USERNAME);
  Serial.printf("Password= %s ",(String)WEBSERVER_PASSWORD);
  Serial.printf("Port= %s ",(String)WEBSEWRVER_PORT);
  Serial.println("");
  
  MDNS.begin("ThermoSmartSensor");

   server.on("/", []()
   {
    server.send(200, "text/html", "Welcome to ThermoSmart website");
   });

   server.on("/info", []()
   {
      String stat;
      stat.concat("Wifi: ");
      stat.concat(WifiConnected?"Connected ":"Disconnected ");
      stat.concat("Config Mode: ");
      stat.concat(ConfigMode?"Active ":"Not Active ");

      server.send(200,"text/html",stat);
   });

    server.on("/config/set", HTTP_POST, []()
    {
      if (!server.authenticate(WEBSERVER_USERNAME,WEBSERVER_PASSWORD))
      return server.requestAuthentication();

      DynamicJsonDocument doc(MAX_EEPROM_SIZE);
      deserializeJson(doc, server.arg("plain"));

      Serial.println(server.arg("plain"));

      WIFI_FIXED_IP=doc["WIFI_FIXED_IP"];       
      WIFI_IP= (String)doc["WIFI_IP"];
      WIFI_SUBNET= (String)doc["WIFI_SUBNET"];
      WIFI_GATEWAY= (String)doc["WIFI_GATEWAY"];   
      WIFI_DNS1= (String)doc["WIFI_DNS1"];  
      WIFI_DNS2= (String)doc["WIFI_DNS2"];  
      WIFI_SSID=(String)doc["WIFI_SSID"];       
      WIFI_PASSWORD= (String)doc["WIFI_PASSWORD"];


      SaveEEPROMRequest =true;

    server.send ( 200, "text/json", "{success:true}" );
    });

  server.begin();
}

void ExecuteWebServer()
{
  server.handleClient();
  MDNS.update();
}


char* AsCharArray(String str)
{
    if(str.length()!=0)
    {
        char *p = const_cast<char*>(str.c_str());
        return p;
    }
}
