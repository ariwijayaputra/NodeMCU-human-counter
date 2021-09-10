#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <elapsedMillis.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
elapsedMillis interval, timeout;

#include "MQTTConnector.h"
#include "Credentials.h"


#define WIFI_TIMEOUT 1000
#define LOOP_TIMEOUT 10000

const int pirSensor = 14;
const int led = 16;
int in, out, sensorValue, current, last;
int jumlahOrang= 0;
bool timer;
void WiFiBegin(const char* ssid, const char* pass)
{
  WiFi.begin(ssid, pass);
  Serial.printf("Waiting for AP connection ...\n");
  lcd.setCursor(0, 0);
  lcd.print("Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("Connection...");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(WIFI_TIMEOUT);
    Serial.printf(".");
  }
  IPAddress ip = WiFi.localIP();
  Serial.printf("\nConnected to AP. IP : %d.%d.%d.%d\n",
                ip[0], ip[1], ip[2], ip[3]);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected");
  delay(500);
  lcd.clear();
}

void setup()
{
  Serial.begin(9600);
  lcdsetup();
  Serial.setDebugOutput(true);
  pinMode(pirSensor, INPUT);
  WiFiBegin(STA_SSID, STA_PASS);
  MQTTBegin();

  Serial.println("Preparing sensor...");
  lcd.setCursor(0, 0);
  lcd.print("Preparing sensor");
  delay(4000);
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  delay(500);
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Ready");

}

void loop()
{
  MQTTLoop();
  //  if (MQTTPublish(TOPIC, "test maqiatto!"))
  //  {
  //    Serial.printf("MQTTPublish was succeeded.\n");
  //  }
  in = int(getIndoor());
  out = int(getOutdoor());
  if ((in == 1 || out == 1) && timer == 0) {
    timeout = 0;
    timer = 1;
  }
  if (timeout > 3000) {
    writeIndoor(0);
    writeOutdoor(0);
    timer = 0;
  }
  current = getPayload();
  if (in == 1 && out == 1) {
    if (last == 2 && current == 1) {
      Serial.println("==== MASUK ======");
      MQTTPublish(STATUS, "1");
      jumlahOrang++;
      lcd.clear();
    }
    else if (last == 1 && current == 2) {
      Serial.println("==== KELUAR ======");
      MQTTPublish(STATUS, "2");
      jumlahOrang--;
      lcd.clear();
    }
    
    lcd.setCursor(0, 1);
    lcd.print("Jumlah = ");
    char jumlah[5];
    sprintf(jumlah, "%d", jumlahOrang);
    lcd.print(jumlahOrang);
    MQTTPublish(JUMLAH, jumlah);
    writeIndoor(0);
    writeOutdoor(0);
    timer = 0;
  }
  last = current;



  if (interval >= 500) {
    pir();
    interval = 0;

    Serial.println(getPayload());
  }

}
