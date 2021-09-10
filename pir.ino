void pir() {
  sensorValue = digitalRead(pirSensor);
  if (sensorValue == HIGH)
  {
    //publish: 1 = indoor sensor detecting, 2 = outdoor sensor detecting motion,     
    MQTTPublish(TOPIC, "1");
    Serial.println("motion detected");
    
    while(digitalRead(pirSensor)==HIGH){
      delay(10);
      //wait until sensor is in low state, otherwise it will publish multiple data to topic
    }
    
  }
  else{
    Serial.println("no motion");
    
  }
}
