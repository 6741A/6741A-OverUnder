/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotorA           motor         1               
// leftMotorB           motor         2               
// rightMotorA          motor         3               
// rightMotorB          motor         4               
// LeftMotorGroup       motor_group   5, 6            
// RightMotorGroup      motor_group   7, 8            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

// Variables modified for use
bool enableDrivePID = true;

// Settings
double kP = 0.0;
double kI = 0.0;
double kD = 0.0;

// Autonomous Settings
int desiredValue = 200; // (Desired Forward Motion Motor Positions) ~ Turn Values From Driver Data Collection

int error; // (Sensor Value - Desired Value)             ~ Positional Value 
int previousError = 0; // (Position 20 Milliseconds Ago) ~ Past Positional Value
int derivative; // (Error - Previous Error)              ~ Speed Value
int totalError = 0;; // (Total Error + Error)            ~ Absement Value

bool resetDriveSensors = false;

int DrivePID()
{

  /*
    !!!!!!!!!!!!!!!!! Remove Integral IF Too Many Oscelations
  */

  while (enableDrivePID)
  {

    if (resetDriveSensors)
    {
      resetDriveSensors = false;
      leftMotorA.setPosition(0, turns);
      leftMotorB.setPosition(0, turns);
      rightMotorA.setPosition(0, turns);
      rightMotorB.setPosition(0, turns);
    }


    // Get Position Of All Motors
    float leftMotorPositionA = leftMotorA.position(turns);
    float leftMotorPositionB = leftMotorB.position(turns);
    float rightMotorPositionA = rightMotorA.position(turns);
    float rightMotorPositionB = rightMotorB.position(turns);

    //////////////////////////////////////
    //       Lateral Movement PID       //
    //////////////////////////////////////

    // Get Average Of Both Sides Motors
    float averagePositionLeft = (leftMotorPositionA + leftMotorPositionB) / 2;
    float averagePositionRight = (rightMotorPositionA + rightMotorPositionB) / 2;

    // Get Average Of 4 Motors
    float averagePosition = (averagePositionLeft + averagePositionRight) / 2;

    // Potential
    error = averagePosition - desiredValue;
    // Derivative
    derivative = error - previousError;
    // Integral
    totalError += error;

    double lateralMotorPower = ((error * kP) + (derivative * kD) + (totalError * kI));


    LeftMotorGroup.spin(forward, lateralMotorPower, voltageUnits::volt);
    RightMotorGroup.spin(forward, lateralMotorPower, voltageUnits::volt);


    previousError = error;
    task::sleep(20);

  }

  return 1;
}

void Turn(float turnAmount)
{
  if (turnAmount < 0)
  {
    LeftMotorGroup
  }
}

void autonomous(void) {

  task Test(DrivePID);
  enableDrivePID = true;

  resetDriveSensors = true;
  desiredValue = 10; // Drives motors forward for 10 turns
  task::sleep(1000);

  resetDriveSensors = true;

  task::sleep(1000);
}

void usercontrol(void) {
  while (1) {
  enableDrivePID = false;
    wait(20, msec); // Sleep the task for a short amount of time to
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}


/*

