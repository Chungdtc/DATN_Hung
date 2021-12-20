#include <SoftwareSerial.h>
#include <SerialCommand.h>
#define rx 11
#define tx 12
SoftwareSerial mySerial(rx,tx);

void setup(){
  Serial.begin(9600);
  mySerial.begin(115200);
 
}

void loop() {
  delay(500);
  int i=5;
  mySerial.print("LED\r\n");
//  delay(500);
//  mySerial.print("LED ");mySerial.print(i*3);mySerial.print("\r\n");
  if(mySerial.available()){
    Serial.print(char(mySerial.read()));
  }
}
