#include "vex.h"
#include "Robot.h"
#include "Catapult.h"
#include "Base.h"

using namespace vex;


// Catapult Functionality

Catapult cata;

void Robot::StartCatapultMatchLoading()
{ cata.StartCatapultMatchLoading(); }

void Robot::RetractCatapult()
{ cata.RetractCatapult(); }

void Robot::LaunchCatapult()
{ cata.LaunchCatapult(); }

// Drivetrain Functionality

Base base;

void Robot::Rotate(float desiredHeading, float roomForError)
{ base.Rotate(desiredHeading, roomForError); }

void Robot::DriveForward(float targetDistance, float roomForError)
{ base.DriveForward(targetDistance, roomForError); }

void Robot::GoTo(float targetX, float targetY, float rotationError, float distanceError)
{ base.GoTo(targetX, targetY, rotationError, distanceError); }


