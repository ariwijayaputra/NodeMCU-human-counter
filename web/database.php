<?php
	/**
	 * 
	 */
	class database
	{
		var $servername="localhost";
		var $username="root";
		var $password="";
		var $dbname="jumlahorang";
		
		public function connect(){
			$conn="";
			$this->$conn = new mysqli($this->servername, $this->username, $this->password, $this->dbname) or die("Couldn't connect");
			return $this->$conn;
		}
	}
	class data_jumlah extends database{
		public function selectall()
		{
			$conn = $this->connect();
			$data = $conn->query("select * from tb_jumlah") or die($conn->error);
			while($d = $data->fetch_assoc()){
				$result[] = $d;
			}
			return $result;
		}
		public function add($jumlah,$waktu,$tanggal)
		{
			$conn = $this->connect();
			$sql = "INSERT INTO tb_jumlah(jumlah,waktu,tanggal) VALUES(?,?,?)";
			$result=$conn->prepare($sql);
			$result->bind_param("iss",$jumlah,$waktu,$tanggal);
			$result->execute();
			mysqli_stmt_store_result($result);
			if ($result) {
				//header("location:index.php");
			}
			else{
				echo "
					<script>
						alert('Data Gagal Disimpan');
						window.location.href='index.php';
					</script>
				";
			}
		}
	}
	class admin extends database
	{
		public function auth($username, $password)
		{
			session_start();
			$conn = $this->connect();
			$sql = "SELECT * FROM admin WHERE username=
			'".$username."' AND password= '".$password."'";
			$result = $conn->query($sql)
			or die($conn->error);
			if($d = $result->fetch_assoc()){
				$_SESSION["username"]=$username;
				header('location:index.php');
			}
			else{
				echo "
				<script>
					alert('Akun tidak ditemukan!');
					window.location.href='login.php';
				</script>
				";
			}
			return $result;
		}
		public function edit($current, $new, $confirm)
		{
			$username = "admin";
			$flag = 0;
			$conn = $this->connect();
			$sql = "SELECT * FROM admin WHERE username=
			'".$username."' AND password= '".$current."'";
			$result = $conn->query($sql)
			or die($conn->error);
			if($d = $result->fetch_assoc()){
				$flag = 1;
			}
			if($new == $confirm && $flag == 1){
				$sql = "UPDATE admin SET password = ?  WHERE username = ?";
				$result=$conn->prepare($sql);
				$result->bind_param("ss",$new,$username);
				$result->execute();
				mysqli_stmt_store_result($result);
				if ($result) {
					echo "
						<script>
							alert('Password berhasil diubah');
							window.location.href='index.php';
						</script>
					";
				}
				else{
					echo "
						<script>
							alert('Data Gagal Disimpan');
							window.location.href='changePassword.php';
						</script>
					";
				}
				$flag = 0;
			}
			else if($new!=$confirm){
				echo "
						<script>
							alert('Konfirmasi Password Salah');
							window.location.href='changePassword.php';
						</script>
					";
			}
			else if ($flag!=1){
				echo "
				<script>
					alert('Password Saat Ini Salah');
					window.location.href='changePassword.php';
				</script>
				";
			}
			
		}
	}
	
?>