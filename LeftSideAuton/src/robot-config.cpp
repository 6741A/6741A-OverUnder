#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
gps GPS9 = gps(PORT9, 0.00, 0.00, mm, 180);
gps GPS8 = gps(PORT21, 0.00, 0.00, mm, 180);
inertial InertialSensor = inertial(PORT1);
rotation RotationLeft = rotation(PORT5, false);
rotation RotationRight = rotation(PORT3, true);
motor LeftMotorsMotorA = motor(PORT8, ratio6_1, false);
motor LeftMotorsMotorB = motor(PORT10, ratio6_1, false);
motor_group LeftMotors = motor_group(LeftMotorsMotorA, LeftMotorsMotorB);
motor RightMotorsMotorA = motor(PORT6, ratio6_1, true);
motor RightMotorsMotorB = motor(PORT7, ratio6_1, true);
motor_group RightMotors = motor_group(RightMotorsMotorA, RightMotorsMotorB);
controller Controller1 = controller(primary);

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