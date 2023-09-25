#include "vex.h"
#include "PositionTracker.h"
#include "PIDTemplate.h"

#pragma once
#ifndef BASE_H
#define BASE_H

class Base : public PositionTracker
{

  public:

    PositionTracker posTracker;

    void TurnRobot (float a, float b);

    void DriveRobot (float a);

    void Rotate (float a, float b);

    void DriveForward (float a, float b);

    void GoTo (float a, float b , float c, float d);

    void RotateLocally(float a, float b);

    void ForwardLocally(float a, float b, float c);



};

#endif
