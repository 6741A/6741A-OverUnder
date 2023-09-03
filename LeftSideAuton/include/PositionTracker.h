#include "vex.h"

#pragma once
#ifndef POSITIONTRACKER_H
#define POSITIONTRACKER_H

class PositionTracker
{

  public:

    float robotXPosition, robotYPosition, robotOrientation;

    void UpdateSensorValues();

    void CalculatePosition();

    void CalculateHeading();

    void TrackPositionAndHeading();

    void FieldVisualizer();

};

#endif 