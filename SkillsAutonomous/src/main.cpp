// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// GPS9                 gps           18              
// GPS8                 gps           21              
// InertialSensor       inertial      13              
// RotationLeft         rotation      20              
// RotationRight        rotation      7               
// LeftMotors           motor_group   3, 5            
// RightMotors          motor_group   2, 1            
// Controller1          controller                    
// CataLimit            limit         A               
// IntakePistonLeft     digital_out   D               
// IntakePistonRight    digital_out   C               
// WingPistonLeft       digital_out   G               
// WingPistonRight      digital_out   E               
// IntakeMotor          motor_group   11, 12          
// Rotation9            rotation      19              
// CatapultMotor        motor_group   8, 6            
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// GPS9                 gps           18              
// GPS8                 gps           21              
// InertialSensor       inertial      13              
// RotationLeft         rotation      20              
// RotationRight        rotation      7               
// LeftMotors           motor_group   3, 5            
// RightMotors          motor_group   2, 1            
// Controller1          controller                    
// CataLimit            limit         A               
// IntakePistonLeft     digital_out   D               
// IntakePistonRight    digital_out   C               
// WingPistonLeft       digital_out   G               
// WingPistonRight      digital_out   E               
// IntakeMotor          motor_group   11, 12          
// Rotation9            rotation      19              
// CatapultMotor        motor_group   8, 6            
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// GPS9                 gps           18              
// GPS8                 gps           21              
// InertialSensor       inertial      13              
// RotationLeft         rotation      20              
// RotationRight        rotation      7               
// LeftMotors           motor_group   3, 5            
// RightMotors          motor_group   2, 1            
// Controller1          controller                    
// CataLimit            limit         A               
// IntakePistonLeft     digital_out   D               
// IntakePistonRight    digital_out   C               
// WingPistonLeft       digital_out   G               
// WingPistonRight      digital_out   E               
// IntakeMotor          motor_group   11, 12          
// Rotation9            rotation      19              
// ---- END VEXCODE CONFIGURED DEVICES ----

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


  // Extend Intake
  robot.intake.ExtendIntake();

  // Freeze Robot
  LeftMotors.stop(hold);
  RightMotors.stop(hold);

  // Match Load
  //robot.catapult.StartCatapultMatchLoading();

  // Face hallway
  robot.base.RotateLocally(334, 25, 5);
  robot.catapult.RetractCatapult();
  waitUntil(Rotation9.angle() < 300);
  CatapultMotor.stop(hold);

  // Drive through hallway
  robot.base.ForwardLocally(-33, 75, 10);
  wait(0.2, sec);

  // Reset heading
  InertialSensor.setHeading(10, degrees);

  // Turn right out of hallway
  robot.base.RotateLocally(84, 25, 5);
  wait(0.2, sec);

  // Move out of hallway
  robot.base.ForwardLocally(-39, 75, 10);
  wait(0.2, sec);

  // Face barrier
  robot.base.RotateLocally(183, 25, 5);
  wait(0.2, sec);

  // Reset rotation sensors
  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

  // Move towards barrier
  robot.base.ForwardLocally(-12, 75, 10);
  wait(0.2, sec);

  // Turn
  robot.base.RotateLocally(108, 25, 5);
  wait(0.2, sec);

  // Reset rotation sensors
  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

  // Align wtih goal for first push
  robot.base.ForwardLocally(-12, 75, 10);
  wait(0.2, sec);

  // Face goal
  robot.base.RotateLocally(20, 25, 5);
  wait(0.2, sec);

  // Push nuts into goal
  robot.wings.ExtendWings();
  robot.base.ForwardLocally(-22, 100, 10);

  // Face away from goal for second push
  robot.base.RotateLocally(145, 25, 5);
  wait(0.2, sec);

  // Reset rotation sensors
  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

  // Back up
  robot.base.ForwardLocally(-16, 50, 10);

  // Face goal again
  robot.base.RotateLocally(22, 25, 5);
  wait(0.2, sec);

  // Reset rotation sensors
  RotationLeft.setPosition(0, degrees);
  RotationRight.setPosition(0, degrees);

  // Push more nuts into goal
  robot.base.ForwardLocally(-20, 100, 10);

}

void DriverControls() {

  /////////////////////////
  // Drivetrain Controls //
  /////////////////////////

  LeftMotors.spin(forward, (Controller1.Axis3.value() + (Controller1.Axis1.value() * 0.35) * 2), percent);
  RightMotors.spin(forward, (Controller1.Axis3.value() - (Controller1.Axis1.value() * 0.35) * 2), percent);

  /////////////////////
  // Intake Controls //
  /////////////////////

  if (Controller1.ButtonR2.pressing()) {

    // Enable and disable intake with every other R2 press
    if (robot.intakeEnabled) { 
      robot.DisableIntake();
    } else { 
      robot.EnableIntake(); 
    }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
  }

  if (Controller1.ButtonR1.pressing()) {
    
    // Enable and disable reverse intake with every other R2 press
    if (robot.intakeEnabled) { 
      robot.DisableIntake(); 
    } else { 
      robot.ReverseIntake(); 
    }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
  }

  ///////////////////////
  // Catapult Controls //
  ///////////////////////

  // Check if catapult is within stopping range
  if ((Rotation9.angle() < 300) && (Rotation9.angle() > 280)) {

    CatapultMotor.stop(hold);

    // Check for user input to launch cata
    if (Controller1.ButtonB.pressing()) {

      CatapultMotor.spin(forward, 100, percent);

      // Wait so the brain doesnt recieve a million pressing() calls in one press
      wait(0.2, sec);
    }
  }

  ///////////////////
  // Wing Controls //
  ///////////////////

  if (Controller1.ButtonA.pressing()) {

    // Extend and retract wings with every other A press
    if (robot.wingsExtended) { 
      robot.RetractWings(); 
    } else { 
      robot.ExtendWings(); 
    }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
  }

  if (Controller1.ButtonLeft.pressing()) {

    // Extend and retract wings with every other A press
    if (robot.intakeExtended) { 
      robot.RetractIntake(); 
    } else { 
      robot.ExtendIntake(); 
    }

    // Wait so the brain doesnt recieve a million pressing() calls in one press
    wait(0.2, sec);
  }
}


void usercontrol(void) {
   robot.catapult.StartCatapultMatchLoading();
  while (1) {
    //robot.base.TrackPositionAndHeading();
    DriverControls();
    wait(20, msec);
  }
}

int main() {

  Rotation9.setPosition(0, degrees);
  CatapultMotor.spin(forward, 100, percent); 
  robot.intake.ExtendIntake();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();
 
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
