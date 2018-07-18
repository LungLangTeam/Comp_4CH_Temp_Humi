#include "DHT.h"
#define DHTPIN D2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(-1);

int CH1 = D5;
int CH2 = D6;
int CH3 = D7;
int CH4 = D1;
void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  Wire.begin(D3,D4);
  

  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
}

void loop() {

  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int f = dht.readTemperature(true);
   float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  int CH11 = digitalRead(CH1);
  int CH12 = digitalRead(CH2);
  int CH13 = digitalRead(CH3);
  int CH14 = digitalRead(CH4);

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
