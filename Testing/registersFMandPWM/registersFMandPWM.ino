//pwm output
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//https://www.youtube.com/watch?v=nXl4fb_LbcI&t=837s
#include <SPI.h>

//setting up pwm
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

unsigned long timeNow;
unsigned long freqs[16] = {100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600}; //mHz
unsigned long deltaMicros[16];

//
long randPWM;
boolean isOn;

uint8_t isOn0 = B00000000;
uint8_t isOn1 = B00000000;

void setup() {
  SPIcomm_setup();

  Serial.begin(9600);

  //gain for testing purposes
  double freqGain = 10;
  
  for(int i = 0; i < 16; i++){
    //calculating bit flip interval value for each freq value. Assuming 50% duty cycle
    if(freqs[i] == 0){
      //no freq
      deltaMicros[i] = 0;
    }else{
      //calculating delta t between flips
      deltaMicros[i] = pow(freqs[i]*freqGain,-1)*1000000000/2;
    }
  }

  //setting pwm
  pwm.setOscillatorFrequency(27000000);
  pwm.begin();
  pwm.setPWMFreq(60);
  Wire.setClock(400000);
  isOn = 1;
}

void loop() {

  //getting which bits should flip
  uint16_t out = calculateOut(deltaMicros);

  //applying
  isOn0 = out&0xff;
  isOn1 = out>>8;
  
  SPI.begin();
  SPI.transfer(isOn0);
  SPI.transfer(isOn1);
  SPI.end();

  digitalWrite(SS,HIGH);
  delayMicroseconds(1);
  digitalWrite(SS,LOW);

  randPWM = random(0,4096);
  pwm.setPWM(0,0,4095*isOn);
  isOn = !isOn;
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

uint16_t calculateOut(unsigned long *deltaMicros_in){
  timeNow = micros();

  uint16_t output = 0;
  unsigned long delta;

  for(int i = 0; i<16; i++){
    delta = deltaMicros_in[i];
    if(delta == 1){
      //values of 1 = const on
      output = (1 << i) | output;
    }
    else if(delta != 0 && timeNow%delta*2 < delta){
      //in lower half of delta, and delta != 0, flip
      output = (1 << i) | output;
    }
  }
  return output;
}
