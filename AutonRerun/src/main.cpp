/*
  INSTRUCTIONS:
  
  1. Have the driver run their route, STEP BY STEP.
  2. After every individual step is complete (e.g. driving forward for x inches), the driver must press X.
  3. Rinse and repeat until the route is finished.
  4. The data written onto the .txt file can then be copy pasted into autonomous.
  The driver's route should then be approximately the same as the following autonomous route.
  Some fine tuning will be required.
  CONTROLS:
  X - Documents values recorded from previous step.
  A - Drives drivetrain forward.
  B - Drives drivetrain backward.
  Left Arrow - Point rotates drivetrain left.
  Right Arrow - Point rotates drivetrain right.
  I've chosen to map controls to buttons rather than joysticks so
  that motor movements are constant. The constant variation that would be recorded
  with joysticks would lead to unnecessary innacuracy.
  The speed of movement is very slow, for better accuracy in data
  recording. 
  */

#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "vex.h"
using namespace vex;

// Brain should be defined by default
brain Brain;
// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))
#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS

// Robot configuration code.
motor leftMotorA = motor(PORT10, ratio18_1, false);
motor leftMotorB = motor(PORT6, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT20, ratio18_1, true);
motor rightMotorB = motor(PORT16, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
gps DrivetrainGPS = gps(PORT5, 0.00, 0.00, mm, 180);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainGPS, 319.19, 320, 40, mm, 1);
controller Controller1 = controller(primary);

void calibrateDrivetrain() {
  wait(200, msec);
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("GPS");
  DrivetrainGPS.calibrate();
  while (DrivetrainGPS.isCalibrating()) {
    wait(25, msec);
  }
  // Clears the screen and returns the cursor to row 1, column 1.
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
#pragma endregion VEXcode Generated Robot Configuration

#include "vex.h"
#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
using namespace vex;

void preAutonomous(void) {
  // Defaults motors stopping to hold.
  leftMotorA.setStopping(hold);
  leftMotorB.setStopping(hold);
  rightMotorA.setStopping(hold);
  rightMotorB.setStopping(hold);
  wait(1, seconds);
}

// Declares ofstream for writing to files.
std::ofstream fout;

// Float to String conversion.
template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

//  -1 When Driver turned left, 0 when Driver hasn't turned, and 1 when Driver turned right.
int directionTurned = 0;

// Writes Autonomous code to .txt file.
void XPressed()
{

  // Calculates average turn across all motors, to minimize innacuracy.
  float averageTurns = (leftMotorA.position(turns) + leftMotorB.position(turns) + rightMotorA.position(turns) + rightMotorB.position(turns)) / 4;

  // Filters out any irrelevant collected data. Any rotation less than 0.001 is unnecessary and shouldn't be recorded.
  if (averageTurns > 0.001)
  {
    // Declares necessary string variables.
    std::string averageTurnsString = ToString(averageTurns);
    std::string nextStep = "";

    // Writes various different autonomous tasks to the .txt file depending on whether the Driver drove straight, or turned.
    switch(directionTurned)
    {
      case -1:
        nextStep = "LeftDriveSmart.spin(reverse); RightDriveSmart.spinFor(forward, "+averageTurnsString+", turns); LeftDriveSmart.Stop(); wait(1, seconds);";
        directionTurned = 0;
        break;
      case 0:
        nextStep = "LeftDriveSmart.spin(forward); RightDriveSmart.spinFor(forward, "+averageTurnsString+", turns); LeftDriveSmart.Stop(); wait(1, seconds);";
        directionTurned = 0;
        break;
      case 1:
        nextStep = "RightDriveSmart.spin(reverse); LeftDriveSmart.spinFor(forward, "+averageTurnsString+", turns); RightDriveSmart.Stop(); wait(1, seconds);";
        directionTurned = 0;
        break;
    }

    // Opens file and appends the previous step.
    fout.open("auton_values.txt", std::ofstream::app);
    fout << nextStep+"\n";
    fout.close();
  }

  // Reset motor positions for next step
  leftMotorA.setPosition(0, turns);
  leftMotorB.setPosition(0, turns);
  rightMotorA.setPosition(0, turns);
  rightMotorB.setPosition(0, turns);
}

// Drives forward only while A is pressed.
void APressed()
{
  Drivetrain.setDriveVelocity(20, percent);
  while (Controller1.ButtonA.pressing())
  {
    Drivetrain.drive(forward);
  }
  Drivetrain.stop();
}

// Drive forward only while B is pressed.
void BPressed()
{
  Drivetrain.setDriveVelocity(20, percent);
  while (Controller1.ButtonB.pressing())
  {
    Drivetrain.drive(reverse);
  }
  Drivetrain.stop();
}

// Point turn left only while left arrow is pressed.
void LeftPressed()
{
  // Stores the rotational direction for later use.
  directionTurned = -1;

  RightDriveSmart.setVelocity(20, percent);
  LeftDriveSmart.setVelocity(20, percent);
  while (Controller1.ButtonLeft.pressing())
  {
    RightDriveSmart.spin(forward);
    LeftDriveSmart.spin(reverse);
  }
  Drivetrain.stop();
}

// Point turn right only while right arrow is pressed.
void RightPressed()
{
  // Stores the rotational direction for later use.
  directionTurned = 1;

  RightDriveSmart.setVelocity(20, percent);
  LeftDriveSmart.setVelocity(20, percent);
  while (Controller1.ButtonRight.pressing())
  {
    RightDriveSmart.spin(reverse);
    LeftDriveSmart.spin(forward);
  }
  Drivetrain.stop();
}

void userControl(void) {

  // Clears file before recording next steps
  fout.open("auton_values.txt");
  fout.close();

  while (true) {
    Controller1.ButtonX.pressed(XPressed);
    Controller1.ButtonA.pressed(APressed);
    Controller1.ButtonB.pressed(BPressed);
    Controller1.ButtonLeft.pressed(LeftPressed);
    Controller1.ButtonRight.pressed(RightPressed);
    wait(20, msec);
  }
}

int main() {
  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods.
  Competition.drivercontrol(userControl);

  // Run the pre-autonomous function.
  preAutonomous();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}