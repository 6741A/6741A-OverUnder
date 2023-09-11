
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:                                                                 */
/*    Created:      Sat Sep 2 2023                                            */
/*    Description:  6741A Skills Challenge program                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
#include "PositionTracker.h"
#include "Robot.h"
#include "Base.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Instantiate Mover class object
Robot robot;

// text
void pre_auton(void) 
{
  //test

  vexcodeInit();

  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

  robot.base.robotXPosition = 0;
  robot.base.robotYPosition = 0;
  robot.base.robotOrientation = 0;

  robot.base.TrackPositionAndHeading();

}



void autonomous(void) 
{

  // 0. Rotate parallel with match load bar, and back into it

  robot.base.Rotate(45, 5);
  robot.base.DriveForward(5, 1);

  // 1. Shoot all 44 Match Loads over

  robot.catapult.StartCatapultMatchLoading();

  // 2. Drive up to right side, then extend wings

  robot.base.Rotate(1, 5);
  robot.base.DriveForward(50, 5);
  robot.wings.ExtendWings();

  // 3. Push nuts forward

  robot.base.Rotate(45, 5);
  robot.base.DriveForward(25, 5);  

  // 4. Line up with goal, push nuts into goal

  robot.base.Rotate(90, 5);
  robot.base.DriveForward(10, 5); 

  // 5. Back up to previous point

  robot.base.DriveForward(-10, 5); 

  // 6. Drive away from goal to mid barrier



  // 7. Drive ⅓ distance of field



  // 8. Face goal, extend wings, push nuts into goal



  // 9. Drive back to previous position



  // 10. Drive ⅔ distance of field



  // 11. Face goal, extend wings, push nuts into goal



  // 12. Drive back to previous position



  // 13. Drive to other corner goal



  // 14. Face goal, extend wings, push nuts into goal




}

void DriverControls()
{

  // Drivetrain Controls

  LeftMotors.spin(forward, (Controller1.Axis3.value() + (Controller1.Axis1.value() * 0.5) * 2), percent);
  RightMotors.spin(forward, (Controller1.Axis3.value() - (Controller1.Axis1.value() * 0.5) * 2), percent);

  // Intake Controls

  if (Controller1.ButtonR2.pressing())
  {

    // Enable and disable intake with every other R2 press
    if (robot.intakeEnabled) { robot.DisableIntake(); }
    else { robot.EnableIntake(); }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);

  }

  if (Controller1.ButtonR1.pressing())
  {
    
    // Enable and disable reverse intake with every other R2 press
    if (robot.intakeEnabled) { robot.DisableIntake(); }
    else { robot.ReverseIntake(); }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);

  }

  // Catapult Controls 

  if (Controller1.ButtonB.pressing())
  {

    // Draw back and launch catapult with every other B press
    if (robot.cataDrawed) { robot.LaunchCatapult(); }
    else { robot.RetractCatapult(); }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
    
  }

  // Wing Controls

  if (Controller1.ButtonA.pressing())
  {

    // Extend and retract wings with every other A press
    if (robot.wingsExtended) { robot.RetractWings(); }
    else { robot.ExtendWings(); }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
    
  }

}


void usercontrol(void) 
{
  InertialSensor.startCalibration();
InertialSensor.resetHeading();

  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

  robot.base.robotXPosition = 0;
  robot.base.robotYPosition = 0;
  robot.base.robotOrientation = 0;

  robot.base.TrackPositionAndHeading();
  



  while (1) 
  {

    robot.base.TrackPositionAndHeading();
    DriverControls();

    wait(20, msec);

  }

}

int main() 
{

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  
  // Prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
  
}
