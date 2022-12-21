<?php
	$dbhost="localhost";
	$dbuser="root";
	$dbpass="";
	$dbname="sensor_air";

	$konek=mysqli_connect($dbhost, $dbuser, $dbpass) or die("Server tidak terhubung");
	if ($konek){
   		 mysqli_select_db($konek,$dbname);
	} else {
    	echo "Server tidak terhubung. <br>";
	}
?>