<?php
// koneksi database
    $konek = mysqli_connect("localhost", "root", "", "sensor_air");
// baca data dari tabel tb_sensor

// baca 5 data ID tertinggi
    $sql_id = mysqli_query($konek, "SELECT MAX(id) FROM datasensor");
    $data_id = mysqli_fetch_array($sql_id);
    $id_akhir = $data_id['MAX(id)']; //ID terakhir
    $id_awal = $id_akhir - 4 ;

// baca informasi tanggal 5 data terakhir - sumbu x
    $waktu = mysqli_query($konek, "SELECT waktu from datasensor WHERE id>='$id_awal' and id<='$id_akhir' ORDER BY id ASC");
// baca informasi ketinggian air 5 data terakhir - sumbu y
    $ketinggian_air = mysqli_query($konek, "SELECT ketinggian_air from datasensor WHERE id>='$id_awal' and id<='$id_akhir' ORDER BY id ASC"); 
?>

<link rel="stylesheet" href="forstyle.css"/>
<!-- tampilan grafik -->
<div class="panel panel-info"> <!-- warna bodyy panel grafik --> 
    <div class="panel-heading">
        Grafik Sensor
    </div>

    <div class="panel-body">
        <!-- canvas grafik -->
        <canvas id="myChart"></canvas>
        <!-- gambar grafik -->
        <script type="text/javascript">
            // baca id canvas grafik
            var canvas = document.getElementById('myChart');
            // data tanggal dan ketinggian air untuk grafik
            var data = {
                labels : [
                    <?php
                        while($data_waktu = mysqli_fetch_array($waktu))
                        {
                            echo '"'.$data_waktu['waktu'].'",';
                        }
                    ?>
                ] ,
                datasets : [{
                    label : "Ketinggian Air (Dalam Satuan Sentimeter)",
                    fill : true,
                    backgroundColor: "rgba(99, 205, 250, .2)",
                    borderColor: "rgba(99, 205, 250, 1)",
                    LineTension: 0.3,
                    pointRadius: 5,
                    data : [
                        <?php
                        while($data_ketinggian_air = mysqli_fetch_array($ketinggian_air))
                        {
                            echo $data_ketinggian_air['ketinggian_air'].',';
                        }
                        ?>
                    ]
                }]
            };

            // option grafik
            var option = {
                showLines : true, 
                animation : {duration : 0}
            };

            // cetak kedalam canvas
            var myLineChart = Chart.Line(canvas, {
                data : data,
                options : option //option hilangkan s untuk animasi
            });

            </script>
    </div>
</div>