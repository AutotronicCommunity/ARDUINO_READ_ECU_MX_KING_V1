/* =============================
   PROGRAM READ ECU MX KING V1
   INFORMATION:
   Pin D2 => Tx ECU
   Pin D3 => rx ECU
   Pin CNVss ECU => +5V
   Pin Clk ECU => Gnd
   =============================*/
   
#include<SoftwareSerial.h>
SoftwareSerial MxKing(2,3); //Rx = D2 dan Tx = D3

int isRead = 0;
int Hitung = 0;

void initMx(){
   for(int i=0; i<16; i++) {
          MxKing.write((byte) 0);
          delay(40);
   }
}

void setBaudrate(){
   MxKing.write(178);
   Serial.begin(38400);
   MxKing.begin(38400);
   delay(100);
}

void unlockIDCode(){
   MxKing.write(251);
   delay(100);
   MxKing.write(245);
   MxKing.write(223);
   MxKing.write(255);
   MxKing.write(15);
   MxKing.write(7);
   MxKing.write(188);
   MxKing.write(222);
   MxKing.write(173);
   MxKing.write(221);
   MxKing.write(212);
   MxKing.write(129);
   MxKing.write(137); 
   delay(100);
   MxKing.write(112);
   delay(100);
}

void readMxKingV1(){
  MxKing.write(80);
  delay(50);
  for(int i=0xE80; i<= 0xEFF; i++) {
    MxKing.write(255);
    MxKing.write(i && 0xFF);
    MxKing.write(i / 0x100);
    delay(100);
  }
}


void setup() {
 Serial.begin(9600);
 MxKing.begin(9600);
 initMx();
 setBaudrate();
 unlockIDCode();
 readMxKingV1();
 isRead = 1;
}

void loop() {
  if (MxKing.available() > 0 ) {
    if (isRead==1){
      if (Hitung < 16){
        Serial.print(MxKing.read(),HEX);
        Serial.print(" ");
        Hitung++;
      }

      if (Hitung == 16){
        Serial.println("");
        Hitung=0;
      }
    } 
  }  
}
