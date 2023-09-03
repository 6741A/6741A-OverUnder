#include "vex.h"
#include "PositionTracker.h"
#include "PIDTemplate.h"

#pragma once
#ifndef MOVER_H
#define MOVER_H

class Mover : public PositionTracker
{

  public:

    PositionTracker posTracker;

    void TurnRobot (float a, float b);

    void DriveRobot (float a);

    void Rotate (float a, float b);

    void DriveForward (float a, float b);

    void GoTo (float a, float b , float c, float d);

};

#endif
