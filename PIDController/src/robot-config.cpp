#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT2, ratio18_1, false);
motor rightMotorA = motor(PORT3, ratio18_1, false);
motor rightMotorB = motor(PORT4, ratio18_1, false);
motor LeftMotorGroupMotorA = motor(PORT5, ratio18_1, false);
motor LeftMotorGroupMotorB = motor(PORT6, ratio18_1, false);
motor_group LeftMotorGroup = motor_group(LeftMotorGroupMotorA, LeftMotorGroupMotorB);
motor RightMotorGroupMotorA = motor(PORT7, ratio18_1, false);
motor RightMotorGroupMotorB = motor(PORT8, ratio18_1, false);
motor_group RightMotorGroup = motor_group(RightMotorGroupMotorA, RightMotorGroupMotorB);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}