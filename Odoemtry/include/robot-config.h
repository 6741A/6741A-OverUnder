using namespace vex;

extern brain Brain;

// VEXcode devices
extern rotation LEncoder;
extern rotation REncoder;
extern rotation BEncoder;
extern motor LDriveF;
extern motor LDriveB;
extern motor RDriveF;
extern motor RDriveB;
extern controller Controller1;
extern drivetrain Drivetrain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );