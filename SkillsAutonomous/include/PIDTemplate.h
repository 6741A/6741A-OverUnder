#include "vex.h"

#pragma once
#ifndef PIDTEMPLATE_H
#define PIDTEMPLATE_H

class PIDTemplate
{

  public:

    float error;
    float previousError;

    float PIDControlLoop(float a, float b, float c, float d, float e, bool f);

};

#endif
