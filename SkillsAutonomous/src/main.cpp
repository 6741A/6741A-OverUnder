
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// GPS9                 gps           15              
// GPS8                 gps           21              
// InertialSensor       inertial      19              
// RotationLeft         rotation      11              
// RotationRight        rotation      12              
// LeftMotors           motor_group   3, 2            
// RightMotors          motor_group   6, 5            
// Controller1          controller                    
// CatapultMotor        motor         10              
// CataLimit            limit         A               
// IntakeMotor          motor         1               
// IntakePistonLeft     digital_out   H               
// IntakePistonRight    digital_out   C               
// WingPistonLeft       digital_out   D               
// WingPistonRight      digital_out   E               
// ---- END VEXCODE CONFIGURED DEVICES ----

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

void pre_auton(void) {

  vexcodeInit();

  robot.base.robotXPosition = 0;
  robot.base.robotYPosition = 0;
  robot.base.robotOrientation = 0;

  robot.base.robotOrientation = 0;
  InertialSensor.setHeading(0, degrees);
  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

  InertialSensor.calibrate();
  wait(3,sec);

  robot.base.TrackPositionAndHeading();
}



void autonomous(void) {

  // Match Auton
/*
  robot.base.DriveForward(-30,5);
  wait(0.5,sec);
  robot.base.DriveForward(18,5);
  robot.base.Rotate(84, 8);
  //robot.base.Rotate(300, 10);
  robot.intake.ReverseIntake();
  //robot.catapult.RetractCatapult();
  //wait(0.7, sec);
  //CatapultMotor.stop(hold);
  //waitUntil(robot.cataDrawed);
  robot.base.DriveForward(35,5);
  wait(0.5, sec);
  //robot.base.Rotate(0,5);
  //wait(1, sec);
  robot.base.DriveForward(-18,5);
  robot.base.Rotate(40,10);
  //robot.base.Rotate(220, 10);
  robot.base.DriveForward(28,5);
*/

// Skill auton through hallway
robot.intake.ExtendIntake();
LeftMotors.stop(hold);
RightMotors.stop(hold);
robot.catapult.StartCatapultMatchLoading();
//wait(1, sec);
robot.base.RotateLocally(334, 25, 5);
//wait(0.2,sec);
robot.catapult.RetractCatapult();
waitUntil(Rotation9.angle() > 45);
CatapultMotor.stop(hold);

robot.base.ForwardLocally(-33, 75, 10);
wait(0.2, sec);

//robot.intake.RetractIntake();

InertialSensor.setHeading(10, degrees);

robot.base.RotateLocally(84, 25, 5);
wait(0.2, sec);


robot.base.ForwardLocally(-39, 75, 10);
wait(0.2, sec);

// face barrier

robot.base.RotateLocally(183, 25, 5);
wait(0.2, sec);

  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

robot.base.ForwardLocally(-12, 75, 10);
wait(0.2, sec);

robot.base.RotateLocally(108, 25, 5);
wait(0.2, sec);


  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

robot.base.ForwardLocally(-12, 75, 10);
wait(0.2, sec);

robot.base.RotateLocally(20, 25, 5);
wait(0.2, sec);




robot.wings.ExtendWings();

robot.base.ForwardLocally(-22, 100, 10);

robot.base.RotateLocally(145, 25, 5);
wait(0.2, sec);



  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

robot.base.ForwardLocally(-16, 50, 10);

robot.base.RotateLocally(22, 25, 5);
wait(0.2, sec);

  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

robot.base.ForwardLocally(-20, 100, 10);



/*


//robot.base.ForwardLocally(-44, 90, 10);
//wait(0.5, sec);

Controller1.Screen.print("bro");


//robot.base.ForwardLocally(-10, -40, 8);
//wait(0.5, sec);

robot.base.RotateLocally(185, 25, 5);

  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

robot.base.ForwardLocally(-16, 40, 10);
wait(0.5, sec);

robot.base.RotateLocally(155, 25, 2);
wait(0.2, sec);

robot.base.ForwardLocally(-25, 40, 10);
wait(0.5, sec);

robot.base.RotateLocally(35, 25, 2);
wait(0.2, sec);

// Push into front
robot.base.ForwardLocally(-38, 80, 10);
wait(0.5, sec);

robot.base.RotateLocally(155, 25, 2);
wait(0.2, sec);

robot.base.ForwardLocally(-25, 40, 10);
wait(0.5, sec);*/

// Skill auton over barrier
/*
//robot.catapult.StartCatapultMatchLoading();
// Go to middle of field
robot.base.ForwardLocally(-20, 25, 10);
wait(0.2, sec);
// Retract cata
robot.catapult.RetractCatapult();
waitUntil(CataLimit);
CatapultMotor.stop(hold);
// Point to front of field
robot.base.RotateLocally(342, 25, 3);
wait(1,sec);
// Drive over barrier and push nuts into goal
robot.base.ForwardLocally(-50, 40, 10);
wait(0.2, sec);
// Back up
robot.base.ForwardLocally(50, -25, 10);
wait(0.2, sec);
// Ram into goal again
robot.base.ForwardLocally(-50, 40, 10);
wait(0.2, sec);

*/





/*
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

*/

  // 8. Face goal, extend wings, push nuts into goal



  // 9. Drive back to previous position



  // 10. Drive ⅔ distance of field



  // 11. Face goal, extend wings, push nuts into goal



  // 12. Drive back to previous position



  // 13. Drive to other corner goal



  // 14. Face goal, extend wings, push nuts into goal

}

void DriverControls() {

//robot.intake.RetractIntake();

  // Drivetrain Controls

  LeftMotors.spin(forward, (Controller1.Axis3.value() + (Controller1.Axis1.value() * 0.35) * 2), percent);
  RightMotors.spin(forward, (Controller1.Axis3.value() - (Controller1.Axis1.value() * 0.35) * 2), percent);

  // Intake Controls

  if (Controller1.ButtonR2.pressing()) {

    // Enable and disable intake with every other R2 press
    if (robot.intakeEnabled) { 

      robot.DisableIntake();

    }
    else { 

      robot.EnableIntake(); 
      
    }

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

  //if (Rotation9.angle() > 350)
  ///{
  //  Rotation9.setPosition(5, degrees);
  //}

  if ((Rotation9.angle() > 62) && (Rotation9.angle() < 350))
  {

    CatapultMotor.stop(hold);
    robot.cataDrawed = true;

    if (Controller1.ButtonB.pressing())
    {
      robot.cataDrawed = false;

      CatapultMotor.spin(forward, 100, percent);

      // Wait so the brain doesnt recieve a million pressing() calls in one press
      wait(0.2, sec);
  }
    
  }


  if (Controller1.ButtonB.pressing())
  { Rotation9.setPosition(0, degrees);
        robot.cataDrawed = false;

    CatapultMotor.spin(forward, 100, percent);

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
    
  }


  // Wing Controls

  if (Controller1.ButtonA.pressing())
  {

    // Extend and retract wings with every other A press
    if (robot.wingsExtended) 
    { robot.RetractWings(); }

    else
    { robot.ExtendWings(); }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
    
  }

  if (Controller1.ButtonLeft.pressing())
  {

    // Extend and retract wings with every other A press
    if (robot.intakeExtended) { robot.RetractIntake(); }
    else { robot.ExtendIntake(); }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
    
  }

  if (CataLimit)
  {
    CatapultMotor.stop(hold);
  }

}


void usercontrol(void) 
{
 /* InertialSensor.startCalibration();
InertialSensor.resetHeading();

  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

  robot.base.robotXPosition = 0;
  robot.base.robotYPosition = 0;
  robot.base.robotOrientation = 0;

  robot.base.TrackPositionAndHeading();*/
  

 // robot.catapult.StartCatapultMatchLoading();


  while (1) 
  {

    //robot.base.TrackPositionAndHeading();


    DriverControls();


    wait(20, msec);

  }

}

int main() 
{

  Rotation9.setPosition(0, degrees);
  CatapultMotor.spin(forward, 100, percent); 
  robot.intake.ExtendIntake();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();
 
  // Prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
  
}
