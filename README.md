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
NodeMCU Amica esp8266        | x1		|
LCD 16x2                     | x1      |
LCD 16x2 I2C Module          | x1      |
PIR sensor                   | x2		|
RTC                          | x1      |
Cabel Jumper                 | depends |

# Schematic

ESP8266 | LCD I2C | PIR1 | PIR2 | RTC |
------- | ------- | ---- | ---- | --- |
vin     | vcc     | vcc  | vcc  |     |
gnd     | gnd     | gnd  | gnd  | gnd |
3.3v    |         |      |      | vcc |
D7      |         | data |      |     |
D6      |         |      | data |     |
D1      | SCL     |      |      | SCL |
D2      | SDA     |      |      | SDA |

![image](https://user-images.githubusercontent.com/62342206/146539453-be7d5a5c-0650-4969-833f-1e4c8705ee06.png)

# Folder Structure
- maqiatto ==> folder for hardware code
    *	Credentials.h ==> your MQTT and WIFi personal data to connect to. `PLEASE EDIT BEFORE UPLOADING CODE`
    * MQTTConnector.cpp ==> file to connect to MQTT. act as data handler between MQTT and `.ino` file
    * MQTTConnector.h ==> header file to connect to MQTT. contains function declaration for data handler
    * Readme.md ==> this file
    * lcd.ino ==> lcd related code. Setting up lcd.
    * maqiatto.ino ==> main code to this program. contains loop and setup for NodeMCU.
    * pir.ino ==> PIR sensor related code. contains function to read data from environment.
- web
   * index.html ==> main view for monitoring data
   - js
     * websockets.js ==> data handler from mqtt broker
     * config.js ==> credential to mqtt broker. `PLEASE EDIT BEFORE TESTING`

# Panduan instalasi
1.  Rangkai komponen sesuai dengan skematik
2.  Sesuaikan `Credential.h` agar sesuai dengan data pada broker MQTT
3.  Upload file pada folder maqiatto ke nodemcu
4.  sesuaikan data pada file web/js/config.js agar sesuai dengan data pada broker MQTT
5.  jalankan file web/index.html untuk menguji.

# Installation Guide
1. Assemble the components according to the schematic
2. Adjust Credential.h to match the data on the MQTT broker
3. Upload files in the maqiatto folder to nodemcu
4. adjust the data in the web/js/config.js file to match the data in the MQTT broker
5. run the web/index.html file to test.
 
