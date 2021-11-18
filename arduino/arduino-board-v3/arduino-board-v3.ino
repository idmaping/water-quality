//======INCLUDE
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#define fs1 A0
#define fs2 A1
#define fs3 A3
#define fs4 A4
#define fs5 A5
#define fs6 A6
#define sensVolt A2
#include <Servo.h>
#include <SimpleKalmanFilter.h>
#define reelD 6
#define reelPWM 7
#define pumpA 4
#define pumpB 5


const int STEERTRIMMER = 100;

//======PRE-INIT
RTC_DS3231 rtc;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int chipSelect = 53;
TinyGPS gps;
SoftwareSerial fb(63, 62); // A8 RX, A9 TX

SimpleKalmanFilter kalmanSteer(1, 1, 0.01);
SimpleKalmanFilter kalmanThrottle(1, 1, 0.01);

Servo servoSteer;
Servo servoThrottle1;
Servo servoThrottle2;



//======VAR
unsigned long refreshTime1 = 0;
unsigned long refreshTime2 = 0;
unsigned long refreshTime3 = 0;
unsigned long refreshTime4 = 0;

int valfsA = 0;
int valfsB = 0;
int valfsC = 0;
int valfsD = 0;
int valfsE = 0;
int valfsF = 0;

int throttle = 0;
int est_throttle = 0;
int steer = 0;
int est_steer = 0;


File myFile;
String shortMonth[12] = {"Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Ags", "Sep", "Okt", "Nov", "Des"};
String longMonth[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
unsigned int time_second = 0;
unsigned int time_minute = 0;
unsigned int time_hour = 0;
unsigned int time_date = 0;
unsigned int time_month = 0;
unsigned int time_year = 0;
unsigned int time_temp = 0;
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
String Sinfo = "";
float vin = 0.0;
float deepth = 0.0;
bool mode = 0; //0=DRIVE MODE 1=REEL MODE
int reel = 0; //0=stop -=tarik +=turuni
int statRs = 0; //Receiver Sensor 0:standby 1:send command 2:get data
int statSd = 0; //Serial 0:standby 1:send -1:failed
int statFb = 0; //Firebase 0:standby 1:send -1:failed
int statGps = 0; //Firebase 0:standby 1:send -1:failed

void FS_Read() {

  map(constrain(pulseIn(fs5, HIGH), 1000, 1900), 1000, 1900, 0, 100) > 50 ? mode = 0 : mode = 1;

  steer = 100;
  throttle = 0;

  if (mode == 0) { //DRIVE
    throttle = map(constrain(pulseIn(fs3, HIGH), 1000, 1900), 1000, 1900, 0, 100);
    steer = map(constrain(pulseIn(fs1, HIGH), 1100, 1900), 1100, 1900, 85, 115);
    //servoSteer.write(steer);

    //Serial.println(pulseIn(fs1, HIGH));

  } else {
    //valfsA = map(constrain(pulseIn(fs1, HIGH), 1040, 1900), 1040, 1900, -100, 100);

    //valfsC = map(constrain(pulseIn(fs3, HIGH), 1000, 1900), 1000, 1900, 0, 100);
    //valfsD = map(constrain(pulseIn(fs4, HIGH), 1000, 1900), 1000, 1900, -100, 100);

    valfsF = map(constrain(pulseIn(fs6, HIGH), 1000, 1900), 1000, 1900, 0, 100);
    if (valfsF < 30) {
      

      reel = 0;
      digitalWrite(reelD,HIGH);
      digitalWrite(reelPWM,HIGH);
    }
    else if (valfsF > 80) {
      reel = +255;
      digitalWrite(reelD,HIGH);
      analogWrite(reelPWM,255-abs(reel));
    }
    else if (valfsF > 30 && valfsF < 80) {
      reel = -255;
      digitalWrite(reelD,LOW);
      analogWrite(reelPWM,abs(reel));
    }

    valfsB = map(constrain(pulseIn(fs2, HIGH), 1000, 1900), 1000, 1900, 100, -100);
    if (abs(valfsB) > 30) {
      reel += valfsB;
    }

  }

  //valfsA = pulseIn(fs1, HIGH);
  //valfsB = map(constrain(pulseIn(fs2, HIGH), 1000, 1900), 1000, 1900, -100, 100);
  //valfsC = map(constrain(pulseIn(fs3, HIGH), 1000, 1900), 1000, 1900, 0, 100);
  //valfsD = map(constrain(pulseIn(fs4, HIGH), 1000, 1900), 1000, 1900, -100, 100);
  //valfsF = map(constrain(pulseIn(fs6, HIGH), 1000, 1900), 1000, 1900, 0, 100);

  //valfsE > 50?mode=1:mode=0;

  //Serial.print(valfsA);Serial.println(",");
  //Serial.print(valfsB);Serial.print(",");
  //Serial.print(valfsC);Serial.print(",");
  //Serial.print(valfsD);Serial.print(",");
  //Serial.print(valfsE);Serial.print(",");
  //Serial.print(valfsF);Serial.print(",");
  //Serial.println("");
}

void DISP_Show() {
  display.clearDisplay(); display.setTextColor(SSD1306_WHITE);

  //DATE
  display.setCursor(0, 0);
  display.print(time_date / 10); display.print(time_date % 10);
  //display.print(time_month/10);display.print(time_month%10);display.print("/");
  display.print(shortMonth[time_month]);
  display.print(time_year % 2000);

  //TIME
  display.setCursor(92, 0); display.print(time_hour / 10); display.print(time_hour % 10);
  time_second % 2 == 0 ? display.print(":") : display.print(" ");
  display.print(time_minute / 10); display.print(time_minute % 10);

  //temp
  display.setCursor(0, 10); display.print("T:" + String(time_temp) + "C");
  //volt
  display.setCursor(35, 10); display.print("V:" + String(vin, 1) + "v");
  //reels
  display.setCursor(80, 10); display.print("D:" + String(deepth, 1) + "m");

  //GPS
  display.setCursor(0, 20); display.print("GPS:" + String(Slat) + " " + String(Slong));
  if (statGps == 1) {
    display.print(" Upd");
  }
  else if (statGps == -1) {
    display.print("Fall"); //update gps
  }

  //upRs
  if (statRs == 1) {
    display.setCursor(80, 50);  //receive from sensor
    display.print("rs");
  }
  else if (statRs == 2) {
    display.setCursor(80, 50);  //receive from sensor
    display.print("rs");
  }

  //upSd
  if (statSd == 1) {
    display.setCursor(95, 50);  //log to sdcard
    display.print("sd");
  }

  //upFb
  if (statFb == 1) {
    display.setCursor(110, 50);  //send to firebase
    display.print("fb");
  }

  //CHANNEL MODE
  if (mode == 0) {
    display.fillRect(50, 0, 24, 9, SSD1306_WHITE);
    display.setTextColor(SSD1306_INVERSE);
    display.setCursor(54, 1); display.print("DRV");

    display.setCursor(0, 30);   display.print("Tht"); display.drawRect(20, 30, 40, 8, SSD1306_WHITE);
    display.fillRect(21, 30, map(est_throttle, 0, 180, 1, 38), 8, SSD1306_WHITE);
    if (throttle > est_throttle) {
      display.drawLine(map(throttle, 0, 180, 21, 60), 30, map(throttle, 0, 180, 21, 60), 37, SSD1306_WHITE);
    }
    else {
      display.drawLine(map(throttle, 0, 180, 21, 60), 32, map(throttle, 0, 180, 21, 60), 36, SSD1306_INVERSE);
    }

    display.setCursor(105, 30); display.print("Str"); display.drawRect(62, 30, 40, 8, SSD1306_WHITE);
    if (est_steer > STEERTRIMMER) {
      display.fillRect(80, 30, map(est_steer, 90, 180, 1, 21), 8, SSD1306_WHITE);
      steer > est_steer ? display.drawLine(map(steer, 0, 180, 62, 100), 32, map(steer, 0, 180, 62, 100), 36, SSD1306_WHITE) : display.drawLine(map(steer, 0, 180, 62, 100), 32, map(steer, 0, 180, 62, 100), 36, SSD1306_INVERSE);
    }
    else if (est_steer < STEERTRIMMER) {
      display.fillRect(map(est_steer, 0, 90, 62, 80), 30, map(est_steer, 0, 90, 20, 1), 8, SSD1306_WHITE);
      steer < est_steer ? display.drawLine(map(steer, 0, 180, 62, 100), 32, map(steer, 0, 180, 62, 100), 36, SSD1306_WHITE) : display.drawLine(map(steer, 0, 180, 62, 100), 32, map(steer, 0, 180, 62, 100), 36, SSD1306_INVERSE);
    }


  } else {
    display.drawRect(50, 0, 24, 9, SSD1306_WHITE);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(54, 1); display.print("MSR");

    display.setCursor(0, 30); display.print("C:"); display.print(Sdo);
    display.setCursor(0, 40); display.print("D:"); display.print(Sec);
    display.setCursor(0, 50); display.print("G:"); display.print(Sorp);
    display.setCursor(40, 30); display.print("H:"); display.print(Sph);
    display.setCursor(40, 40); display.print("I:"); display.print(Stds);
    display.setCursor(40, 50); display.print("J:"); display.print(Stemp);
    display.setCursor(80, 30); display.print("K:"); display.print(Swc);

    display.setCursor(80, 40);
    if (reel == 0) {
      display.write(0x07);
    }
    else if (reel < 0) {
      display.write(0x1E);
      display.print(" ");
      display.print(abs(reel));
    }
    else if (reel > 0) {
      display.write(0x1F);
      display.print(" ");
      display.print(abs(reel));
    }

  }

  //display.setCursor(0, 30);   display.print("Ch3"); display.drawRect(20,30,40,8,SSD1306_WHITE); display.fillRect(21,30,map(valfsC,0,100,1,38),8,SSD1306_WHITE); //38
  //display.setCursor(0, 40);   display.print("Ch4"); display.drawRect(20,40,40,8,SSD1306_WHITE); display.drawLine(map(valfsD,-100,100,21,58), 40, map(valfsD,-100,100,21,58), 47, SSD1306_WHITE);
  //display.setCursor(105, 30); display.print("Ch1"); display.drawRect(62,30,40,8,SSD1306_WHITE); display.drawLine(map(valfsA,-100,100,63,100),30, map(valfsA,-100,100,63,100),37, SSD1306_WHITE);
  //display.setCursor(105, 40); display.print("Ch2"); display.drawRect(62,40,40,8,SSD1306_WHITE); display.drawLine(map(valfsB,-100,100,63,100),40, map(valfsB,-100,100,63,100),47, SSD1306_WHITE);

  display.display();
}

void FS_Write() {


  est_throttle = kalmanThrottle.updateEstimate(throttle);
  est_steer = kalmanSteer.updateEstimate(steer);

  

  if (mode == 0) {
    //servoSteer.write(est_steer);

    if(steer<STEERTRIMMER-10){servoSteer.write(STEERTRIMMER-15);}
    else if(steer>STEERTRIMMER+10){servoSteer.write(STEERTRIMMER+15);}
    else{servoSteer.write(STEERTRIMMER);}
    
    
    servoThrottle1.write(est_throttle);
    servoThrottle2.write(est_throttle);

    if(est_throttle > 10){
      digitalWrite(pumpA,HIGH);digitalWrite(pumpB,LOW);
    }
    else{
      digitalWrite(pumpA,LOW);digitalWrite(pumpB,LOW);
    }
    
  }
  else {
    servoSteer.write(STEERTRIMMER);
    servoThrottle1.write(0);
    servoThrottle2.write(0);
    digitalWrite(pumpA,LOW);
    digitalWrite(pumpB,LOW);
  }

  //servoSteer.write(90);




  //Serial.print(throttle); Serial.print(","); Serial.println(est_throttle);
  //Serial.print(steer);Serial.print(",");Serial.println(est_steer);



}

void RTC() {
  DateTime now = rtc.now();
  time_second = now.second();
  time_minute = now.minute();
  time_hour = now.hour();
  time_date = now.day();
  time_month = now.month();
  time_year = now.year();
  time_now = now.unixtime();
  time_temp = rtc.getTemperature();
  Sdate = String(time_date) + "/" + String(time_month) + "/" + String(time_year);

  if (time_hour < 10) {
    if (time_minute < 10) {
      Stime = "0" + String(time_hour) + ".0" + String(time_minute);
    }
    else {
      Stime = "0" + String(time_hour) + "." + String(time_minute);
    }
  } else {
    if (time_minute < 10) {
      Stime = String(time_hour) + ".0" + String(time_minute);
    }
    else {
      Stime = String(time_hour) + "." + String(time_minute);
    }
  }


  vin = analogRead(sensVolt);
  vin = (vin * 5) / 1024.0;
  vin = vin / (7500.0 / (7500.0 + 30000.0));

  //Reset Status
  statFb = 0;
  statRs = 0;
  statSd = 0;
  statGps = 0;

  //======INFO
  Sinfo = "Proc OK;";
  if (time_temp > 60) {
    Sinfo += "Proc OH;";
  }

}

void SD_Write() {
  String dataString = Sdate + "," + Stime + ",";
  dataString += String(Slat, 6) + "," + String(Slong, 6);
  dataString += "," + String(Sdo) + "," + String(Sec);
  dataString += "," + String(Sorp) + "," + String(Sph);
  dataString += "," + String(Stds) + "," + String(Stemp);
  dataString += "," + String(Swc) + "," + String(Sinfo);

  if (SD.exists("DATALOG.csv")) { // check the card is still there
    // now append new data file
    myFile = SD.open("DATALOG.csv", FILE_WRITE);
    if (myFile) {
      myFile.println(dataString);
      myFile.close(); // close the file
      //display.setCursor(CURSOR_SD + 17, 10); display.print("V"); display.display(); delay(100);
      //Serial.println(dataString);
      statSd = 1;
    }
  }
  else {
    statSd = -1;
  }
}

void GPS_Get() {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  // For one second we parse GPS data and report some key values
  for (unsigned long refreshTime2 = millis(); millis() - refreshTime2 < 200;)
  {
    while (Serial3.available())
    {
      char c = Serial3.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);

    flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat; //LAT
    flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon; //LONG
    gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites(); //SAT
    gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop(); //PREC
    Slat = flat; Slong = flon;
    statGps = 1;
  }
  gps.stats(&chars, &sentences, &failed);
  if (chars == 0) {
    //Serial.println("** No characters received from GPS: check wiring **");
    statGps = -1;
  }
}

void FB_SendDBRT() {

  String dataString = "Z1A" + Sdate + "B" + Stime;
  dataString += "C" + String(Sdo) + "D" + String(Sec);
  dataString += "E" + String(Slat, 5) + "F" + String(Slong, 5);
  dataString += "G" + String(Sorp) + "H" + String(Sph);
  dataString += "I" + String(Stds) + "J" + String(Stemp);
  dataString += "K" + String(Swc);
  dataString += "L" + String(time_temp);
  dataString += "M" + String(vin,2);
  dataString += "N" + String(deepth,2);
  dataString += "T" + String(time_now) + ";";
  

  Serial.println(dataString);

  fb.println(dataString);
  statFb = 1;
}

void FB_SendLastData() {
  String dataString = "Z0A" + Sdate + "B" + Stime;
  dataString += "C" + String(Sdo) + "D" + String(Sec);
  dataString += "E" + String(Slat, 5) + "F" + String(Slong, 5);
  dataString += "G" + String(Sorp) + "H" + String(Sph);
  dataString += "I" + String(Stds) + "J" + String(Stemp);
  dataString += "K" + String(Swc);
  dataString += "L" + String(time_temp);
  dataString += "M" + String(vin,2);
  dataString += "N" + String(deepth,2);
  dataString += "T" + String(time_now) + ";";
  

  //Serial.println(dataString);

  fb.println(dataString);
  statFb = 1;
}




void setup() {

  Serial.begin(115200);
  //Serial.println("Ro-Boat");
  Serial3.begin(9600);

  //=========FB
  fb.begin(115200);

  //=========FLYSKY
  pinMode(fs1, INPUT); pinMode(fs2, INPUT); pinMode(fs3, INPUT);
  pinMode(fs4, INPUT); pinMode(fs5, INPUT); pinMode(fs6, INPUT);

  //=========VOLTMETER
  pinMode(sensVolt, INPUT);

  //=========OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  //=========RTC
  display.setCursor(0, 0); display.print("Init RTC"); display.display(); delay(500);
  if (! rtc.begin())
  {
    display.println(" X"); display.display();
    Serial.flush();
    abort();
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (rtc.lostPower()) {
    display.println(" Lo"); display.display();
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  display.print(" V"); display.display(); delay(500);//Serial.println("OkRTC");
  RTC();

  //=========CARD READER
  display.setCursor(0, 10); display.print("Init Card"); display.display(); delay(500);
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    display.print(" X"); display.display();
    // don't do anything more:
    while (1) ;
  }
  display.println(" V"); display.display(); delay(500);
  display.setCursor(0, 20); display.print("Init File"); display.display(); delay(500);
  myFile = SD.open("DATALOG.csv", FILE_WRITE);
  myFile.close(); delay(1000);
  if (SD.exists("DATALOG.csv")) {
    display.print(" V");
    //Serial.println("OkSd");
    display.display();
    delay(500);
  }
  else {
    display.print(" X please reset");
    //Serial.println("NoSd");
    display.display();
    while (1);
  }
  

  //=========SERVO
  servoSteer.attach(12);
  servoThrottle1.attach(11, 1000, 1900);
  servoThrottle2.attach(10, 1000, 1900);

  //=========REEL
  pinMode(reelD,OUTPUT);
  pinMode(reelPWM,OUTPUT);
  pinMode(pumpA,OUTPUT);
  pinMode(pumpB,OUTPUT);



}
void loop() {
  FS_Read();

  if ((millis() - refreshTime3 > 100 * 1 || refreshTime3 == 0)) {
    refreshTime3 = millis();
    DISP_Show();
  }
  if ((millis() - refreshTime1 > 1000 * 1 || refreshTime1 == 0)) {
    refreshTime1 = millis();
    RTC();
  }
  if ((millis() - refreshTime4 > 5000 * 1 || refreshTime4 == 0)) {
    refreshTime4 = millis();
    GPS_Get();
  }

  FS_Write();

  if ((millis() - refreshTime2 > 5000 * 1 || refreshTime2 == 0)) {
    refreshTime2 = millis();
    if (mode == 0) {
      FB_SendLastData();
    }
    else {
      SD_Write();
      FB_SendDBRT();
    }
  }





}
