#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
gps GPS9 = gps(PORT18, 101.60, 152.40, mm, 90);
gps GPS8 = gps(PORT21, 0.00, 0.00, mm, 180);
inertial InertialSensor = inertial(PORT13);
rotation RotationLeft = rotation(PORT20, true);
rotation RotationRight = rotation(PORT7, false);
motor LeftMotorsMotorA = motor(PORT3, ratio6_1, true);
motor LeftMotorsMotorB = motor(PORT5, ratio6_1, true);
motor_group LeftMotors = motor_group(LeftMotorsMotorA, LeftMotorsMotorB);
motor RightMotorsMotorA = motor(PORT2, ratio6_1, false);
motor RightMotorsMotorB = motor(PORT1, ratio6_1, false);
motor_group RightMotors = motor_group(RightMotorsMotorA, RightMotorsMotorB);
controller Controller1 = controller(primary);
limit CataLimit = limit(Brain.ThreeWirePort.A);
digital_out IntakePistonLeft = digital_out(Brain.ThreeWirePort.D);
digital_out IntakePistonRight = digital_out(Brain.ThreeWirePort.C);
digital_out WingPistonLeft = digital_out(Brain.ThreeWirePort.G);
digital_out WingPistonRight = digital_out(Brain.ThreeWirePort.E);
motor IntakeMotorMotorA = motor(PORT11, ratio6_1, true);
motor IntakeMotorMotorB = motor(PORT12, ratio6_1, false);
motor_group IntakeMotor = motor_group(IntakeMotorMotorA, IntakeMotorMotorB);
rotation Rotation9 = rotation(PORT19, false);
motor CatapultMotorMotorA = motor(PORT8, ratio36_1, false);
motor CatapultMotorMotorB = motor(PORT6, ratio36_1, true);
motor_group CatapultMotor = motor_group(CatapultMotorMotorA, CatapultMotorMotorB);

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