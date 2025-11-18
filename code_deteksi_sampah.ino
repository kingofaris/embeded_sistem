#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD (alamat 0x27 bisa berbeda, tergantung modul)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 8;

long duration;
int distance;
int count = 0;
bool objectDetected = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Botol Terdeteksi:");
  lcd.setCursor(0,1);
  lcd.print("Jumlah: 0");
}

void loop() {
  // Kirim pulsa ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Hitung waktu pantulan
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // dalam cm

  // Deteksi objek lewat (misal jarak < 10 cm)
  if (distance < 10 && !objectDetected) {
    objectDetected = true;
    count++;
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Botol Terdeteksi:");
    lcd.setCursor(0,1);
    lcd.print("Jumlah: ");
    lcd.print(count);
    
    delay(500); // jeda untuk menghindari double count
  }

  // Reset deteksi jika objek sudah lewat
  if (distance >= 10 && objectDetected) {
    objectDetected = false;
  }
  
  delay(100);
}
