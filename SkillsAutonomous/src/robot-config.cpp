#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
gps GPS9 = gps(PORT15, 101.60, 152.40, mm, 90);
gps GPS8 = gps(PORT21, 0.00, 0.00, mm, 180);
inertial InertialSensor = inertial(PORT19);
rotation RotationLeft = rotation(PORT11, true);
rotation RotationRight = rotation(PORT12, false);
motor LeftMotorsMotorA = motor(PORT3, ratio6_1, true);
motor LeftMotorsMotorB = motor(PORT2, ratio6_1, true);
motor_group LeftMotors = motor_group(LeftMotorsMotorA, LeftMotorsMotorB);
motor RightMotorsMotorA = motor(PORT6, ratio6_1, false);
motor RightMotorsMotorB = motor(PORT5, ratio6_1, false);
motor_group RightMotors = motor_group(RightMotorsMotorA, RightMotorsMotorB);
controller Controller1 = controller(primary);
motor CatapultMotor = motor(PORT10, ratio36_1, false);
limit CataLimit = limit(Brain.ThreeWirePort.A);
motor IntakeMotor = motor(PORT1, ratio6_1, false);
digital_out IntakePistonLeft = digital_out(Brain.ThreeWirePort.H);
digital_out IntakePistonRight = digital_out(Brain.ThreeWirePort.C);
digital_out WingPistonLeft = digital_out(Brain.ThreeWirePort.D);
digital_out WingPistonRight = digital_out(Brain.ThreeWirePort.E);

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