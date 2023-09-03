
// PID Control Loop Template ~~

#include "vex.h"
#include "PIDTemplate.h"

using namespace vex;

float derivative;
float previousError;
float integral;

float error;

float PIDTemplate::PIDControlLoop(float kP, float kI, float kD, float target, float sensorValue, bool subtraction)
{

  if (subtraction) { error = target - sensorValue; }
  else { error = target + sensorValue; }

  integral += error;

  if (error == 0) { integral = 0; }

  derivative = error - previousError;

  previousError = error;

  float output = (kP * error) + (kI * integral) + (kD * derivative);

  return output;

}
