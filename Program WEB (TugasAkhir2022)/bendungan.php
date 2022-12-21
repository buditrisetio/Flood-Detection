<?php
    
    include "koneksibendungan.php";
    //  mengambil parameter stat yang dikirim daru ajax
    $stat = $_GET['stat'];
    if($stat == "Sensor Banjir Aktif")
    {
        // ubah field relay menjadi 1
        mysqli_query($konek, "UPDATE statusbendungan SET bendungan=1");
        // berikan respon
        echo "Sensor Banjir Aktif";
    }
    else
    {
         // ubah field relay menjadi 0
         mysqli_query($konek, "UPDATE statusbendungan SET bendungan=0");
         // berikan respon
         echo "Sensor Banjir Nonaktif";
    }
?>