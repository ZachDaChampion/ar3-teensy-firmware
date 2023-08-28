#include <Arduino.h>

#include <AccelStepper.h>
#include <Encoder.h>

#include <pb_common.h>
#include <pb_encode.h>
#include <pb_decode.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}