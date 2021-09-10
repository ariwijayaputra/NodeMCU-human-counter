# Description

`id`
Program untuk menghitung jumlah orang di dalam ruangan dan
mengirimkan datanya ke WEB melalui protokol MQTT 
(http://maqiatto.com). bekerja dengan menghitung orang yang masuk
dan keluar ruangan melalui sensor PIR di pintu bagian luar
dan pintu bagian dalam.

`en`
Program to count how many person is in the room and send
the data to WEB using MQTT protocol (http://maqiatto.com).
works by counting people coming and leaving the room 
via the PIR sensor on the exterior door and the inner door

# Material

Name				 				  | Amount  | Detail
---------------------------- | ------- | ------
NodeMCU Amica esp8266        | x2		|
LCD 16x2                     | x1      |(for indoor h/w only, but indoor & outdoor lcd is recommended)
LCD 16x2 I2C Module          | x1      |(amount depends on the lcd)
PIR sensor                   | x1		|
Cabel Jumper                 | depends |

# Schematic

ESP8266 | LCD I2C | PIR  | 5v
------- | ------- | ---- | ---
vin     | vcc     |      | 5v
gnd     | gnd     | gnd  |
3.3v    |         | vcc  |
D5      |         | data |
D1      | SCL     |      |
D2      | SDA     |      |

# Folder Structure
- maqiatto ==> folder for hardware code
    *	Credentials.h ==> your MQTT and WIFi personal data to connect to. `PLEASE EDIT BEFORE UPLOADING CODE`
    * MQTTConnector.cpp ==> file to connect to MQTT. act as data handler between MQTT and `.ino` file
    * MQTTConnector.h ==> header file to connect to MQTT. contains function declaration for data handler
    * Readme.md ==> this file
    * lcd.ino ==> lcd related code. Setting up lcd.
    * maqiatto.ino ==> main code to this program. contains loop and setup for NodeMCU.
    * pir.ino ==> PIR sensor related code. contains function to read data from environment. change `MQTTPublish(Topic, "1")` to `MQTTPublish(Topic, "2")` if you wish to upload code for `outdoor` NodeMCU so that we can determine the sensor data source.
- web
   * index.html ==> main view for monitoring data
   - js
     * websockets.js ==> data handler from mqtt broker
     * config.js ==> credential to mqtt broker. `PLEASE EDIT BEFORE TESTING`

# Langkah Langkah
1.  Rangkai komponen sesuai dengan skematik
2.  Sesuaikan `Credential.h` agar sesuai dengan data pada broker MQTT
3.  Sesuaikan `MQTTPublish` pada `pir.ino` agar sesuai dengan hardware. publish 1 untuk hardware indoor dan publish 2 untuk hardware outdoor
4.  Upload file pada folder maqiatto ke nodemcu
5.  sesuaikan data pada file web/js/config.js agar sesuai dengan data pada broker MQTT
6.  jalankan file web/index.html untuk menguji.
 
