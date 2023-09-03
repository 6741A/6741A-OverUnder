#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
rotation LEncoder = rotation(PORT1, false);
rotation REncoder = rotation(PORT2, false);
rotation BEncoder = rotation(PORT3, false);
motor LDriveF = motor(PORT4, ratio18_1, false);
motor LDriveB = motor(PORT5, ratio18_1, false);
motor RDriveF = motor(PORT6, ratio18_1, false);
motor RDriveB = motor(PORT7, ratio18_1, false);
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT8, ratio18_1, false);
motor leftMotorB = motor(PORT9, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT10, ratio18_1, true);
motor rightMotorB = motor(PORT11, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}