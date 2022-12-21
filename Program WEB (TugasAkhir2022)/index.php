<!DOCTYPE html> 
<html lang="en">

    <head>
        
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Bantu Bencana Banjir Server</title>
   <!--icon web  -->
   
    <link href="img/b3ss.png" rel="shortcut icon">
   <!-- icon -->
   <!-- Bootstrap CSS -->
   <link rel="stylesheet" type="text/css" href="forstyle.css"/>
   <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
   
  
  
   <link rel="stylesheet" type="text/css" href="assets/css/bootstrap.min.css">
   <script type="text/javascript" src="assets/js/jquery-3.4.0.min.js"> </script>
   <script type="text/javascript" src="assets/js/mdb.min.js"> </script>
   <script type="text/javascript" src="jquery-latest.js"> </script>
   <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">

<script type="text/javascript">
$(document).ready(function() {
$("#nilai_tinggi_air").load("view/ketinggianair.php");
$("#nilai_tingkat_bahaya").load("view/tingkatbahaya.php");
var refreshId = setInterval(function()
{
  $("#nilai_tinggi_air").load('view/ketinggianair.php?randval='+ Math.random());
  $("#nilai_tingkat_bahaya").load('view/tingkatbahaya.php?randval='+ Math.random());
}, 1000);
});
</script>
</head>

<body id="page-top">
 <script type="text/javascript">
      var refreshid = setInterval(function(){
      $('#responsecontainer').load('grafik.php');
      }, 1000);
  </script>

     <nav class="fixed-top">
         <div class="logo">
            <img src="img/b3ss.png" width="40" height="40" style="text-align: center";> 
            &nbsp;&nbsp;&nbsp; <b>SENSOR BANJIR</b>
          </div>
     </nav>
       
            <div class="container">
              <br><br><br><br><br><br><br>
                <div class="tag" style="color:rgb(99, 205, 199);"><h1>SERVER DETEKSI KETINGGIAN AIR BANJIR PERUM BMI I & II</h1></div>
                <div id="wrapper">
                    <!-- Sidebar -->
        
                
                 
                           <!-- tempat tampilan grafik -->
                <div class="container" style="text-align: center;">
                  <h4>(Data yang ditampilkan adalah 5 data terakhir)</h4>
                  </div>
                  <!-- div grafik -->
                  <div class="container">
                  <div class="container shadow h-100 py-4"  id="responsecontainer" style="width: 75%; text-align:center"> </div>
                  </div>
                <br>

                <div class="container">
                  <div class="container shadow h-100 py-4"  id="responsecontainer" style="width: 75%; text-align:left">
               <div class="kategori">
                <h3><b><u>KATEGORI KETINGGIAN AIR</u></b></h3>
                <br>
                <div class="textkategori">
                <h4 style="color:rgb(255, 255, 255)"> • TINGKAT BAHAYA : 45cm - 180cm </h4>
                <h4 style="color:rgb(255, 255, 255)"> • TINGKAT AMAN &nbsp;&nbsp;&nbsp;&nbsp;: 0 cm - 45cm </h4>
                <br>
                </div>
                <h3 style="color:rgb(255, 255, 255)"><b>  PERINGATAN! </b></h3>
                <h7 style="color:rgb(255, 255, 255)"><i>  ( Jika Bendungan situ Kamojing dibuka, maka dalam kurun waktu  </i></h7>     
                <br>             
                <h7 style="color:rgb(255, 255, 255)"><i>   ± 1 jam ketinggian air dapat bertambah hingga ± 25 cm ) </i></h7>                               
                </div>
              </div>
                
           <br>
             
          <div class="container shadow h-100 py-4"  id="responsecontainer" style="width: 75%; text-align:center">
            <div class="row">

          <div class="cardname1">
            <p><b>KETINGGIAN AIR :</b></p>
            <h4><b><div id="nilai_tinggi_air" style="color:black ;"></div></b></h4>
          </div>

          <div class="cardname2">
            <p><b>TINGKAT BAHAYA :</b></p>
            <h4><b><div id="nilai_tingkat_bahaya" style="color:black ;"></div></b></h4>
          </div>
        
            </div>
        </div>

  <br>

  
    <div class="container shadow h-100 py-4"  id="responsecontainer" style="width: 75%; text-align:left">
  <div class="note">
  <h4 style="color:rgb(255, 255, 255)"> Alat deteksi banjir yang dibuat merupakan rangkaian Mikrokontroler dengan menggunakan algoritma <i>Fuzzy Logic (Fuzzy Tsukamoto)</i></h4>
  
  </div>
</div>

<br>

                    <h6 style = "text-align:center; color: white "><b> @Tugas Akhir 2022 - Budi Tri Setio - 18416255201070</b></h6>
    </div>
          </div>
          
         </body>
</html>