//https://forum.arduino.cc/index.php?topic=482567.0

//OUTPUTS
const int stepPin = 4;
const int dirPin = 3;
const int torqueControllPin = 5;

//initial delay
int delta = 1;

int numOnSpeed = 5;

int maxHalf = 700;
int minHalf = 100;

void setup(){
  pinMode(stepPin, OUTPUT); 
  digitalWrite (13, HIGH);
  pinMode(dirPin, OUTPUT);
  digitalWrite (dirPin, HIGH);
  pinMode(torqueControllPin, OUTPUT);
}

void loop(){

  
  //full torque
  if (false){
    maxHalf = 700;
    minHalf = 100;
    analogWrite(torqueControllPin,255);
    accel_decel();
    PIND = PIND | (1 << (dirPin));
    accel_decel();
    PIND = PIND | (1 << (dirPin));
  }

  //3/4
  if (false){
    maxHalf = 700;
    minHalf = 150;
    analogWrite(torqueControllPin,255 *3/4);
    accel_decel();
    PIND = PIND | (1 << (dirPin));
    accel_decel();
    PIND = PIND | (1 << (dirPin));
  }

  //1/2
  if (false){
    maxHalf = 700;
    minHalf = 200;
    analogWrite(torqueControllPin,255/2);
    accel_decel();
    PIND = PIND | (1 << (dirPin));
    accel_decel();
    PIND = PIND | (1 << (dirPin));
  }

  //1/4
  if (false){
    maxHalf = 700;
    minHalf = 300;
    analogWrite(torqueControllPin,255/4);
    accel_decel();
    PIND = PIND | (1 << (dirPin));
    accel_decel();
    PIND = PIND | (1 << (dirPin));
  }

  //10%
  if (false){
    maxHalf = 1000;
    minHalf = 500;
    analogWrite(torqueControllPin,255*0.1);
    accel_decel();
    PIND = PIND | (1 << (dirPin));
    accel_decel();
    PIND = PIND | (1 << (dirPin));
  }

  //5%
  if (true){
    maxHalf = 1000;
    minHalf = 500;
    analogWrite(torqueControllPin,255*0.05);
    accel_decel();
    PIND = PIND | (1 << (dirPin));
    accel_decel();
    PIND = PIND | (1 << (dirPin));
  }
  
}

void accel_decel(){
  int halfPeriod = maxHalf;
  
  while (halfPeriod >= minHalf){
    for (int i = 0; i < numOnSpeed; i++){
      PIND = PIND | (1 << (stepPin));
      delayMicroseconds(halfPeriod);
    }
    halfPeriod = halfPeriod - delta;
  }

  while (halfPeriod <= maxHalf){
    for (int i = 0; i < numOnSpeed; i++){
      PIND = PIND | (1 << (stepPin));
      delayMicroseconds(halfPeriod);
    }
    halfPeriod = halfPeriod + delta;
  }
}
