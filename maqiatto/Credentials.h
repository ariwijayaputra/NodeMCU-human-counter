#ifndef ARDUINO_CREDENTIALS_H
#define ARDUINO_CREDENTIALS_H

/* WiFi Credentials to connect Internet */
#define STA_SSID "AWP2" // wifi name
#define STA_PASS "Ariwijayaputra1" // wifi password

/* Provide MQTT broker credentials as denoted in maqiatto.com. */
#define MQTT_BROKER       "maqiatto.com"
#define MQTT_BROKER_PORT  1883
#define MQTT_USERNAME     "aryanathaaa@gmail.com"//example : aryanathaaa@gmail.com
#define MQTT_KEY          "Ariwijaya1"//your maqiatto password


/* Provide topic as it is denoted in your topic list. 
 * For example mine is : aryanathaaa@gmail.com/motion. <- motion is topic name
 * To add topics, see https://www.maqiatto.com/configure
 */
#define TOPIC   "aryanathaaa@gmail.com/motion"//ex : aryanathaaa@gmail.com/motion
#define STATUS  "aryanathaaa@gmail.com/status"//ex : aryanathaaa@gmail.com/status
#define JUMLAH  "aryanathaaa@gmail.com/jumlah"//ex : aryanathaaa@gmail.com/jumlah
#define WAKTU   "aryanathaaa@gmail.com/waktu"//ex : aryanathaaa@gmail.com/waktu
#define TANGGAL   "aryanathaaa@gmail.com/tanggal"//ex : aryanathaaa@gmail.com/tanggal
#endif /* ARDUINO_CREDENTIALS_H */
