#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
inertial INERTIAL = inertial(PORT1);
motor LEFTDRIVEMotorA = motor(PORT2, ratio18_1, false);
motor LEFTDRIVEMotorB = motor(PORT3, ratio18_1, false);
motor_group LEFTDRIVE = motor_group(LEFTDRIVEMotorA, LEFTDRIVEMotorB);
motor RIGHTDRIVEMotorA = motor(PORT4, ratio18_1, false);
motor RIGHTDRIVEMotorB = motor(PORT5, ratio18_1, false);
motor_group RIGHTDRIVE = motor_group(RIGHTDRIVEMotorA, RIGHTDRIVEMotorB);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}