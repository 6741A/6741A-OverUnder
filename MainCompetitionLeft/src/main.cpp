/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       CompetitionLeft.cpp                                       */
/*    Authors:      Coleman Donahue & Brendan Parker                          */
/*    Created:      Mon July 11 2022                                          */
/*    Description:  All individual programs combined to create                */
/*                  the final program that will be used during                */
/*                  matches                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;
competition Competition;

motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT2, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT3, ratio18_1, true);
motor rightMotorB = motor(PORT4, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
controller Controller1 = controller(primary);

void pre_auton(void) {
  vexcodeInit();
  // Setting to coast to prevent overheating.
  // Hold & Brake create unecessary heat.
  leftMotorA.setBrake(coast);
  leftMotorB.setBrake(coast);
  rightMotorA.setBrake(coast);
  rightMotorB.setBrake(coast);
}

/////////////////////////////////////////
//             AUTONOMOUS              //
/////////////////////////////////////////

// Code from Rerun program will be pasted into here
void autonomous(void) {


}

/////////////////////////////////////////
//               DRIVER                //
/////////////////////////////////////////

float speedDampeningFactor = 0.5;

// Control Drivetrain With Left Joystick
void SingleJoystickControls()
{ 
  LeftDriveSmart.setVelocity(((Controller1.Axis3.position() + Controller1.Axis4.position())) * speedDampeningFactor, percent);
  RightDriveSmart.setVelocity(((Controller1.Axis3.position() - Controller1.Axis4.position())) * speedDampeningFactor, percent);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
}

// Control Drivetrain With Both Joysticks
void DoubleJoystickControls()
{
  LeftDriveSmart.setVelocity(((Controller1.Axis3.position() + Controller1.Axis1.position())) * speedDampeningFactor, percent);
  RightDriveSmart.setVelocity(((Controller1.Axis3.position() - Controller1.Axis1.position())) * speedDampeningFactor, percent);
  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
}

// Control Drivetrain With Video Game Controls
/* 
    What are video game Controls? 
      I've attempted to recreate the controls of popular
      driving and racing video games, and map them out onto
      a Vex Controller. The goal is for it to feel as natural
      and second nature as possible.
*/  

// Speed of Drivetrain.
float speed = 20;

// Joystick deadzone, allows for less sporadic movement.
float deadzone = 10;

// Tells motor groups to stop moving when true.
bool stopOverrideLeft = false;
bool stopOverrideRight = false;

void VideoGameControls()
{
  // Drive Forward
  if (Controller1.ButtonR2.pressing())
  {
    if (!stopOverrideLeft) { LeftDriveSmart.setVelocity(speed, percent); }
    if (!stopOverrideRight) { RightDriveSmart.setVelocity(speed, percent); }
  }
  // Drive Backwards
  else if (Controller1.ButtonR1.pressing())
  {
    if (!stopOverrideLeft) { LeftDriveSmart.setVelocity(-speed, percent); }
    if (!stopOverrideRight) { RightDriveSmart.setVelocity(-speed, percent); }
  }
  // Turn Right
  if (Controller1.Axis4.position() < -deadzone)
  { LeftDriveSmart.setVelocity(0, percent); stopOverrideRight = true; }
  // Turn Left
  else if (Controller1.Axis4.position() > deadzone)
  { RightDriveSmart.setVelocity(0, percent); stopOverrideLeft = true; }
  // Dont override drive system to turn if joystick is unmoved
  if (Controller1.Axis4.position() < deadzone && Controller1.Axis4.position() > -deadzone)
  { stopOverrideRight = false; stopOverrideLeft = false; }
}

// 1 = Single Joystick, 2 = Double Joystick, 3 = Video Game
int controlType = 3;
void usercontrol(void) {
    // Executes independent while loops
    // Depending on control type, so
    // It doesn't have to waste resources
    // Constantly checking switch statement
    // Every 20 msec.
    switch(controlType)
    {
      case 1:
        while (1) {
          SingleJoystickControls(); 
          wait(20, msec); 
        }
        break;
      case 2: 
        while (1) {
          DoubleJoystickControls(); 
          wait(20, msec); 
        }
        break;
      case 3: 
        while (1) {
          VideoGameControls(); 
          wait(20, msec); 
        }
        break;
    }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}
