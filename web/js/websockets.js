var mqtt;
var nowJumlah;
var nowTanggal;
var flag = 0;
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
      mqtt.connect(options);
  }
  
  //fungsi untuk mengecek koneksi dengan broker
  function onConnect() {
		$('#status').html('Host: ' + host + ':' + port + path);
		mqtt.subscribe(topic, {qos: 0});
    mqtt.subscribe("aryanathaaa@gmail.com/jumlah", {qos: 0});
    mqtt.subscribe("aryanathaaa@gmail.com/waktu", {qos: 0});
    mqtt.subscribe("aryanathaaa@gmail.com/tanggal", {qos: 0});
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
		console.log(topic);
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
    if(topic == waktu){
      $("#waktu").html(payload);   
      let nowWaktu = payload;  
      let str = payload;
      const arrWaktu = str.split(":");
      
      if(arrWaktu[0]=="16" || arrWaktu[0]=="10"){ 
        if(flag == 1){
          $.post('action.php?action=insertData',{dt_jumlah: nowJumlah,
              dt_waktu: nowWaktu, dt_tanggal: nowTanggal},
               function(data){
                $('#tampil_data').load("tabel.php");
            });
            flag = 0;//dont upload data again
          }
        }
        else{
          flag = 1;//ready to upload data
        }
      }
    if(topic == jumlah){
      $("#jumlah").html(payload);     
      nowJumlah = payload;
      console.log(nowJumlah);
    }
    if(topic == tanggal){
      $("#tanggal").html(payload);     
      nowTanggal = payload;
      console.log(nowTanggal);
    }
  };
  $(document).ready(function() {
      MQTTconnect();  
      
  });
});
