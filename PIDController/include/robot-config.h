using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftMotorA;
extern motor leftMotorB;
extern motor rightMotorA;
extern motor rightMotorB;
extern motor_group LeftMotorGroup;
extern motor_group RightMotorGroup;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );