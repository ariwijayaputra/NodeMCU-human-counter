#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <elapsedMillis.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Wire.h>
#include <DS3231.h>

RTClib RTC;
DS3231 jam;
LiquidCrystal_I2C lcd(0x27, 16, 2);
elapsedMillis interval, timeout, timerPir;


#include "MQTTConnector.h"
#include "Credentials.h"


#define WIFI_TIMEOUT 1000
#define LOOP_TIMEOUT 10000
const int pirSensor2 = 12;
const int pirSensor = 13;
const int resetJumlah = 14;
const int led = 16;
int sensorValue, sensorValue2, current, last;
bool century = false;
bool  in, out, timer, h12Flag, pmFlag;

uint addr = 0;

// fake data
struct {
  int jumlah = 0;
} data;

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
  delay(1000);
  lcd.clear();
}

void setup()
{
  Wire.begin(); // Start the I2C
  Serial.begin(9600);
  EEPROM.begin(512);
  lcdsetup();
  pinMode(pirSensor, INPUT);
  pinMode(resetJumlah, INPUT_PULLUP);
  WiFiBegin(STA_SSID, STA_PASS);//mengkoneksi wifi
  MQTTBegin();//memulai koneksi MQTT
  Serial.println("Preparing sensor...");
  lcd.setCursor(0, 0);
  lcd.print("Preparing sensor");
  delay(4000);
  lcd.noBacklight();
  delay(300);
  lcd.backlight();
  delay(300);
  lcd.noBacklight();
  delay(300);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Ready");
  EEPROM.get(addr, data);
  char jumlah[5];
  sprintf(jumlah, "%d", data.jumlah);
  MQTTPublish(JUMLAH, jumlah);
  jam.setClockMode(false);
}

void loop()
{
  EEPROM.get(addr, data);//mengambil data dari eeprom dan menyimpannya ke struct data
  if (digitalRead(resetJumlah) == LOW) {
    data.jumlah = 0;
    EEPROM.put(addr, data);
    EEPROM.commit();
  }

  MQTTLoop();
  
  if (timerPir > 500) { // mengambil data sensor setiap 0.5 second
    pir();
    delay(500);
    pir2();
    timerPir = 0; // reset timer untuk pengambilan data
  }
  if ((in == 1 || out == 1) && timer == 0) {//jika salah satu sensor mendeteksi gerakan dan timer belum dinyalakan
    timeout = 0; // reset timeout
    timer = 1; // menyalakan timer
  }
  if (timeout > 3000) {//jika nilai timeout (auto increment) lebih dari 4000,
    in = 0; //clear status, sensor tidak mendeteksi gerakan.
    out = 0;
    timer = 0;// matikan timer
    Serial.println("timeout");
  }
  if (in == 1 && out == 1) {
    if (last == 2 && current == 1) {
      Serial.println("==== MASUK ======");
      data.jumlah++;
      
      lcd.clear();
    }
    else if (last == 1 && current == 2) {
      Serial.println("==== KELUAR ======");
      data.jumlah--;
      if (data.jumlah < 0)
      {
        data.jumlah = 0;
      }
      lcd.clear();
      
    }
    delay(500);
    EEPROM.put(addr, data);//replace data pada byte array cache, belum meyimpan ke hardware
    EEPROM.commit();// menyimpan data pada byte array cache ke hardware
    in = 0;
    out = 0;
    timer = 0;
  }
  last = current;
  if (interval >= 1000) {//proses update data jam dan pengiriman data
    interval = 0;
    lcd.clear();
    DateTime now = RTC.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.setCursor(6, 0);
    lcd.print(now.hour(), DEC);
    lcd.print(":");
    lcd.print(now.minute(), DEC);
    lcd.print(":");
    lcd.print(now.second(), DEC);
    lcd.setCursor(0, 1);
    lcd.print("Jumlah = ");
    lcd.print(data.jumlah);

    char tanggal[10] = "";
    sprintf(tanggal, "%d/%d/%d", jam.getDate(), jam.getMonth(century), jam.getYear());
    MQTTPublish(TANGGAL, tanggal);
    
    char waktu[10] = "";
    sprintf(waktu, "%d:%d:%d", jam.getHour(h12Flag, pmFlag), jam.getMinute(), jam.getSecond());
    MQTTPublish(WAKTU, waktu);
    
    char jumlah[5];
    sprintf(jumlah, "%d", data.jumlah);
    MQTTPublish(JUMLAH, jumlah);
    
    for (int i = 0; i < 10; i++) {
      Serial.print(tanggal[i]);
    }
    Serial.println();
  }
}
