#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include <RtcDS1307.h>
RtcDS1307<TwoWire> Rtc(Wire);
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
#include <TinyGPS.h>
TinyGPS gps;


//=======WIFI CONFIG
//const char *ssid     = "Spektrum Teknologi";
//const char *password = "#2019gantisplas";
const char *ssid     = "Firman";
const char *password = "12344321";

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
unsigned long sendDataPrevMillis = 0;
unsigned long sendDataPrevMillis2 = 0;
unsigned long sendDataPrevMillis3 = 0;


//=======Used Variable
String shortMonth[12] = {"Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Ags", "Sep", "Okt", "Nov", "Des"};
String longMonth[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
unsigned int time_second = 0;
unsigned int time_minute = 0;
unsigned int time_hour = 0;
unsigned int time_date = 0;
unsigned int time_month = 0;
unsigned int time_year = 0;
unsigned int long time_now = 0;
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

void TimeRTC() {
  if (!Rtc.IsDateTimeValid())
  {
    if (Rtc.LastError() != 0)
    {
      Serial.print("RTC communications error = ");
      Serial.println(Rtc.LastError());
    }
    else
    {
      Serial.println("RTC lost confidence in the DateTime!");
    }
  }
  RtcDateTime now = Rtc.GetDateTime();
  time_second = now.Second();
  time_minute = now.Minute();
  time_hour = now.Hour();
  time_date = now.Day();
  time_month = now.Month();
  time_year = now.Year();
  time_now = now;
  Sdate = String(time_date) + "/" + String(time_month) + "/" + String(time_year);
  if (time_minute < 10) {
    Stime = String(time_hour) + ".0" + String(time_minute);
  }
  else {
    Stime = String(time_hour) + "." + String(time_minute);
  }

}

void TimeNTP() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  time_second = second(epochTime);
  time_minute = minute(epochTime);
  time_hour = hour(epochTime);
  time_date = day(epochTime);
  time_month = month(epochTime);
  time_year = year(epochTime);
  time_now = epochTime;
  Sdate = String(time_date) + "/" + String(time_month) + "/" + String(time_year);
  if (time_minute < 10) {
    Stime = String(time_hour) + ".0" + String(time_minute);
  }
  else {
    Stime = String(time_hour) + "." + String(time_minute);
  }
}

void TimeSerialPrint() {
  Serial.print(time_now); Serial.print(" | "); Serial.print(Sdate); Serial.print(" | "); Serial.println(Stime);
}

void TimeDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(Sdate); display.print(" "); display.print(Stime);
  if (time_second < 10) {
    display.print(".0");
    display.println(time_second);
  }
  else {
    display.print(".");
    display.println(time_second);
  }
  display.display();
}

void UpdateSensorRandom() {

  Sdo = random(20);
  Sec = random(20);
  Slat = -8.17941;
  Slong = 112.47524;
  Sorp = random(20);
  Sph = random(20);
  Stds = random(20);
  Stemp = random(20);
  Swc = random(20);
  //delay(1000);
  display.setCursor(120, 0); display.print("U"); display.display();
}

void UpdateSensor() {
  String c = Serial1.readStringUntil('\n');
  int addressC = c.indexOf('C');
  int addressD = c.indexOf('D');
  int addressG = c.indexOf('G');
  int addressH = c.indexOf('H');
  int addressI = c.indexOf('I');
  int addressJ = c.indexOf('J');
  int addressK = c.indexOf('K');
  int addressEnd = c.indexOf(';');
  Sdo = c.substring(addressC + 1, addressD).toInt();
  Sec = c.substring(addressD + 1, addressG).toInt();
  Sorp = c.substring(addressG + 1, addressH).toInt();
  Sph = c.substring(addressH + 1, addressI).toInt();
  Stds = c.substring(addressI + 1, addressJ).toInt();
  Stemp = c.substring(addressJ + 1, addressK).toInt();
  Swc = c.substring(addressK + 1, addressEnd).toInt();
  display.setCursor(120, 0); display.print("U"); display.display();

}


void PrintSensor() {
  Serial.print(Sdo); Serial.print(",");
  Serial.print(Sec); Serial.print(",");
  Serial.print(Sorp); Serial.print(",");
  Serial.print(Sph); Serial.print(",");
  Serial.print(Stds); Serial.print(",");
  Serial.print(Stemp); Serial.print(",");
  Serial.print(Swc); Serial.println("");
}

void UpdateLastDatabase() {
  Serial.println("Last Data Update !!!");
  //display.setCursor(120, 0);display.print("U");
  display.setCursor(0, 10); display.print("a");  Firebase.setString(fbdo, "/last-data/kapal-1/date", Sdate) ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(0, 20); display.print("b");  Firebase.setString(fbdo, "/last-data/kapal-1/time", Stime) ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(15, 10); display.print("c"); Firebase.setInt(fbdo,   "/last-data/kapal-1/do",   Sdo)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(15, 20); display.print("d"); Firebase.setInt(fbdo,   "/last-data/kapal-1/ec",   Sec)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(30, 10); display.print("e"); Firebase.setInt(fbdo,   "/last-data/kapal-1/lat",  Slat)  ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(30, 20); display.print("f"); Firebase.setInt(fbdo,   "/last-data/kapal-1/long", Slong) ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(45, 10); display.print("g"); Firebase.setInt(fbdo,   "/last-data/kapal-1/orp",  Sorp)  ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(45, 20); display.print("h"); Firebase.setInt(fbdo,   "/last-data/kapal-1/ph",   Sph)   ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(60, 10); display.print("i"); Firebase.setInt(fbdo,   "/last-data/kapal-1/tds",  Stds)  ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(60, 20); display.print("j"); Firebase.setInt(fbdo,   "/last-data/kapal-1/temp", Stemp) ? display.print("v") : display.print("x"); delay(100); display.display();
  display.setCursor(75, 10); display.print("k"); Firebase.setInt(fbdo,   "/last-data/kapal-1/wc",   Swc)   ? display.print("v") : display.print("x"); delay(100); display.display();
}

void UpdateRealtimeDatabase() {
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

void setup() {
  pinMode(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  display.display();
  delay(100);

  //======WIFI INIT
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

  //=======NTP INIT
  timeClient.begin();

  //=======FIREBASE INIT
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(6);

  //=======NTP INIT
  timeClient.begin();

  /*//=======RTC INIT
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
    if (!Rtc.IsDateTimeValid())
    {
    if (Rtc.LastError() != 0)
    {
      // we have a communications error
      // see https://www.arduino.cc/en/Reference/WireEndTransmission for
      // what the number means
      Serial.print("RTC communications error = ");
      Serial.println(Rtc.LastError());
    }
    else
    {
      // Common Causes:
      //    1) first time you ran and the device wasn't running yet
      //    2) the battery on the device is low or even missing
      Serial.println("RTC lost confidence in the DateTime!");
      // following line sets the RTC to the date & time this sketch was compiled
      // it will also reset the valid flag internally unless the Rtc device is
      // having an issue
      Rtc.SetDateTime(compiled);
    }
    }

    if (!Rtc.GetIsRunning())
    {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
    }
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled)
    {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
    }
    else if (now > compiled)
    {
    Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled)
    {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
    // never assume the Rtc was last configured by you, so
    // just clear them to your needed state
    Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low);
  */
}

void loop() {
  //TimeRTC();

  TimeNTP();
  TimeDisplay();
  //TimeSerialPrint();

  if (Serial1.available() > 0) {
    UpdateSensor();
    //PrintSensor();
  }

  if ((millis() - sendDataPrevMillis3 > 1000 * 1 || sendDataPrevMillis3 == 0)) {
    sendDataPrevMillis3 = millis();
    bool newData = false;
    unsigned long chars;
    unsigned short sentences, failed;
    while (Serial2.available())
    {
      char c = Serial2.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
    if (newData)
    {
      float flat, flon;
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
      Serial.print("LAT=");
      Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
      Serial.print(" LON=");
      Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      Serial.print(" SAT=");
      Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
      Serial.print(" PREC=");
      Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
      display.setCursor(110, 0); display.print("G"); display.display();
      Slat = flat; Slong = flon;
    }
    gps.stats(&chars, &sentences, &failed);
    Serial.print(" CHARS=");
    Serial.print(chars);
    Serial.print(" SENTENCES=");
    Serial.print(sentences);
    Serial.print(" CSUM ERR=");
    Serial.println(failed);
    if (chars == 0)
      Serial.println("** No character");
  }

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 60000 * 5 || sendDataPrevMillis == 0)){
  //if (Firebase.ready() && (millis() - sendDataPrevMillis > 3000 || sendDataPrevMillis == 0)){
    display.clearDisplay();
    sendDataPrevMillis = millis();
    display.setCursor(0, 0); display.print("Sending to Last - DB"); UpdateLastDatabase(); display.clearDisplay();
    display.setCursor(0, 0); display.print("Sending to RT - DB"); UpdateRealtimeDatabase(); display.clearDisplay();
  }

  delay(500);

}



#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
  char datestring[20];
  snprintf_P(datestring,
             countof(datestring),
             PSTR(" % 02u / % 02u / % 04u % 02u: % 02u: % 02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  //Serial.println(datestring);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(datestring);
}
