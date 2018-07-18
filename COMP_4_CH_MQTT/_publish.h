#include <MqttConnector.h>

extern int relayPinState;
extern MqttConnector* mqtt;
extern int relayPin;
extern char myName[];
extern int CH1 ;
extern int CH2 ;
extern int CH3 ;
extern int CH4 ;
extern DHT dht;
int CH11;
int CH12;
int CH13;
int CH14;
int h;
int t;
int f;
extern Adafruit_SSD1306 OLED;

static void readSensor(); 

extern String DEVICE_NAME;
extern int PUBLISH_EVERY;

void register_publish_hooks() {
  strcpy(myName, DEVICE_NAME.c_str());
  mqtt->on_prepare_data_once([&](void) {
    Serial.println("initializing sensor...");
  });

  mqtt->on_before_prepare_data([&](void) {
    readSensor();
  });

  mqtt->on_prepare_data([&](JsonObject *root) {
    JsonObject& data = (*root)["d"];
    JsonObject& info = (*root)["info"];
    data["myName"] = myName;
    data["millis"] = millis();
    data["relayState"] = relayPinState;
    data["CH1 ="] = CH11;
    data["CH2 ="] = CH12;
    data["CH3 ="] = CH13;
    data["CH4 ="] = CH14;
    data["Temp"] = t;
    data["Humi"] = h;
    data["updateInterval"] = PUBLISH_EVERY;
  }, PUBLISH_EVERY);
  mqtt->on_after_prepare_data([&](JsonObject * root) {
    /**************
      JsonObject& data = (*root)["d"];
      data.remove("version");
      data.remove("subscription");
    **************/
  });
}

static void readSensor() {
  Serial.println("Perform reading sensor...");
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  CH11 = digitalRead(CH1);
  CH12 = digitalRead(CH2);
  CH13 = digitalRead(CH3);
  CH14 = digitalRead(CH4);

   if (h>100 || t>100 || f>200) {
    
    Serial.println("Failed to read from DHT sensor!");
    Serial.println(h);
  OLED.clearDisplay();
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.println("CH1");
  OLED.setTextSize(2);
  OLED.println("CH2");
  OLED.setTextSize(2);
  OLED.println("CH3");
  OLED.setTextSize(2);
  OLED.println("CH4");

  OLED.setCursor(70, 0);
  OLED.setTextSize(2);
  OLED.println("Temp");

  OLED.setCursor(70, 32);
  OLED.setTextSize(2);
  OLED.println("Humi");

  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(50, 0);
  OLED.setTextSize(2);
  OLED.println(CH11);
  OLED.setCursor(50, 16);
  OLED.setTextSize(2);
  OLED.println(CH12);
  OLED.setCursor(50, 32);
  OLED.setTextSize(2);
  OLED.println(CH13);
  OLED.setCursor(50, 48);
  OLED.setTextSize(2);
  OLED.println(CH14);

  OLED.setCursor(80, 16);
  OLED.setTextSize(1);
  OLED.println("off");

  OLED.setCursor(80, 48);
  OLED.setTextSize(1);
  OLED.println("off");

  
  OLED.display();
  delay(1000);

    return;
    }
  Serial.println(h);
 // Serial.println("  ");
  //Serial.print("CH1 = ");
  //Serial.println(CH11);
 // Serial.print("CH2 = ");
 // Serial.println(CH12);
 // Serial.print("CH3 = ");
 // Serial.println(CH13);
 // Serial.print("CH4 = ");
  //Serial.println(CH14);

  OLED.clearDisplay();
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.println("CH1");
  OLED.setTextSize(2);
  OLED.println("CH2");
  OLED.setTextSize(2);
  OLED.println("CH3");
  OLED.setTextSize(2);
  OLED.println("CH4");

  OLED.setCursor(70, 0);
  OLED.setTextSize(2);
  OLED.println("Temp");

  OLED.setCursor(70, 32);
  OLED.setTextSize(2);
  OLED.println("Humi");

  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(50, 0);
  OLED.setTextSize(2);
  OLED.println(CH11);
  OLED.setCursor(50, 16);
  OLED.setTextSize(2);
  OLED.println(CH12);
  OLED.setCursor(50, 32);
  OLED.setTextSize(2);
  OLED.println(CH13);
  OLED.setCursor(50, 48);
  OLED.setTextSize(2);
  OLED.println(CH14);


  
  OLED.setCursor(80, 16);
  OLED.setTextSize(1);
  OLED.println(t);
  OLED.setCursor(100, 16);
  OLED.print("*C");

  
  OLED.setCursor(80, 48);
  OLED.setTextSize(1);
  OLED.println(h);
  OLED.setCursor(100, 48);
  OLED.print("%\t");
  
  OLED.display();
  delay(1000);










  
}
