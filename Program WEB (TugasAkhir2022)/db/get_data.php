<?php
function data($val){ 
    include ("koneksi.php");
    $db = mysqli_query($konek, "SELECT * FROM `datasensor` ORDER BY `waktu` DESC"); //sensor_suhu itu nama folder db bukan nama db nya
    if ($data = mysqli_fetch_array($db) ){
        
        return $data[$val];
    }
    else{
        return $not;
    }
}
?>
