<?php
    // include koneksi
    include "koneksibendungan.php";

    $sql = mysqli_query($konek, "SELECT * FROM statusbendungan");
    $data = mysqli_fetch_array($sql);
    $bendungan = $data['bendungan'];
    // respon balik ke nodemcu
    echo $bendungan; // 1 / 0
?>