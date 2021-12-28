void pir() {
  sensorValue = digitalRead(pirSensor);
  if (sensorValue == HIGH)
  {
    //MQTTPublish(TOPIC, "1");
    if (in == 0) {
      Serial.println("motion 1 detected");
      in = 1;
      current = 1;
    }
    sensorValue = LOW;
  }
}
void pir2() {
  sensorValue2 = digitalRead(pirSensor2);
  if (sensorValue2 == HIGH)
  {
    //MQTTPublish(TOPIC, "1");
    if (out == 0) {
      Serial.println("motion 2 detected");
      out = 1;
      current = 2;
    }
    sensorValue2 = LOW;
  }
}
