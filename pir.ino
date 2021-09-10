void pir() {
  sensorValue = digitalRead(pirSensor);
  if (sensorValue == HIGH)
  {
    /*
    CHANGE `MQTTPublish(TOPIC, "1");` to  `MQTTPublish(TOPIC, "2");` if you working
    with outdoor nodeMCU
    publish: 1 = indoor sensor detecting, 2 = outdoor sensor detecting motion
    */     
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
