// from https://www.youtube.com/watch?time_continue=456&v=5CmjB4WF5XA

//OUTPUTS
const int stepPin = 4;
const int dirPin = 3;
const int torqueControllPin = 5;

//INPUTS
const int speedPin = A0;
const int torqueReadPin = A1;

//CALIBRATION
const int SPEED_MAX = 1023;
const int TORQUE_MAX = 837;

const float LOW_SPEED = 10;
const float HIGH_SPEED = 2;
const int LOW_TORQUE = 0;
const int HIGH_TORQUE = 255; //max 255



void setup() {
  //Setting up serial communication
  Serial.begin(9600);

  //output pins
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(torqueControllPin, OUTPUT);
//  setPwmFrequency(torqueControllPin, 1024);

  //input pins
  pinMode(speedPin, INPUT);
  pinMode(torqueReadPin, INPUT);
}

int iter = 0;
void loop() {
  //reading inputs
  float speedVal = analogRead(speedPin);
  int torqueVal = analogRead(torqueReadPin);

//  Serial.print("\n************************\n");
//  Serial.print(speedVal);
  
  //Mapping inputs
  //direction
  boolean dir = speedVal > (SPEED_MAX/2);

  //speed
  if (speedVal > SPEED_MAX){
    speedVal = SPEED_MAX;
  }
  speedVal = abs(speedVal - SPEED_MAX/2);
  speedVal = map(speedVal, 0, SPEED_MAX/2, LOW_SPEED, HIGH_SPEED);
  if (speedVal < HIGH_SPEED){
    speedVal = HIGH_SPEED;
  }

  //torque
  if (torqueVal > TORQUE_MAX){
    torqueVal = TORQUE_MAX;
  }
  torqueVal = map(torqueVal, 0, TORQUE_MAX, LOW_TORQUE, HIGH_TORQUE);

  iter += 1;
  if (iter %200 == 0){
    
//    Serial.print("************************");
//    Serial.print("\nDirection (0-1): ");
//    Serial.print(dir);
//    Serial.print("\ntorque (0-255): "); 
//    Serial.print(torqueVal);
//    Serial.print("\ndelay (LOW-HIGH): "); 
//    Serial.print(speedVal);
  }

  digitalWrite(dirPin, dir);
  analogWrite(torqueControllPin, torqueVal);
//  analogWrite(torqueControllPin, 255);
  delay(speedVal/2);
  digitalWrite(stepPin,HIGH);
  delay(speedVal/2);
  digitalWrite(stepPin,LOW);
}

//https://playground.arduino.cc/Code/PwmFrequency/
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
