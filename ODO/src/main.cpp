/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LEncoder             rotation      1               
// REncoder             rotation      2               
// BEncoder             rotation      3               
// LDriveF              motor         4               
// LDriveB              motor         5               
// RDriveF              motor         6               
// RDriveB              motor         7               
// Controller1          controller                    
// Drivetrain           drivetrain    8, 9, 10, 11    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
motor LDriveF = motor(PORT10, ratio18_1, false);
motor LDriveB = motor(PORT6, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(LDriveF, LDriveB);
motor RDriveF = motor(PORT20, ratio18_1, true);
motor RDriveB = motor(PORT16, ratio18_1, true);
motor_group RightDriveSmart = motor_group(RDriveF, RDriveB);

rotation REncoder = rotation(PORT1, false);
rotation LEncoder = rotation(PORT2, false);
rotation BEncoder = rotation(PORT3, false);

controller Controller1 = controller(primary);
/*
  1. motor group
  2. motor group
  3. circumference of wheel (3.25 = 299.24)
  4. track width
  5. wheel base
  6. measurement
  7. gear ratio
*/
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 295, 40, mm, 1.6666666666666667);


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// Angle and point definition
float x = 0;
float y = 0;
float head = 0;
float relativeHead = 0;

// Stored Value Definition
float prevLeft = 0.0;
float prevRight = 0.0;
float prevBack = 0.0;
float currentLeft = 0.0;
float currentRight = 0.0;
float currentBack = 0.0;

// Tracking Wheels (CHANGE THESE)
float trackWidth = 0;
float LDistance = 0;
float RDistance = 0;
float BDistance = 0;
/*----------------------------------------------------------------------------*/

	// Minimum turn velocity
float minTurnVel = 1;

	// P value for turn PD system
float kP_turn = 0.75;

	// D value for turn PD system
float kD_turn = 3;

	// Acceptable margin of error for turn PD system
float MoE_turn = 0.5;

	// Minimum turn velocity
float minDriveVel = 5;

	// P value for drive PD system
float kP_drive = 95;

	// D value for drive PD system
float kD_drive = 0;

	// Acceptable margin of error for drive PD system
float MoE_drive = 0.1;

/*----------------------------------------------------------------------------*/

void ClearEncoders()
{
  // Resets all encoder values
  LEncoder.resetPosition();
  REncoder.resetPosition();
  BEncoder.resetPosition();
}

void SetOdometry(float set_x, float set_y, float set_head)
{
  
  // Sets key odom values to inputs or default (0)
  x = set_x;
  y = set_y;
  head = set_head;

	// Sets all values to default (0)
  relativeHead = 0;
  prevBack = 0;
  prevLeft = 0;
  prevRight = 0;
  currentBack = 0;
  currentLeft = 0;
  currentRight = 0;
  
  ClearEncoders();
}

/**
- Reduces input angle to max range of [-(PI), (PI)] radians or [-180, 180] degrees.
- Returns a float that is the angle converted to the reduced angle range (in degrees).
- _angleDeg The angle measure (in degrees) to be converted.
*/
float ReduceAngle(float _angleDeg)
{
  while(!(_angleDeg >= -180 && _angleDeg < 180))
  {
    if (_angleDeg < -180) { _angleDeg += 360; }
    if (_angleDeg >= 180) { _angleDeg -= 360; }
  }
  return _angleDeg;
}

/**
- Reduces input angle to max range of [0, 2(PI)] radians or [0, 360] degrees.
- Returns a float that is the angle converted to the reduced angle range (in radians).
- _angleRad The angle measure (in radians) to be converted.
*/
float NormalizeAngle(float _angleRad){
  while( !(_angleRad >= 0 && _angleRad < (2 * M_PI)) )
  {
    if  (_angleRad < 0)           { _angleRad += (2 * M_PI); }
    if  (_angleRad >= (2 * M_PI)) { _angleRad -= (2 * M_PI); }
  }
  return _angleRad;
}

/**
- Sets motor velocities to the identified params and spins the motors at their respective velocities.
- LFSpeed Velocity input for the left front motor.
- LBSpeed Velocity input for the left back motor.
- RFSpeed Velocity input for the right front motor.
- RBSpeed Velocity input for the right back motor.
*/
void setDriveVelocity(float LFSpeed, float LBSpeed, float RFSpeed, float RBSpeed){
  LDriveF.spin(directionType::fwd, LFSpeed, velocityUnits::pct);
  LDriveB.spin(directionType::fwd, LBSpeed, velocityUnits::pct);
  RDriveF.spin(directionType::fwd, RFSpeed, velocityUnits::pct);
  RDriveB.spin(directionType::fwd, RBSpeed, velocityUnits::pct);
}


/**
- Sets all motor velocities to 0, stopping the motors.
*/
void stopDrive(){
  LDriveF.stop(brakeType::hold);
  LDriveB.stop(brakeType::hold);
  RDriveF.stop(brakeType::hold);
  RDriveB.stop(brakeType::hold);
  wait(50, msec);
  LDriveF.stop(brakeType::coast);
  LDriveB.stop(brakeType::coast);
  RDriveF.stop(brakeType::coast);
  RDriveB.stop(brakeType::coast);
}

bool enableOdom = true;

float getXPos() { return x; }
float getYPos() { return y; }
float getHeading() { return head; }
float getHeadingDeg() { return head * (180 / M_PI); }


int UpdatePosition()
{
  ClearEncoders();
  //setOdometry();

  while (enableOdom)
  {
    currentLeft = -LEncoder.position(turns);
    currentRight = REncoder.position(turns);
    currentBack = -BEncoder.position(turns);

    float dL = currentLeft * M_PI * trackWidth;
    float dR = currentRight * M_PI * trackWidth;
    float dB = currentBack * M_PI * trackWidth;

    float dHeading = (dL - dR) / (LDistance + RDistance);

    float h;
    float halfAngle;
    float h2;

    if (dHeading)
    {
      float radius = dR / dHeading;
      halfAngle = dHeading / 2;

      float halfSin = sin(halfAngle);
      h = ((radius + RDistance) * halfSin) * 2.0;

      float radius2 = dB / dHeading;
      h2 = ((radius2 + BDistance) * halfSin) * 2.0;
    }
    else
    {
      h = dR;
      halfAngle = 0;
      h2 = dB;
    }

    float endAngle = halfAngle + head;
    float cosA = cos(endAngle);
    float sinA = sin(endAngle);

    y += h * cosA;
    x += h * sinA;

    y += h2 * -sinA;
    x += h2 * cosA;

    head += dHeading;
    head = NormalizeAngle(head);

    ClearEncoders();

    // Update Brain
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(10, 20, "X: %f", getXPos);
    Brain.Screen.printAt(10, 70, "Y: %f", getYPos);
    Brain.Screen.printAt(10, 120, "Heading: %f", getHeadingDeg);
    Brain.Screen.printAt(10, 170, "Controller Ax3 %d", Controller1.Axis3.value());
    Brain.Screen.printAt(10, 230, "Controller Ax2 %d", Controller1.Axis2.value());

    // Wait
    task::sleep(5);
  }
  return 1;
}

// - _targetAngle = desired robot angle
void PointTurn(float _targetAngle)
{

  SetOdometry(0, 0, 0);

  float tempDeg = getHeadingDeg();

  float turnError = ReduceAngle(fabs(_targetAngle) - tempDeg);

  int turnDirection = fabs(_targetAngle) / _targetAngle;

  //std::cout << "TurnDirection: " << turnDirection << std::endl;

  float dTurnError = 0;

  float prevTurnError = turnError;

  // Keeps turning the robot until the error is within the defined range of accepted error.
  while (fabs(turnError) > MoE_turn)
  {
    tempDeg = getHeadingDeg();

    if (getHeadingDeg() > _targetAngle && turnDirection < 0)
    {
      tempDeg = 360 - getHeadingDeg();
    }

    turnError = ReduceAngle(fabs(_targetAngle) - tempDeg);

    dTurnError = turnError - prevTurnError;

    prevTurnError = turnError;

    float turnSpeed = (turnError * kP_turn) + (dTurnError * kD_turn);

    //std::cout << "Speed: " << turnSpeed << std::endl;

    if (turnSpeed < minTurnVel)
    {
      //std::cout << "break | " << turnError << std::endl;
      break;
    }

    setDriveVelocity(turnDirection * turnSpeed, turnDirection * turnSpeed, turnDirection * -turnSpeed, turnDirection * -turnSpeed);

    wait(5, msec);
  }
  //std::cout << "done | " << turnError << std::endl;
  stopDrive();
}

// - _targetDistanceInches = however many inches point is away from robot
void DriveTo(float _targetDistanceInches)
{
  SetOdometry(0, 0, 0);

  float driveError = 1 - (getYPos() / _targetDistanceInches);

  float driveDirection = fabs(_targetDistanceInches) / _targetDistanceInches;

  float dDriveError = 0;
  float prevDriveError = driveError;

  while (driveError > MoE_drive)
  {
    driveError = 1 - (getYPos() / _targetDistanceInches);

    dDriveError = driveError - prevDriveError;

    prevDriveError = driveError;

    float driveSpeed = (driveError * kP_drive) + (driveError * kD_drive);

    if (driveSpeed < minDriveVel)
    {
      break;
    }

    setDriveVelocity(driveDirection * driveSpeed, driveDirection * driveSpeed, driveDirection * driveSpeed, driveDirection * driveSpeed);

    wait(5, msec);
  }
  stopDrive();
}

void DriveToPoint(float _x, float _y)
{
  SetOdometry(0, 0, 0);
  float startingX = getXPos();
  float startingY = getYPos();


  float turnAngle = atan((_y - startingY) / (_x - startingX)) * (180 / M_PI);
  if (_y - startingY < 0) { turnAngle = turnAngle + 180; }
  PointTurn(turnAngle);

  float driveDistance = sqrt(((_x - startingX) * (_x - startingX)) + ((_y - startingY) * (_y - startingY)));

  Drivetrain.setDriveVelocity(50, percent);
  Drivetrain.driveFor(forward, driveDistance, mm, true);

}

void functionTest()
{
  SetOdometry(0, 0, 0);
  DriveToPoint(0, 0);
  PointTurn(45);
  DriveTo(-12);
  DriveTo(-10);
}

void autonomous(void) {
  functionTest();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
