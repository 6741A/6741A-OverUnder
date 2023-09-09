#include "vex.h"
#include "Robot.h"
#include "Catapult.h"
#include "Intake.h"
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

// Intake Functionality

Intake intake;

void Robot::EnableIntake()
{ intake.EnableIntake(); }

void Robot::ReverseIntake()
{ intake.ReverseIntake(); }

void Robot::DisableIntake()
{ intake.DisableIntake(); }

void Robot::ExtendIntake()
{ intake.ExtendIntake(); }

void Robot::RetractIntake()
{ intake.RetractIntake(); }

// Wings Functionality

Wings wings;

void Robot::ExtendWings()
{ wings.ExtendWings(); }

void Robot::RetractWings()
{ wings.RetractWings(); }

