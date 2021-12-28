<?php
	require_once 'database.php';
	$action = $_GET['action'];
	if ($action == 'insertData') {
		$dt_jumlah = new data_jumlah;
		$jumlah=$_POST["dt_jumlah"];
		$waktu=$_POST["dt_waktu"];
		$tanggal=$_POST["dt_tanggal"];
		$dt_jumlah->add($jumlah, $waktu,$tanggal);
	}
	if ($action == 'auth') {
		$admin = new admin();
		$username=$_POST["admin"];
		$password=$_POST["password"];
		$admin->auth($username, $password);
	}
	if ($action == 'edit') {
		$admin = new admin();
		$current=$_POST["current"];
		$new=$_POST["new"];
		$confirm=$_POST["confirm"];
		$admin->edit($current, $new, $confirm);
	}
?>