#include "vex.h"
#include "Base.h"
#include "Catapult.h"

#pragma once
#ifndef ROBOT_H
#define ROBOT_H

class Robot
{ 

  public:

    // Catapult Functionality
    void StartCatapultMatchLoading();
    void RetractCatapult();
    void LaunchCatapult();

    // Drivetrain Functionality
    void Rotate (float a, float b);
    void DriveForward (float a, float b);
    void GoTo (float a, float b , float c, float d);
  
};

#endif

