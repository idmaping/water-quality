#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#define LED_BUILTIN 2
const long utcOffsetInSeconds = 25200;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);


String Sdate = "";
String Stime = "";
int Sdo = 0;
int Sec = 0;
float Slat = 0;
float Slong = 0;
int Sorp = 0;
int Sph = 0;
int Stds = 0;
int Stemp = 0;
int Swc = 0;
int Mode = -1;
unsigned int time_second = 0;
unsigned int time_minute = 0;
unsigned int time_hour = 0;
unsigned int time_date = 0;
unsigned int time_month = 0;
unsigned int time_year = 0;
unsigned int time_temp = 0;
float vin = 0.0;
float deepth = 0.0;
unsigned int long time_now = 0;

//=======WIFI CONFIG
//const char *ssid     = "Spektrum Teknologi";
//const char *password = "#2019gantisplas";
//const char *ssid     = "Firman";
//const char *password = "12344321";
const char *ssid     = "roboat";
const char *password = "roboatum";


//=======FIREBASE CONFIG
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define API_KEY "AIzaSyAFOfvASHTz3jfe7kuXMlPH1joyq5dYjbw"
#define DATABASE_URL "https://sambigede-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define USER_EMAIL "id.maping@gmail.com"
#define USER_PASSWORD "firebase71217"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


void UpdateLastDatabase() {
  display.clearDisplay();
  Serial.println("Last Data Update !!!");
  display.setCursor(0, 0); display.print("a");  Firebase.setString(fbdo, "/last-data/kapal-1/date", Sdate) ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(15, 0); display.print("b");  Firebase.setString(fbdo, "/last-data/kapal-1/time", Stime) ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(30, 0); display.print("c"); Firebase.setInt(fbdo,   "/last-data/kapal-1/do",   Sdo)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(45, 0); display.print("d"); Firebase.setInt(fbdo,   "/last-data/kapal-1/ec",   Sec)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(60, 0); display.print("e"); Firebase.setFloat(fbdo,   "/last-data/kapal-1/lat",  Slat)  ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(75, 0); display.print("f"); Firebase.setFloat(fbdo,   "/last-data/kapal-1/long", Slong) ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(80, 0); display.print("g"); Firebase.setInt(fbdo,   "/last-data/kapal-1/orp",  Sorp)  ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(95, 0); display.print("h"); Firebase.setInt(fbdo,   "/last-data/kapal-1/ph",   Sph)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(110, 0); display.print("i"); Firebase.setInt(fbdo,   "/last-data/kapal-1/tds",  Stds)  ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(0, 10); display.print("j"); Firebase.setInt(fbdo,   "/last-data/kapal-1/temp", Stemp) ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(15, 10); display.print("k"); Firebase.setInt(fbdo,   "/last-data/kapal-1/wc",   Swc)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(30, 10); display.print("l"); Firebase.setInt(fbdo,   "/last-data/kapal-1/innertemp",   time_temp)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(45, 10); display.print("m"); Firebase.setFloat(fbdo,   "/last-data/kapal-1/vin",   vin)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(60, 10); display.print("n"); Firebase.setFloat(fbdo,   "/last-data/kapal-1/deepth",   deepth)   ? display.print("v") : display.print("x"); delay(100); display.display();
  
}

void UpdateRealtimeDatabase() {
  display.clearDisplay();
  Serial.println("RTDB Update !!!");
  String ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "date";
  display.setCursor(0, 10); display.print("A"); Firebase.setString(fbdo, ref, Sdate) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "time";
  display.setCursor(0, 20); display.print("B"); Firebase.setString(fbdo, ref, Stime) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "do";
  display.setCursor(15, 10); display.print("C"); Firebase.setInt(fbdo, ref, Sdo) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "ec";
  display.setCursor(15, 20); display.print("D"); Firebase.setInt(fbdo, ref, Sec) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "lat";
  display.setCursor(30, 10); display.print("E"); Firebase.setFloat(fbdo, ref, Slat) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "long";
  display.setCursor(30, 20); display.print("F"); Firebase.setFloat(fbdo, ref, Slong) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "orp";
  display.setCursor(45, 10); display.print("G"); Firebase.setInt(fbdo, ref, Sorp) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "ph";
  display.setCursor(45, 20); display.print("H"); Firebase.setInt(fbdo, ref, Sph) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "tds";
  display.setCursor(60, 10); display.print("I"); Firebase.setInt(fbdo, ref, Stds) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "temp";
  display.setCursor(60, 20); display.print("J"); Firebase.setInt(fbdo, ref, Stemp) ? display.print("v") : display.print("x"); delay(100); display.display();
  ref = "/dbrt/kapal-1/" + String(time_year) + "/" + String(time_month) + "/" + String(time_date) + "/" + String(time_now) + "/" + "wc";
  display.setCursor(75, 10); display.print("K"); Firebase.setInt(fbdo, ref, Swc) ? display.print("v") : display.print("x"); delay(100); display.display();
}


void UpdateSensor() {
  String c = Serial1.readStringUntil('\n');
  int addressZ = c.indexOf('Z');
  int addressA = c.indexOf('A');
  int addressB = c.indexOf('B');
  int addressC = c.indexOf('C');
  int addressD = c.indexOf('D');
  int addressE = c.indexOf('E');
  int addressF = c.indexOf('F');
  int addressG = c.indexOf('G');
  int addressH = c.indexOf('H');
  int addressI = c.indexOf('I');
  int addressJ = c.indexOf('J');
  int addressK = c.indexOf('K');
  int addressL = c.indexOf('L');
  int addressM = c.indexOf('M');
  int addressN = c.indexOf('N');
  int addressT = c.indexOf('T');
  int addressEnd = c.indexOf(';');
  Mode = c.substring(addressZ + 1, addressA).toInt();
  Sdate = c.substring(addressA + 1, addressB);
  Stime = c.substring(addressB + 1, addressC);
  Sdo = c.substring(addressC + 1, addressD).toInt();
  Sec = c.substring(addressD + 1, addressE).toInt();
  Slat = c.substring(addressE + 1, addressF).toFloat();
  Slong = c.substring(addressF + 1, addressG).toFloat();
  Sorp = c.substring(addressG + 1, addressH).toInt();
  Sph = c.substring(addressH + 1, addressI).toInt();
  Stds = c.substring(addressI + 1, addressJ).toInt();
  Stemp = c.substring(addressJ + 1, addressK).toInt();
  Swc = c.substring(addressK + 1, addressL).toInt();  
  time_temp = c.substring(addressL + 1, addressM).toInt();  
  vin = c.substring(addressM + 1, addressN).toFloat();  
  deepth = c.substring(addressN + 1, addressT).toFloat();
  time_now = c.substring(addressT + 1, addressEnd).toInt();  
  
}

void PrintSensor() {
  Serial.println("===========================");
  Serial.print("Mode : "); Serial.print(Mode); Mode == 0 ? Serial.println(" DRIVE MODE") : Serial.println(" MEASURE MODE");
  Serial.print("Date : "); Serial.println(Sdate);
  Serial.print("Time : "); Serial.println(Stime);
  Serial.print("DO : "); Serial.println(Sdo);
  Serial.print("EC : "); Serial.println(Sec);
  Serial.print("Lat : "); Serial.println(Slat, 5);
  Serial.print("Long : "); Serial.println(Slong, 5);
  Serial.print("ORP : "); Serial.println(Sorp);
  Serial.print("PH : "); Serial.println(Sph);
  Serial.print("TDS : "); Serial.println(Stds);
  Serial.print("Temp : "); Serial.println(Stemp);
  Serial.print("Inner Temp : "); Serial.println(time_temp);
  Serial.print("Vin : "); Serial.println(vin);
  Serial.print("Depth : "); Serial.println(deepth);
  Serial.print("Time Unix : "); Serial.println(time_now);
  
}

void DisplaySensor() {
  display.clearDisplay(); display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0); display.print(Sdate);
  display.setCursor(92, 0); display.print(Stime);

  if (Mode == 0) {
    display.fillRect(61, 0, 24, 9, SSD1306_WHITE);
    display.setTextColor(SSD1306_INVERSE);
    display.setCursor(65, 1); display.print("DRV");
  } else {
    display.drawRect(61, 0, 24, 9, SSD1306_WHITE);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(65, 1); display.print("MSR");
  }

  display.setCursor(0, 10); display.print("A:"); display.print(Sph);
  display.setCursor(0, 20); display.print("B:"); display.print(Stds);
  display.setCursor(30, 10); display.print("C:"); display.print(Sdo);
  display.setCursor(30, 20); display.print("D:"); display.print(Sec);
  display.setCursor(60, 10); display.print("E:"); display.print(Sorp);
  display.setCursor(60, 20); display.print("F:"); display.print(Stemp);
  display.setCursor(90, 10); display.print("G:"); display.print(Swc);
  






  display.display();
}

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);


  //=============OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  //=========WIFI INIT
  display.setCursor(0, 0);
  display.println("Connecting to ");
  display.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connected with IP: ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
  

  //==============FIREBASE INIT
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(6);
  
}

void loop()
{
  if (Serial1.available() > 0) {
    UpdateSensor();
    PrintSensor();

    if(Mode==0){
      // Serial.println("DRIVE MODE");
      UpdateLastDatabase();
    }else if(Mode==1){
      //Serial.println("MEASURE MODE");
      UpdateLastDatabase();
      //UpdateRealtimeDatabase();
    }
    
    //DisplaySensor();
  }

}
