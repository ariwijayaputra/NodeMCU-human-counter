var mqtt;
var current=0;
var last=0;
var indoor;
var outdoor; 
//fungsi untuk mengirimkan perintah ke Broker
function sendmesg(devicestring, command) {
 
  mqtt.send(devicestring, command);
 
}


//fungsi untuk melakukan koneksi dengan broker
//berdasarkan identitas dari broker seperti host, port, path, username dan password
$( document ).ready(function() {
  var reconnectTimeout = 2000;
  function MQTTconnect() {
  if (typeof path == "undefined") {
      path = '/mqtt';
  }
  mqtt = new Paho.MQTT.Client(
    host,
    port,
    path,
    "web_" + parseInt(Math.random() * 100, 10)
  );
      var options = {
          timeout: 3,
          useSSL: useTLS,
          cleanSession: cleansession,
          onSuccess: onConnect,
          onFailure: function (message) {
              $('#status').val("Connection failed: " + message.errorMessage + "Retrying");
              setTimeout(MQTTconnect, reconnectTimeout);
          }
      };

      mqtt.onConnectionLost = onConnectionLost;
      mqtt.onMessageArrived = onMessageArrived;

      if (username != null) {
          options.userName = username;
          options.password = password;
      }
      console.log("Host="+ host + ", port=" + port + ", path=" + path + " TLS = " + useTLS + " username=" + username + " password=" + password);
      mqtt.connect(options);
  }
  
  //fungsi untuk mengecek koneksi dengan broker
  function onConnect() {
		$('#status').html('Host: ' + host + ':' + port + path);
		mqtt.subscribe(topic, {qos: 0});
    mqtt.subscribe("aryanathaaa@gmail.com/jumlah", {qos: 0});
		console.log("onConnect");
  }

  //fungsi jika koneksi putus dengan broker
  function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

  //fungsi untuk menerima data dari broker
  function onMessageArrived(message) {

		var topic = message.destinationName;
		var payload = message.payloadString;
		
    if(topic == "aryanathaaa@gmail.com/status"){
      if (payload == '1') {
        $("#state").html("masuk");     
        indoor = 1;
        console.log('orang masuk');
      }
      if (payload == '2') {
        $("#state").html("Keluar");     
        indoor = 1;
        console.log('orang keluar');
      }
    }
    if(topic == jumlah){
      $("#jumlah").html(payload);     
      console.log(payload);
    }
  };

 

  $(document).ready(function() {
      MQTTconnect();   
  });

});
