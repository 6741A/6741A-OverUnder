#include "vex.h"
#include "Intake.h"

using namespace vex;

void Intake::EnableIntake() {

  IntakeMotor.spin(forward, 100, percent);
}

void Intake::ReverseIntake() {

  IntakeMotor.spin(reverse, 100, percent);
}

void Intake::DisableIntake() {

  IntakeMotor.stop();
}

void Intake::ExtendIntake() {

  IntakePistonLeft = true;
  IntakePistonRight = true;
}

void Intake::RetractIntake() {

  IntakePistonLeft = false;
  IntakePistonRight = false;
}