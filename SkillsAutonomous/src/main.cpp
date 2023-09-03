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
// GPS9                 gps           9               
// GPS8                 gps           21              
// InertialSensor       inertial      1               
// RotationLeft         rotation      5               
// RotationRight        rotation      3               
// LeftMotors           motor_group   8, 10           
// RightMotors          motor_group   6, 7            
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "PositionTracker.h"
#include "Mover.h"

using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) 
{
  
  // test
  
  vexcodeInit();

}

// Instantiate Mover class object
Mover mover;

void autonomous(void) 
{


}


void usercontrol(void) 
{

  while (1) 
  {

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
    mover.FieldVisualizer();
    wait(100, msec);
  }
  
}
