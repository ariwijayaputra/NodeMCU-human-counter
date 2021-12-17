#ifndef ARDUINO_CREDENTIALS_H
#define ARDUINO_CREDENTIALS_H

/* WiFi Credentials to connect Internet */
#define STA_SSID "" // wifi name
#define STA_PASS "" // wifi password

/* Provide MQTT broker credentials as denoted in maqiatto.com. */
#define MQTT_BROKER       "maqiatto.com"
#define MQTT_BROKER_PORT  1883
#define MQTT_USERNAME     ""//example : aryanathaaa@gmail.com
#define MQTT_KEY          ""//your maqiatto password


/* Provide topic as it is denoted in your topic list. 
 * For example mine is : aryanathaaa@gmail.com/motion. <- motion is topic name
 * To add topics, see https://www.maqiatto.com/configure
 */
#define TOPIC   ""//ex : aryanathaaa@gmail.com/motion
#define STATUS  ""//ex : aryanathaaa@gmail.com/status
#define JUMLAH  ""//ex : aryanathaaa@gmail.com/jumlah
#define WAKTU   ""//ex : aryanathaaa@gmail.com/waktu
#define TANGGAL   ""//ex : aryanathaaa@gmail.com/waktu
#endif /* ARDUINO_CREDENTIALS_H */
