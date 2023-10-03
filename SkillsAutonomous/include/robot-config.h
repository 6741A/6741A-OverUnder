using namespace vex;

extern brain Brain;

// VEXcode devices
extern gps GPS9;
extern gps GPS8;
extern inertial InertialSensor;
extern rotation RotationLeft;
extern rotation RotationRight;
extern motor_group LeftMotors;
extern motor_group RightMotors;
extern controller Controller1;
extern motor CatapultMotor;
extern limit CataLimit;
extern digital_out IntakePistonLeft;
extern digital_out IntakePistonRight;
extern digital_out WingPistonLeft;
extern digital_out WingPistonRight;
extern motor_group IntakeMotor;
extern rotation Rotation9;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );