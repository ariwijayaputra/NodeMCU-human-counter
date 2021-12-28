<!DOCTYPE html>
<?php
  session_start();
?>
<html lang="en">
<head>
	<title>Human Counter</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<script src="https://cdnjs.cloudflare.com/ajax/libs/paho-mqtt/1.0.1/mqttws31.js" type="text/javascript"></script>
	<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-+0n0xVW2eSR5OomGNYDnhzAbDsOXxcvSN1TPprVMTNDbiYZCxYbOOl7+AMvyTG2x" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.1/dist/js/bootstrap.bundle.min.js" integrity="sha384-gtEjrD/SeCtmISkJkNUaaKMoLD0//ElJ19smozuHV6z3Iehds+3Ulb9Bn9Plx0x4" crossorigin="anonymous"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <script src="js/config.js" type="text/javascript"></script>
	<script src="js/websockets.js"></script>
</head>
<body class="p-3"> 
<div>
	<h2>
		<center>
			PIR Sensor
		</center>
	</h2>
	<div class="row">
			<div class="card m-2">
				<div class="card-body">
					<center>
						<h3>
							jumlah : 
							<span id="jumlah"></span>
						</h3>
					</center>	
				</div>
			</div>

	</div>
</div>

	<?php
		if (isset($_SESSION["username"])) {
		    include 'admin.php';
		}
		if(!isset($_SESSION["username"])){
			echo '
				<div class="d-flex justify-content-center">
					<a class="btn btn-primary m-2"  href="login.php" role="button">Login</a>
				</div>
			';
		}
	?>

</body>
</html>