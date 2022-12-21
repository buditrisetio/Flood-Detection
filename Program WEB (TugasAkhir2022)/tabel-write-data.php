<?php
    //Variabel database
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "sensor_air";
    $conn = mysqli_connect("$servername", "$username", "$password","$dbname");

    //$Nama='Nama from Program 1';
    // Prepare the SQL statement
    $result = mysqli_query ($conn,"INSERT INTO datasensor (ketinggian_air, tingkat_bahaya) VALUES 
        ('".$_GET["Ketinggian-Air"]."', '".$_GET["Tingkat-Bahaya"]."')");    
    if (!$result) 
        {
            die ('Invalid query: '.mysqli_error($conn));
        }  
?>

