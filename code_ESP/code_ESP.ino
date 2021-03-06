#include "DHT.h"
#include <SocketIOClient.h>
#include <ESP8266WiFi.h>  
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>  

#define btCleanPIN 0
#define btEatPIN 1
#define DHTPIN 2
#define DADPIN 3
#define DRIVERPIN 4
#define clkPIN 5
#define latchPIN 6
#define dataPIN 7
#define DHTTYPE DHT11

float nd = 0;
int dad = 0; int eat = 0; int clean = 0;

int sttEat = 0; int sttEatPre = 0;
int sttWater = 0; int sttWaterPre = 0;
int sttFan = 0; int sttFanPre = 0;
int sttClean = 0; int sttCleanPre = 0;
int sttLight = 0;

DHT dht(DHTPIN, DHTTYPE);
String host = "192.168.43.165";
int port =3000;


SocketIOClient socket;

//Dinh nghia on
/*************************************************/
void fan(String data) {
  if (data == "0"){
    sttFan = 0;
  }
  if (data == "1"){
    sttFan = 1;
  }
}

void wat(String data) {
  if (data == "0"){
    sttWater = 0;
  }
  if (data == "1"){
    sttWater = 1;
  }
}

void eatDT(String data) {
  if (data == "0"){
    sttEat = 0;
  }
  if (data == "1"){
    sttEat = 1;
  }
}

void cle(String data) {
  if (data == "0"){
    sttClean = 0;
  }
  if (data == "1"){
    sttClean = 1;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(DADPIN,INPUT);

  WiFiManager wifiManager;
  wifiManager.autoConnect("PHONG_KHACH");

  
  dht.begin();
}

void loop() {
  socket.monitor();
  readDHT();
}

//Xử lý nhiệt độ
/**********************************************************************************/
void readDHT() {
  float h = dht.readHumidity();
  if (isnan(h)) {
  }
  else {
    if(h == nd) {
    }
    else {
      nd = h;
      socket.emit("nd", (String)nd);
    }
  }
  if (nd>27) {
    sttFan=1;
  }
  else {
    sttFan=0;
  }
  if (sttFan == sttFanPre) {
  }
  else {
    sttFanPre = sttFan;
    data74HC(sttEat, sttWater, sttFan, sttClean, sttLight);
    socket.emit("fan", (String)sttFan);
  }
}
/**********************************************************************************/

//Xử lý nước uống
/**********************************************************************************/
void readDAD() {
  dad = digitalRead(DADPIN);
  if (dad==0) {
    sttWater=0;
  }
  else {
    sttWater=1;
  }
  if (sttWater == sttWaterPre) {
  }
  else {
    sttWaterPre = sttWater;
    data74HC(sttEat, sttWater, sttFan, sttClean, sttLight);
    socket.emit("wat", (String)sttWater);
  }
}
/**********************************************************************************/

void readBTEat() {
  eat = digitalRead(btEatPIN);
  if(eat == 1) {
    sttEat = 1;
  }
  else {
    sttEat = 0;
  }

  if (sttEat == sttEatPre) {
  }
  else {
    sttEatPre = sttEat;
    socket.emit("eat", (String)sttEat);
    data74HC(sttEat, sttWater, sttFan, sttClean, sttLight);
    actionVan();
  }
}

void readBTClean() {
  clean = digitalRead(btCleanPIN);
  if(clean == 1) {
    sttClean = 1;
  }
  else {
    sttClean = 0;
  }

  if ( sttClean == sttCleanPre ) {
    
  }
  else {
    sttCleanPre = sttClean;
    data74HC(sttEat, sttWater, sttFan, sttClean, sttLight);
    socket.emit("cle",(String)sttClean);
  }
}

//Gửi data ra 73hc5959
/**********************************************************************************/
void data74HC(int a, int b, int c, int d, int e) {
  digitalWrite(latchPIN, LOW);
  sendBit74HC(0);sendBit74HC(0);sendBit74HC(e);sendBit74HC(d);sendBit74HC(c);sendBit74HC(b);sendBit74HC(a);sendBit74HC(0);
  digitalWrite(latchPIN, HIGH);
}
void sendBit74HC(int data) {
  digitalWrite(clkPIN,HIGH);
  if(data == 0){
    digitalWrite(dataPIN, LOW);
  }
  else {
    digitalWrite(dataPIN, HIGH);
  }
  digitalWrite(clkPIN, LOW);
}
/**********************************************************************************/



void actionVan() {
  for (int i=0; i<100; i++) {
      digitalWrite(DRIVERPIN, HIGH);
      delayMicroseconds(500);
      digitalWrite(DRIVERPIN, LOW);
      delayMicroseconds(500);
    }
}
