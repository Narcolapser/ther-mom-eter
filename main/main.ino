#include <Stepper.h>

const int stepsPerRevolution = 1024;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 16, 4, 5, 0);
int stepCount = 0;         // number of steps the motor has taken

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  myStepper.setSpeed(10);
  Serial.print("All setup.");
}

void loop() {
  move(0,512);
  delay(1000);
  move(512,0);
  delay(1000);
}

void move(int from, int to)
{
  int val = to - from;
  if (val > 0)
  {
    while(val > 128)
    {
      myStepper.step(128);
      val -= 128;
      delay(5);
    }
    myStepper.step(val);
  }
  else if (val < 0)
  {
    while(val < -128)
    {
      myStepper.step(-128);
      val += 128;
      delay(5);
    }
    myStepper.step(val);
  }
}

