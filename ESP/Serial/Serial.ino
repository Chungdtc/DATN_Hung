#include <SerialCommand.h>
#include <SoftwareSerial.h>
const byte RX = D1;
const byte TX = D2;
SoftwareSerial mySerial(RX, TX); 
SerialCommand sCmd(mySerial);

SerialCommand SCmd;
void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);
  SCmd.addCommand("LED", led);
  
}
void loop(){
  SCmd.readSerial();
}



void led() {
  char *arg = SCmd.next();
  int i= atoi(arg);
  if(i==15){
    Serial.println("Da nhan duoc");
  }
}
