// Handles the position tracking procedures, contains odometry algorithm ~~

#include "Mover.h"
#include "PIDTemplate.h"
#include "PositionTracker.h"
#include "vex.h"

using namespace vex;

PositionTracker posTracker;

float wheelCircumference = 3.25;

/*

TurnRobot: Point-turns the robot to any desired heading with
any desired speed in percentage. Used in PID control loops

Arguments:
  output: this is the speed in percentage the robot should turn
  desiredHeading: this is the heading in degrees, from 0 to 360,
                  that the robot should face

*/

void Mover::TurnRobot(float output, float desiredHeading) 
{

  posTracker.TrackPositionAndHeading();

  // Calculation to determine which direction rotating to reach desired heading
  // is shortest
  float shortestTurn = ((int(posTracker.robotOrientation) - int(desiredHeading + (3 * M_PI)) % int((2 * M_PI)))) - M_PI;

  // If the calculated value is greater than zero, then rotation clockwise is
  // shorter
  if (shortestTurn > 0) 
  {

    // Rotate motors clockwise by output
    LeftMotors.spin(reverse, output, percent);
    RightMotors.spin(forward, output, percent);

  }
  // If the calculated value is less than zero, then rotation counterclockwise
  // is shorter
  else 
  {

    // Rotate motors counterclockwise by output
    LeftMotors.spin(forward, output, percent);
    RightMotors.spin(reverse, output, percent);

  }

}

/*

DriveRobot: drives the robot forward accoesing to output in percentage.
Used in PID control loops.

Arguments:
  output: this is the speed in which the drivetrain should move
          stationary at 0

*/

void Mover::DriveRobot(float output) 
{

  // Drives motors according to output
  LeftMotors.spin(reverse, output, percent);
  RightMotors.spin(reverse, output, percent);

}

/*

Rotate: Uses a PID Control Loop to accurately rotate the robot towards
the desired heading.


Arguments:
  desiredHeading: The target heading
  roomForError: The amount of error acceptable before ending loop

*/

PIDTemplate pid;

void Mover::Rotate(float desiredHeading, float roomForError) 
{

  while (true) 
  {

    posTracker.TrackPositionAndHeading();

    TurnRobot(pid.PIDControlLoop(2, 2, 2, desiredHeading, posTracker.robotOrientation, true), desiredHeading);

    // Print values to controller for debugging purposes
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0, 0);
    Controller1.Screen.print(pid.error);
    Controller1.Screen.print("    ");
    Controller1.Screen.print(posTracker.robotOrientation);

    if (abs(int(pid.error)) < roomForError) 
    {

      // Stop motors
      LeftMotors.stop();
      RightMotors.stop();

      // Print done for debugging purposes
      Controller1.Screen.clearScreen();
      Controller1.Screen.print("Done!");
      Controller1.Screen.print(posTracker.robotOrientation);

      // Exit control loop
      break;

    }

  }

}

/*

DriveForward: Uses a PID Control Loop to accurately drive a specific
dististance in inches.


Arguments:
  targetDistance: The target distance
  roomForError: The amount of error acceptable before ending loop

*/

void Mover::DriveForward(float targetDistance, float roomForError) 
{

  RotationLeft.setPosition(0, turns);
  RotationRight.setPosition(0, turns);

  targetDistance *= 3;

  while (true) 
  {

    posTracker.TrackPositionAndHeading();

    float rotations = ((RotationRight.position(turns) + RotationLeft.position(turns)) / 2) * wheelCircumference;

    DriveRobot(pid.PIDControlLoop(2, 2, 2, targetDistance, rotations, false));

    // Print values to controller for debugging purposes
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0, 0);
    Controller1.Screen.print(pid.error);
    Controller1.Screen.print("    ");
    Controller1.Screen.print(posTracker.robotOrientation);

    if (abs(int(pid.error)) < roomForError) 
    {

      // Stop motors
      LeftMotors.stop();
      RightMotors.stop();

      // Print done for debugging purposes
      Controller1.Screen.clearScreen();
      Controller1.Screen.print("Done!");
      Controller1.Screen.print(posTracker.robotOrientation);

      // Exit control loop
      break;

    }

  }

}

/*

GoTo: Allows robot to go to any specific point on the field. Combines
all previous functions within this class.


Arguments:
  targetX: Desired X Coordinate
  targetY: Desired Y Coordinate
  rotationError: The amount of error acceptable before ending rotation PID
  distanceError: The amount of error acceptable before ending distance PID

*/

void Mover::GoTo(float targetX, float targetY, float rotationError, float distanceError) 
{

  // Get current position.
  posTracker.TrackPositionAndHeading();

  // Calculate heading robot must face to point towards desired point
  float turnAngle = atan2((targetY - posTracker.robotYPosition),
                          (targetX - posTracker.robotXPosition));

  // Use PID to face point
  Rotate(turnAngle * (180 / M_PI), rotationError);

  // Calculate forward distance robot must travel to reach desired point
  float driveDistanceInches = sqrt((pow((targetX - posTracker.robotXPosition), 2)) +
                                   (pow((targetY - posTracker.robotYPosition), 2)));

  // Use PID to reach point
  DriveForward(driveDistanceInches, distanceError);

}