//********************************************************************************************
// IO Handling
//********************************************************************************************

//********************************************************************************************
// Configuration
//********************************************************************************************
uint8_t IN_MAN_OPEN_PIN =  D8;
uint8_t IN_MAN_DEFAULT_CONFIG =  D5;
uint8_t OUT_GATE_CLOSING =  D7;
uint8_t OUT_LED_CONFIG_PIN =  D6;
uint8_t OUT_LED_CLOUD_OK_PIN =  D0;
uint8_t OUT_LED_WIFI_OK_PIN =  D2;
short BLINK_SPEED =100;
int FIXED_LAMP_TIME_DELAY = 300000;
int BLINK_LAMP_TIME_DELAY = 100000;


//********************************************************************************************
// Variables
//********************************************************************************************

//********************************************************************************************
// Methods
//********************************************************************************************

void InitIO()
{
  Serial.println("[InitIO] Configuring IO");
  pinMode(IN_MAN_OPEN_PIN, INPUT);
  pinMode(OUT_GATE_CLOSING, OUTPUT);
  pinMode(OUT_LED_CONFIG_PIN, OUTPUT);
  pinMode(OUT_LED_WIFI_OK_PIN, OUTPUT);
  pinMode(IN_MAN_DEFAULT_CONFIG, INPUT);

  if (digitalRead(IN_MAN_DEFAULT_CONFIG)==HIGH )
  {
    ConfigMode =true;
  }
  
}

void ExecuteIO()
{
  digitalWrite(OUT_LED_CONFIG_PIN,ConfigMode==true?HIGH:LOW); 
  digitalWrite(OUT_LED_WIFI_OK_PIN,WifiConnected==true?HIGH:(millis() / BLINK_SPEED) % 2);
  
  
}
