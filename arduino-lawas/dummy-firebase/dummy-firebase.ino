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

//=======WIFI CONFIG
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

//=======TIME
const long utcOffsetInSeconds = 25200;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);


void setup() {
  pinMode(LED_BUILTIN, HIGH);
  Serial.begin(115200);

  //======WIFI INIT
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


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

}

void loop() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  String Sdate = String(day(epochTime)) + "/" + String(month(epochTime)) + "/" + String(year(epochTime));
  String Stime = String(hour(epochTime)) + "." + String(minute(epochTime));

  Serial.print("ID : "); Serial.println(epochTime);
  Serial.print("date : "); Serial.println(Sdate);
  Serial.print("time : "); Serial.println(Stime);
  Serial.print("Last update : ");
  Serial.print((millis() - sendDataPrevMillis ) / 60000 );
  Serial.println(" minute ago");
  delay(1000);

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 60000*10 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    int Sdo = random(20);
    int Sec = random(20);
    float Slat = -8.17941;
    float Slong = 112.47524;
    int Sorp = random(20);
    int Sph = random(20);
    int Stds = random(20);
    int Stemp = random(20);
    int Swc = random(20);

    Serial.print("UPDATE!!!");
    Serial.printf("date... %s\n", Firebase.setString(fbdo, "/last-data/kapal-1/date", Sdate) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("time... %s\n", Firebase.setString(fbdo, "/last-data/kapal-1/time", Stime) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("do... %s\n", Firebase.setInt(fbdo,   "/last-data/kapal-1/do", Sdo) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("ec... %s\n", Firebase.setInt(fbdo,   "/last-data/kapal-1/ec", Sec) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("lat... %s\n", Firebase.setInt(fbdo,  "/last-data/kapal-1/lat", Slat) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("long... %s\n", Firebase.setInt(fbdo, "/last-data/kapal-1/long", Slong) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("orp... %s\n", Firebase.setInt(fbdo,  "/last-data/kapal-1/orp", Sorp) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("ph... %s\n", Firebase.setInt(fbdo,   "/last-data/kapal-1/ph", Sph) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("tds... %s\n", Firebase.setInt(fbdo,  "/last-data/kapal-1/tds", Stds) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("temp... %s\n", Firebase.setInt(fbdo, "/last-data/kapal-1/temp", Stemp) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("wc... %s\n", Firebase.setInt(fbdo,   "/last-data/kapal-1/wc", Swc) ? "ok" : fbdo.errorReason().c_str());

    Serial.println("REALTIME DB!!!");  
    String ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "date";
    Serial.printf("date... %s\n", Firebase.setString(fbdo, ref, Sdate) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "time";
    Serial.printf("time... %s\n", Firebase.setString(fbdo, ref, Stime) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "do";
    Serial.printf("do... %s\n", Firebase.setInt(fbdo,   ref, Sdo) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "ec";
    Serial.printf("ec... %s\n", Firebase.setInt(fbdo,   ref, Sec) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "lat";
    Serial.printf("lat... %s\n", Firebase.setInt(fbdo,  ref, Slat) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "long";
    Serial.printf("long... %s\n", Firebase.setInt(fbdo, ref, Slong) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "orp";
    Serial.printf("orp... %s\n", Firebase.setInt(fbdo,  ref, Sorp) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "ph";
    Serial.printf("ph... %s\n", Firebase.setInt(fbdo,   ref, Sph) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "tds";
    Serial.printf("tds... %s\n", Firebase.setInt(fbdo,  ref, Stds) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "temp";
    Serial.printf("temp... %s\n", Firebase.setInt(fbdo, ref, Stemp) ? "ok" : fbdo.errorReason().c_str());
    ref = "/dbrt/kapal-1/" + String(year(epochTime)) + "/" + String(month(epochTime)) + "/" + String(day(epochTime)) + "/" + String(epochTime) + "/" + "wc";
    Serial.printf("wc... %s\n", Firebase.setInt(fbdo,   ref, Swc) ? "ok" : fbdo.errorReason().c_str());

  }

}
