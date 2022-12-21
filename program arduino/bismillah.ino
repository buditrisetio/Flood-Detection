//--- PERANCANGAN ALAT DETEKSI DINI BENCANA BANJIR MENGGUNAKAN ---//
//------ METODE FUZZY TSUKAMOTO BERBASIS INTERNET OF THINGS ------//
#include <ESP8266HTTPClient.h>       // Library Komunikasi database
#include <ESP8266WiFi.h>             // Library Komunikasi WiFi pada ESP8266
#include <math.h>                    // Library Perhitungan Matematika (Fuzzy Logic Tsukamoto)
#include <Wire.h>                    // Library Komunikasi Serial 

//--- Konfigurasi WiFi (Hotspot) ---//
const char *ssid = "Redmi";          // Nama WiFi
const char *password = "hahahaha";   // Password WiFi
const char *host = "192.168.140.46"; // IP Address Server pada Laptop
                                     // IP addres akan berubah jika media yg digunakan berbeda
//--- Deklarasi INPUT & OUTPUT ---//

int echoPin = 14;      // Sensor HC-SR04 pada pin GPIO14 / D5
int triggerPin = 12;   // Sensor HC-SR04 pada pin GPIO12 / D6
int Led_Hijau = 3;     // Led Hijau pada pin GPIO3 / RX (menandakan tingkat bahaya aman)
int Led_Kuning = 13;   // Led Kuning pada pin GPIO13 / D7 (menandakan sensor aktif)
int Led_Merah = 15;    // Led Merah pada pin GPIO15 / D8 (menandakan tingkat bahaya bahaya)
int Buzzer = 5;        // Buzzer pada pin GPIO5 / D1
int hasil;


float ketinggian_air;
String tingkatbahaya;  // Variabel String 
float ketinggian_air_rendah, ketinggian_air_sedang, ketinggian_air_tinggi;
float z1, z2, z3;
float nilai_z1, nilai_z2, nilai_z3;
float z_jumlah_nilai;
float z_jumlah_alpha_predikat;
float z_total; 

int i;                 // led


   


                       
//--- RUMUS FUZZIFIKASI PADA VARIABEL KETINGGIAN AIR ---//
float u_ketinggian_air_rendah ()                           // Nilai derajat keanggotaan dari ketinggianair_rendah 20cm - 30cm
{
  if (ketinggian_air <= 20)    
    {
      ketinggian_air_rendah = 1;                           // jika ketinggianair dibawah 20cm maka himpunannya bernilai 1
    }
  else if (ketinggian_air >= 20 && ketinggian_air <= 30)
    {
      ketinggian_air_rendah = (30 - ketinggian_air) / 10;   // (30 - ketinggianair) / (30 - 20)
    }
  else if (ketinggian_air >= 30)
    {
      ketinggian_air_rendah = 0;                           // jika ketinggianair diatas 30cm maka himpunannya bernilai 0
    }
}

float u_ketinggian_air_sedang ()                           // Nilai derajat keanggotaan dari ketinggianair_sedang 30cm - 40cm
{
  if (ketinggian_air <= 20)
    {
      ketinggian_air_sedang = 0;                           // jika ketinggianair dibawah 20cm maka himpunannya bernilai 0
    }
  else if (ketinggian_air >= 20 && ketinggian_air <= 30)
    {
      ketinggian_air_sedang = (ketinggian_air - 20) / 10;   // (ketinggianair - 20) / (30 - 20)       
    }
  else if (ketinggian_air >= 30 && ketinggian_air <= 35)
    {
      ketinggian_air_sedang = 1;                           // jika ketinggianair diatas 30cm & dibawah 35 cm maka himpunannya bernilai 0
    }
  else if (ketinggian_air >= 35 && ketinggian_air <= 45)
    {
      ketinggian_air_sedang = (45 - ketinggian_air) / 10;   // (45 - ketinggianair) / (45 - 35)         
    }
  else if (ketinggian_air >= 45)
    {
      ketinggian_air_sedang = 0;                           // jika ketinggianair diatas 45 cm maka himpunannya bernilai 0
    }
}

float u_ketinggian_air_tinggi ()                           // Nilai derajat keanggotaan dari ketinggianair_tinggi 35cm - 45cm                            
{
  if (ketinggian_air <= 35)
    {
      ketinggian_air_tinggi = 0;                           // jika ketinggianair dibawah 40cm maka himpunannya bernilai 0
    }
  else if (ketinggian_air >= 35 && ketinggian_air <= 45)
    {
      ketinggian_air_tinggi = (ketinggian_air - 35) / 10;   // (ketinggianair - 35) / (45 - 35)       
    }
  else if (ketinggian_air >= 45)
    {
      ketinggian_air_tinggi = 1;                           // jika ketinggianair diatas 45cm maka himpunannya bernilai 1
    }
}


void setup() {
  Serial.begin(9600);                  // Komunikasi dengan Serial Monitor dan kecepatan komunikasi (baudrate)
  pinMode(echoPin, INPUT);             // Menjadikan Ultrasonik Echo sebagai INPUT
  pinMode(triggerPin, OUTPUT);         // Menjadikan Ultrasonik Trigger sebagai OUTPUT
  pinMode (Led_Hijau, OUTPUT);         // Menjadikan Led Hijau sebagai OUTPUT
  pinMode (Led_Merah, OUTPUT);         // Menjadikan Led Merah sebagai OUTPUT
  pinMode (Led_Kuning, OUTPUT);            // Menjadikan Buzzer sebagai OUTPUT
  pinMode (Buzzer, OUTPUT);
  
  
  
//--- Proses Konektifitas WiFi ---//
// konektifitas WiFi sesuai dengan ssid dan password yang terdaftar yang dilakukan berulang-ulang hingga WiFi tehubung  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Terkoneksi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {
   
   long duration;        
   digitalWrite(triggerPin, LOW);
   delayMicroseconds(2); 
   digitalWrite(triggerPin, HIGH);
   delayMicroseconds(10); 
   digitalWrite(triggerPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   ketinggian_air = 180 - ((duration/2) / 29.1) ; // 180 dikurangi nilai baca sensor HC-SR04, hal ini dilakukan karena sensor diletakan berjarak 180cm dari objek baca sensor 
   delay(100);


//--- Tampilan Serial Monitor ---//
   Serial.println   (" ");
   Serial.println (" +---------------------------- SELAMAT DATANG ----------------------------+ ");
   Serial.print   (" ");
   Serial.print   (" KETINGGIAN AIR : ");
   Serial.print   (ketinggian_air);
   Serial.println (" cm");
   Serial.print   (" WAKTU PANTULAN : ");
   Serial.print   (duration);
   Serial.println (" µs");
   
//--- Proses Fuzzyfikasi ---//
//--- fuzzifikasi rule ---//
//--- [R1] = Jika ketinggianair_rendah, maka tingkatbahaya AMAN ---//
//--- [R2] = Jika ketinggianair_sedang, maka tingkat bahaya AMAN ---//
//--- [R3] = Jika ketinggianair_tinggi, maka tingkat bahaya BAHAYA ---//
   Serial.println (" ");
   Serial.print (" +------------------------------ FUZZYFIKASI -----------------------------+ ");
   Serial.println (" ");
//--- Derajat keanggotaan ---//   
   Serial.println (u_ketinggian_air_rendah ());
   Serial.print (" : Derajat Keanggotaan Ketinggian Air Rendah = ");
   Serial.println (ketinggian_air_rendah);   
   Serial.print (u_ketinggian_air_sedang ());
   Serial.print (" : Derajat Keanggotaan Ketinggian Air Sedang = ");
   Serial.println (ketinggian_air_sedang);  
   Serial.print (u_ketinggian_air_tinggi ());
   Serial.print (" : Derajat Keanggotaan Ketinggian Air Tinggi = ");
   Serial.println (ketinggian_air_tinggi);  
   
   
//--- Proses Inferensi ---//  
   Serial.println (" ");
   Serial.println (" +------------------------------- INFERENSI ------------------------------+ ");
   Serial.print   (" ");
//--- [R1] = if Ketinggian air RENDAH, then tingkat bahaya AMAN --// 
   Serial.println (" [R1]             = if Ketinggian air RENDAH, then tingkat bahaya AMAN");
   Serial.print   (" ");
   Serial.print (" Alpha Predikat 1 = ");
   Serial.println (ketinggian_air_rendah);
   z1 = ketinggian_air_rendah * 20 ;
   nilai_z1 = 50 - z1 ;
   Serial.print   (" ");
   Serial.print (" Nilai z1         = ");
   Serial.println (nilai_z1);
   Serial.print   (" ");

//--- [R2] = if Ketinggian air SEDANG, then tingkat bahaya AMAN --// 
   Serial.println (" [R2]             = if Ketinggian air SEDANG, then tingkat bahaya AMAN");
   Serial.print   (" ");
   Serial.print (" Alpha Predikat 2 = ");
   Serial.println (ketinggian_air_sedang);
   z2 = ketinggian_air_sedang * 20 ;
   nilai_z2 = 50 - z2 ;
   Serial.print   (" ");
   Serial.print (" Nilai z2         = ");
   Serial.println (nilai_z2);
   Serial.print   (" ");   

//--- [R3] = if Ketinggian air TINGGI, then tingkat bahaya BAHAYA --// 
   Serial.println (" [R3]             = if Ketinggian air TINGGI, then tingkat bahaya BAHAYA");
   Serial.print   (" ");
   Serial.print (" Alpha Predikat 3 = ");
   Serial.println (ketinggian_air_tinggi);
   z3 = ketinggian_air_tinggi * 20 ;
   nilai_z3 = 30 + z3 ;
   Serial.print   (" ");
   Serial.print (" Nilai z3         = ");
   Serial.println (nilai_z3);
   

//--- Proses Defuzzyfikasi ---//  
   Serial.println (" ");
   Serial.println (" +---------------------------- DEFUZZYFIKASI -----------------------------+ ");
   Serial.print   (" ");
   
   z_jumlah_nilai = (ketinggian_air_rendah * nilai_z1)+(ketinggian_air_sedang * nilai_z2)+(ketinggian_air_tinggi * nilai_z3) ;
   z_jumlah_alpha_predikat = (ketinggian_air_rendah + ketinggian_air_sedang + ketinggian_air_tinggi) ;
   z_total = z_jumlah_nilai / z_jumlah_alpha_predikat ;
   Serial.print (" z Total = ("); Serial.print (ketinggian_air_rendah); Serial.print ("x"); Serial.print (nilai_z1); Serial.print (")"); 
   Serial.print ("+"); Serial.print ("("); Serial.print (ketinggian_air_sedang); Serial.print ("x"); Serial.print (nilai_z2); Serial.print (")");    
   Serial.print ("+"); Serial.print ("("); Serial.print (ketinggian_air_tinggi); Serial.print ("x"); Serial.print (nilai_z3); Serial.print (")");
   Serial.print ("/");
   Serial.print ("("); Serial.print (ketinggian_air_rendah); Serial.print ("+"); Serial.print (ketinggian_air_sedang); Serial.print ("+"); Serial.print (ketinggian_air_tinggi); Serial.println (")");
   Serial.print (" ");
   Serial.print (" z Total = ");
   Serial.println (z_total);
   Serial.print   (" ");
   Serial.print (" Maka Tingkat Bahayanya adalah = ");
   Serial.println (tingkatbahaya);

//--- Deklarasi Tingkat Bahaya ---//
   if (z_total <= 40){
    Serial.print ("");
    digitalWrite(Led_Hijau, HIGH);  
    delay(1000);
    digitalWrite(Led_Hijau, LOW);   
    delay(1000);   
    tingkatbahaya = "AMAN";
   }
     if (ketinggian_air <= 35 && ketinggian_air >= 30){
    Serial.print ("");
    digitalWrite(Led_Kuning, HIGH); 
    digitalWrite(Buzzer, HIGH);  
    delay(85);
    digitalWrite(Led_Kuning, LOW); 
    digitalWrite(Buzzer, LOW);   
    delay(85);   
   }
    delay(2000);
    if (z_total > 40){
//    for (i=0; i<4; i=i+1)
    Serial.print ("");
    digitalWrite(Led_Merah, HIGH); 
    digitalWrite(Buzzer, HIGH); 
    delay(1000);
    digitalWrite(Led_Merah, LOW);
    digitalWrite(Buzzer, LOW);   
    delay(1000); 
    tingkatbahaya = "BAHAYA";  
   }
    delay(2000);
   

// ================================== Proses Pengiriman Data pada Database =================================
/* Proses pengiriman data pada database dengan alamat sesuai wi-fi yang dipakai. 
   Pengiriman data ini apabila alamat wi-fi salah, maka data gagal terkirim, 
   Apabila alamat wi-fi benar maka isi data suhu tubuh dan kondisi badan yang diperoleh akan dikirim ke alamat IP ESP8266 dan mengirim request data ke server web*/
    Serial.println (" ");
    Serial.println (" +----------------------- KIRIM DATA KE DATABASE -------------------------+ ");
    Serial.print   (" ");
    Serial.print   (" Wi-Fi (Hotspot) : ");
    Serial.println (ssid);
    Serial.print   (" ");
    Serial.print   (" Koneksi dari IP Address : ");
    Serial.println (host);

// =============================== Mengirimkan ke alamat host dengan port 80 ===============================
       WiFiClient client;
       const int httpPort = 80;
       if (!client.connect(host, httpPort)) {
          Serial.println("Koneksi Gagal");
          return;
       }

// ======================== Isi Konten yang dikirim adalah alamat dari IP ESP8266 ==========================
       String url = "/TugasAkhir2022/tabel-write-data.php?Ketinggian-Air=";   // Mengarah ke File eko-tugas-akhir di folder htdocs (HTML)
       url += ketinggian_air;
       url += "&Tingkat-Bahaya=";
       url += tingkatbahaya;
//        Serial.print   (" Requesting URL : ");
//        Serial.println (url);
          Serial.println (" ");
          Serial.println (" +--------------------------------- END ----------------------------------+ ");
          

  //=========================== Sensor =============================
// baca status bendungan
  String LinkBendungan ;
  HTTPClient httpBendungan ;
  LinkBendungan = "http://" +String(host)+ "/TugasAkhir2022/bacabendungan.php";
  httpBendungan.begin(LinkBendungan);
//  ambil isi status bendungan
  httpBendungan.GET();
//  baca status respon
   String responseBendungan = httpBendungan.getString();
   Serial.println(responseBendungan);
   httpBendungan.end();
   //   UBAH STATUS BENDUNGAN DI NODEMCU
digitalWrite(Led_Kuning, responseBendungan.toInt());
if (responseBendungan.toInt() == 1){
  digitalWrite (triggerPin, HIGH);
  digitalWrite (echoPin, HIGH); 
  Serial.print(" Sensor Banjir Aktif ");
  digitalWrite(Buzzer, HIGH);
  delay (70);
  digitalWrite(Buzzer, LOW);
}
else if (responseBendungan.toInt() == 0){
  digitalWrite (triggerPin, LOW);
  digitalWrite (echoPin, LOW); 
  digitalWrite (Led_Hijau, LOW); 
  digitalWrite (Led_Merah, LOW); 
  digitalWrite(Buzzer, LOW);
  Serial.print(" Sensor Banjir Nonaktif ");
}


// ======================== Mengirimkan Request Data yang didapat ke Server (Web) ==========================
       client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
       unsigned long timeout = millis();
       while (client.available() == 0) {
            if (millis() - timeout > 1000) {
               Serial.println(">>> Client Timeout !");
               client.stop();
               return;
            }
       } 
       delay(2000);
} 
