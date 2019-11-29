
//https://www.youtube.com/watch?v=nXl4fb_LbcI&t=837s
#include <SPI.h>

void setup() {
  SPIcomm_setup();
  
}

void loop() {

  long delayTime = 100000000;
  
  SPI.begin();
//  SPI.transfer(B00000000);
  digitalWrite(SS,HIGH);
  delayMicroseconds(1);
  digitalWrite(SS,LOW);
  SPI.end();

  delayMicroseconds(delayTime);

  SPI.begin();
  SPI.transfer(B10101010);
  digitalWrite(SS,HIGH);
  delayMicroseconds(1);
  digitalWrite(SS,LOW);
  SPI.end();

  delayMicroseconds(delayTime);

  SPI.begin();
//  SPI.transfer(B11111111);
  digitalWrite(SS,HIGH);
  delayMicroseconds(1);
  digitalWrite(SS,LOW);
  SPI.end();

  delayMicroseconds(delayTime);
  
}

//SPI control constant

void SPIcomm_setup(){

    pinMode(SS, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, OUTPUT);
    
    Serial.begin(9600);
    Serial.print("\nSS:");
    Serial.print(SS);
    Serial.print("\nSCK:");
    Serial.print(SCK);
    Serial.print("\nMOSI:");
    Serial.print(MOSI);
    Serial.print("\nMISO:");
    Serial.print(MISO);

    //defining SPI config
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.begin();
  
}

 
