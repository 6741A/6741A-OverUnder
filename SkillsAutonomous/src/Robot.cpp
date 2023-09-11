#include "vex.h"
#include "Robot.h"
#include "Catapult.h"
#include "Intake.h"
#include "Base.h"

using namespace vex;


// Catapult Functionality

Catapult catapult;

bool cataDrawed = false;

void Robot::StartCatapultMatchLoading()
{ catapult.StartCatapultMatchLoading(); }

void Robot::RetractCatapult()
{ catapult.RetractCatapult(); cataDrawed = true; }

void Robot::LaunchCatapult()
{ catapult.LaunchCatapult(); cataDrawed = false; }

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

bool intakeEnabled = false;

void Robot::EnableIntake()
{ intake.EnableIntake(); intakeEnabled = true; }

void Robot::ReverseIntake()
{ intake.ReverseIntake(); intakeEnabled = true; }

void Robot::DisableIntake()
{ intake.DisableIntake(); intakeEnabled = false; }

void Robot::ExtendIntake()
{ intake.ExtendIntake(); }

void Robot::RetractIntake()
{ intake.RetractIntake(); }

// Wings Functionality

Wings wings;

bool wingsExtended;

void Robot::ExtendWings()
{ wings.ExtendWings(); wingsExtended = true; }

void Robot::RetractWings()
{ wings.RetractWings(); wingsExtended = false; }

