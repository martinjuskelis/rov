#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 0x04

// define motor pins
byte pin_forwLeft = 11;
byte pin_forwRight = 10;
byte pin_vertLeft = 9;
byte pin_vertRight = 6;

// start servos
Servo forwLeft;
Servo forwRight;
Servo vertLeft;
Servo vertRight;

void setup()
{
  //Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);      // join i2c bus with address #4
  Wire.onReceive(receiveEvent);   // register event

    // attatch all the motors to their pins
  forwLeft.attach(pin_forwLeft);
  forwRight.attach(pin_forwRight);
  vertLeft.attach(pin_vertLeft);
  vertRight.attach(pin_vertRight);

  // set all the motors to an off state
  forwLeft.writeMicroseconds(1500);
  forwRight.writeMicroseconds(1500);
  vertLeft.writeMicroseconds(1500);
  vertRight.writeMicroseconds(1500);

  delay(1000); // delay to allow the ESC to recognize the stopped signal
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    int x = Wire.read();    // read one character from the I2C
    motor(x);
  }
}


void motor(int x) {
  static byte mot = 0;    // create a number that will rememember its last value
  if (x == 0) {
    mot = 0;
    return;
  }
  int state = (x - 64) * 400 / 63 + 1500;    //convert from 0-127 to 1100-1900
  //Serial.print(state);
  //Serial.print("\n");
    // iterate to next motor after every signal
  switch (mot) {
  case 0:
    forwLeft.writeMicroseconds(state);
    mot = 1;
    break;

  case 1:
    forwRight.writeMicroseconds(state);
    mot = 2;
    break;
  case 2:

    vertLeft.writeMicroseconds(state);
    mot = 3;
    break;

  case 3:
    vertRight.writeMicroseconds(state);
    mot = 0;
    break;
  }
}

void loop() {
  delay(100);
}

