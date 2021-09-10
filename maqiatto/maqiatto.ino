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
}

void loop()
{
  MQTTLoop();
  in = int(getIndoor());
  out = int(getOutdoor());
  if ((in == 1 || out == 1) && timer == 0) {
    /*
    Kondisi untuk mereset timer timeout. timer menyala (timer = 1) jika
    salah satu sensor mendeteksi gerakan dan jika timer dalam keadaan mati.
    variabel timeout dalam hal ini akan terus melakukan increment
    oleh karena itu, timeout harus di reset pada kondisi ini.
    */
    timeout = 0;
    timer = 1;
  }
  if (timeout > 3000) {
    /*
    kondisi untuk mereset nilai sensor dan mematikan timer. 
    dilakukan apabila salah satu sensor telah mendeteksi 
    gerakan namun tidak ada deteksi gerakan dari sensor
    lainnya dalam rentang waktu 3 detik (3000ms).
    Seseorang harus melewati kedua buah sensor dalam rentang
    waktu 3 detik untuk bisa dideteksi telah melewati pintu.
    ubah timeout > 3000 jika ingin menambah/mengurangi waktu tunggu
    sensor.
    */
    writeIndoor(0);
    writeOutdoor(0);
    timer = 0;
  }
  current = getPayload();
  /*
  current adalah variabel untuk menyimpan data sensor mana yang saat ini
  mendeteksi gerakan.
  current = 1 jika indoor yang baru saja mendeteksi gerakan.
  current = 2 jika outdoor yang baru saja mendeteksi gerakan.
  */
  if (in == 1 && out == 1) {
    /*
      jika sensor dalam dan luar mendeteksi gerakan maka nilai in dan
      out adalah 1. kondisi diatas digunakan apabila kedua sensor mendeteksi
      gerakan sebelum 3 detik. jika kondisi ini TRUE maka sensor mendeteksi
      ada seseorang yang telah melewati pintu, namun masih belum diketahui arahnya
      apakah orang tersebut masuk atau keluar.
    */
    if (last == 2 && current == 1) {
      /*
        jika current == 1 (indoor yang saat ini mendeteksi gerakan). 
        dan last == 2 (outdoor yang sebelumnya mendeteksi gerakan)
        maka arah orang tersebut:
        outdoor -> indoor (Masuk)
      */
      Serial.println("==== MASUK ======");
      MQTTPublish(STATUS, "1");
      jumlahOrang++;
      lcd.clear();
    }
    else if (last == 1 && current == 2) {
      /*
        jika current == 2 (outdoor yang saat ini mendeteksi gerakan). 
        dan last == 1 (indoor yang sebelumnya mendeteksi gerakan)
        maka arah orang tersebut:
        indoor -> outdoor (Keluar)
      */
      Serial.println("==== KELUAR ======");
      MQTTPublish(STATUS, "2");
      jumlahOrang--;
      lcd.clear();
    }
    
    lcd.setCursor(0, 1);
    lcd.print("Jumlah = ");
    lcd.print(jumlahOrang);
    
    /*
    inisiasi char jumlah untuk publish jumlahOrang
    ke MQTT karena MQTTPublish hanya menerima type *char
    */
    char jumlah[5];
    sprintf(jumlah, "%d", jumlahOrang);
    MQTTPublish(JUMLAH, jumlah);
    
    writeIndoor(0);// reset data (indoor tidak mendeteksi gerakan)
    writeOutdoor(0);// reset data (outdoor tidak mendeteksi gerakan)
    timer = 0;//reset timer =  mati
  }
  last = current;

  if (interval >= 500) {
    //membaca nilai pir dan mempublish data setiap 500ms
    pir();
    interval = 0;
  }

}
