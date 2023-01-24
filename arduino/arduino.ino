#include <LiquidCrystal_I2C.h> 
#include <SoftwareSerial.h> 

LiquidCrystal_I2C lcd(0x3F, 20, 4);
SoftwareSerial ss(2,3);

// inisiasi variabel pin buzzer
const int pinBuzzer = 3;

//inisiasi variabel pin sensor
const int pinMQ4A=1;
const int pinMQ4D=7;
const int pinMQ136A=2;
const int pinMQ136D=4;
const int pinMQ137A=0;
const int pinMQ137D=8;

//inisiasi variabel output analog sensor
int MQ4OutA;
int MQ136OutA;
int MQ137OutA;

//inisiasi variabel output digital sensor
int MQ4OutD;
int MQ136OutD;
int MQ137OutD;

//inisiasi variabel to string
String skorMQ4;
String skorMQ136;
String skorMQ137;

//inisiasi range ppm sensor
float rangeMQ4 = 9700.00;
float rangeMQ136 = 199.00;
float rangeMQ137 = 495.00;

//inisiasi variabel awal lcd
boolean lcdBool = true;

void setup() {
  Serial.begin(9600);
  ss.begin(115200);
  
  pinMode(pinMQ4D, INPUT);
  pinMode(pinMQ136D, INPUT);
  pinMode(pinMQ137D, INPUT);
  
  lcd.init();
  lcd.backlight();
}

void loop(){
  //cek lcd
  if(lcdBool){
    //print ke lcd
    lcd.setCursor(0,0);
    lcd.print("Loading ...");

    lcd.setCursor(0,1);
    lcd.print("SKOR MQ4: 0");
  
    lcd.setCursor(0,2);
    lcd.print("SKOR MQ136: 0");
    
    lcd.setCursor(0,3);
    lcd.print("SKOR MQ137: 0");

    lcdBool = false;

    delay(5000);
  }

  
  //baca hasil sensor analog
  MQ4OutA = analogRead(pinMQ4A); 
  MQ136OutA = analogRead(pinMQ136A);
  MQ137OutA = analogRead(pinMQ137A);

  //baca hasil sensor digital
  MQ4OutD = digitalRead(pinMQ4D);
  MQ136OutD = digitalRead(pinMQ136D);
  MQ137OutD = digitalRead(pinMQ137D);

  //Konversi
  float voltMQ4 = adc(MQ4OutA);
  float ppmMQ4 = ppm(rangeMQ4, voltMQ4);

  float voltMQ136 = adc(MQ136OutA);
  float ppmMQ136 = ppm(rangeMQ136, voltMQ136);

  float voltMQ137 = adc(MQ137OutA);
  float ppmMQ137 = ppm(rangeMQ137, voltMQ137);

  //convert ke string
  skorMQ4 = String(ppmMQ4);
  skorMQ136 = String(ppmMQ136);
  skorMQ137 = String(ppmMQ137);

  //kirim ke esp8266
  String send = "";
  send += ppmMQ4;
  send += ";";
  send += ppmMQ136;
  send += ";";
  send += ppmMQ137;

  ss.println(send);
  
  //print ke lcd
  lcd.setCursor(0,0);
  lcd.print("PPM MQ4: " + skorMQ4);

  lcd.setCursor(0,1);
  lcd.print("PPM MQ136: " + skorMQ136);
  
  lcd.setCursor(0,2);
  lcd.print("PPM MQ137: " + skorMQ137);

  for(int i = 0; i < 20; i++){
    lcd.setCursor(i,3);
    lcd.print(" ");
  }

//untuk testing di serial monitor
//  Serial.print("Data mentah MQ4: ");
//  Serial.println(MQ4OutA);
//  Serial.print("Tegangan MQ4: ");
//  Serial.println(voltMQ4);
//  Serial.print("PPM MQ4: ");
//  Serial.println(ppmMQ4);
  
   delay(1000);
}
//function convert dari analog ke digital/volt
float adc(int analog){
  return analog * (5.00 /1024.00);
}
//function convert digital/volt ke ppm
float ppm(float selisih, float digital){
  return (selisih / 5.00) * digital; 
}
