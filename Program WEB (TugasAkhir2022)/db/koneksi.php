<?php
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "sensor_air";
$konek = mysqli_connect ($servername, $username, $password, $dbname); // Perintah untuk menghubungkan ke database
if (!$konek) {
    die("Connection failed: " . mysqli_connect_error());
}


?>