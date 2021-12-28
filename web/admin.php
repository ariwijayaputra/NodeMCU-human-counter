<div class="card m-2">
        <div class="card-body">
          <center>
            <h3>
              waktu : 
              <span id="waktu"></span>
            </h3>
          </center>
          
        </div>
      </div>
      <div class="card m-2">
        <div class="card-body">
          <center>
            <h3>
              tanggal : 
              <span id="tanggal"></span>
            </h3>
          </center>
          
        </div>
      </div>
      <div class="table-responsive p-4" id="tampil_data">
<table class="table table striped">
		<thead>
            <tr>
              <th>waktu</th>
              <th>jumlah</th>
              <th>tanggal</th>
            </tr>
        </thead>
        <tbody>
        	 <?php
        	 include 'database.php';
  			  $db = new database;
              $id=0;
              $No=0;
              $dt_jumlah = new data_jumlah;
              foreach ($dt_jumlah->selectall() as $x) {        
              ?>
            <tr>
              <td><?php echo $x['waktu']; ?></td>
              <td><?php echo $x['jumlah']; ?></td>
              <td><?php echo $x['tanggal']; ?></td>
          	</tr>
            <?php } ?>
        </tbody>
</table>
</div>
<div class="d-flex justify-content-center">
   <a class="btn btn-danger m-2"  href="logout.php" role="button">Logout</a> 
   <a class="btn btn-primary m-2"  href="changePassword.php" role="button">Change Admin Password</a> 
</div>