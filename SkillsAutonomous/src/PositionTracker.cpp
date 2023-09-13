// Handles the position tracking procedures, contains odometry algorithm ~~

#include "PositionTracker.h"
#include "vex.h"

using namespace vex;

// DRIVETRAIN SPECS CONSTANTS ~~ TUNE THESE !

// Distance from tracking center to middle of left wheel in inches
const float SL = 5;

// Distance from tracking center to middle of right wheel in inches
const float SR = 5;

// Diameter of tracking wheels in inches
const float wheelCircumference = (3.25 * 2 * M_PI);

// Degrees per single sensor rotation
const float degreesPerRotation = 360;

// Scale of the field for brain visualizer
const float fieldscale = 1.66548042705;

// ODOMETRY ALGORITHM VARIABLES ~~ DONT TOUCH THESE !

// Change in left and right rotational sensor values
float deltaLeft, deltaRight;

// Current left and right rotational sensor values
float currentLeft, currentRight;

// Previous left and right rotational sensor values
float previousLeft, previousRight;

// Change in heading, current heading
float deltaTheta, Theta;

// Intermediate X and Y Position calculations
float X, Y;

// Final X and Y Positions
float combinedX, combinedY;

// Change in X and Y Position
float deltaX, deltaY;

// Chord for calculating change with arc, absolute heading, final heading
float sideChord, absHeading, combinedHeading;

// Average GPS positional values
float averageGPSX, averageGPSY;

// Global robot positional values
float robotXPosition, robotYPosition, robotOrientation;

/*

UpdateSensorValues: Updates the rotational sensor values, then calculates the
change in these values by subtracting their previous value, and converts it
to distance travelled. Finally, it calculates the change in heading using the
following formula:

deltaTheta = (deltaL - deltaR) / (sL + sR)

*/

void PositionTracker::UpdateSensorValues() 
{

  // Updates left and right rotation sensor values
  currentLeft = (RotationLeft.position(degrees));
  currentRight = (RotationRight.position(degrees));

  // Calculates change in inches travelled
  deltaLeft = ((currentLeft - previousLeft) * wheelCircumference) / degreesPerRotation;
  deltaRight = ((currentRight - previousRight) * wheelCircumference) / degreesPerRotation;

  // Calculates change in robot heading
  deltaTheta = (deltaRight - deltaLeft) / (SL + SR);

}

/*

CalculatePosition: first checks to see if robot is driving straight, or
rotating. If it's driving straight, it can simply add the change in distance
travelled taking heading into account. If it's rotating, it's forming an arc,
and you can then use chords to calculate the distance formed by the arc.
Additionally, after calculating with odometry, it checks each of the two GPS
sensors for which one has the most accurate reading. If theyre both reasonably
accurate, it will take the average of their readings and insert that into the
position calculation. If one is more accurate than the other, it will only use
it's reading.

*/

void PositionTracker::CalculatePosition() 
{

  // True if there is no change in robot heading
  if (deltaTheta == 0) 
  {

    // Calculate X and Y Position using forward travel formula for their
    // respective values.
    X += deltaLeft * sin(Theta);
    Y += deltaLeft * cos(Theta);

  }
  // Otherwise, robot is curving, thus the length of the arc formed can be
  // determined
  else 
  {

    // Calculate chord length with formula
    sideChord = 2 * ((deltaLeft / deltaTheta) + SL) * sin(deltaTheta / 2);

    // Calculate change in X and Y position using chord
    deltaX = sideChord * sin(Theta + (deltaTheta / 2));
    deltaY = sideChord * cos(Theta + (deltaTheta / 2));

    // Add change in heading to cumulative heading
    Theta += deltaTheta / 2;

    // Add change in X and Y position to cumulative X and Y position
    X += deltaX / 2;
    Y -= deltaY / 2;

  }

  // True if the reading quality difference between either GPS is within 2, use
  // both
  if (abs(GPS9.quality() - GPS8.quality()) < 2) 
  {

    // Calculate average GPS X and Y Position
    averageGPSX = (GPS9.xPosition(inches) + GPS8.xPosition(inches)) / 2;
    averageGPSY = (GPS9.yPosition(inches) + GPS8.yPosition(inches)) / 2;

    // Calculate average between odometry X and GPS X, likewise with Y
    combinedX = (X + averageGPSX) / 2;
    combinedY = (Y + averageGPSY) / 2;

  }
  // True if the second GPS has higher reading quality than the first,
  // then only use that one to determine position
  else if (GPS9.quality() > GPS8.quality()) 
  {

    // Calculate average between odometry X and second GPS X, likewise with Y
    combinedX = (X + GPS9.xPosition(inches)) / 2;
    combinedY = (Y + GPS9.yPosition(inches)) / 2;

  }
  // True if the first GPS reading is higher than the second,
  // then only use that one to determine position
  else 
  {

    // Calculate average between odometry X and first GPS X, likewise with Y
    combinedX = (X + GPS8.xPosition(inches)) / 2;
    combinedY = (Y + GPS8.yPosition(inches)) / 2;
  }

}

/*

CalculateHeading: Combines the odometry heading value with the inertial sensor
heading value for percise heading measurements.

*/

void PositionTracker::CalculateHeading() 
{

  // Checks edge cases where the odomety heading calculation returns a value
  // over 360 degrees
  while (Theta > (2 * M_PI))
  {

    // Subtracts 360 until it is within the range 0-360
    Theta -= 2 * M_PI;

  }

  // Checks edge cases where odometry heading calculation returns a value under
  // 0 degrees
  while (Theta < 0) 
  {

    // Adds 360 until it is within the range 0-360
    Theta += 2 * M_PI;

  }

  // Checks edge case where the odometry value might be staggered from the
  // inertial value, such that one is in the 330+ range and the other is in the
  // 30- range
  if ((Theta * 180 / M_PI) > 330 && InertialSensor.heading(degrees) < 30) 
  {

    // Ignores inertial reading and defaults to odometry value
    combinedHeading = Theta;

  }
  // Checks edge case where the odometry value might be staggered from the
  // inertial value, such that one is in the 30- range and the other is in the
  // 330+ range
  else if ((Theta * 180 / M_PI) < 30 && InertialSensor.heading(degrees) > 330) 
  {

    // Ignores odometry reading and defaults to inertial reading, converted to
    // radians
    combinedHeading = InertialSensor.heading(degrees) * (M_PI / 180);

  }
  // Checks edge case where the difference between the odometry and inertial
  // reading is too great, above 40, and defaults to odometry value
  else if (abs(int(Theta * 180 / M_PI) - int(InertialSensor.heading(degrees))) > 40) 
  {

    // Ignores inertial reading and defaults to odometry value
    combinedHeading = Theta;

  }
  // In any other case, it has passed every edge case check
  else 
  {

    // Combines the heading by taking the average of the odometry value and
    // inertial reading
    combinedHeading = (((InertialSensor.heading(degrees) * 1.05) * (M_PI / 180)) + Theta * (M_PI / 180));

  }

}

/*

FieldVisualizer: Draws a field and a representation
of the robot and its heading onto the brain. Used for
debugging purposes. This visualizer was made by Sargarpatel.

*/

void PositionTracker::FieldVisualizer() 
{

  // Coordinates for each section of text
  int textadjustvalue = 55;
  int rowadjust = 39;

  // Sets graphical settings for display
  Brain.Screen.setPenWidth(1);
  vex::color redtile = vex::color(210, 31, 60);
  vex::color bluetile = vex::color(14, 77, 146);
  vex::color graytile = vex::color(49, 51, 53);
  Brain.Screen.setFillColor(vex::color(0, 0, 0));
  Brain.Screen.setFont(vex::fontType::mono20);
  Brain.Screen.setPenColor(vex::color(222, 49, 99));

  // Displays all the field tiles, text of odom values, and a dot symbolizing
  // the robot
  Brain.Screen.printAt(40, 20 + textadjustvalue, "X-Pos:%f", -robotXPosition);
  Brain.Screen.setPenColor(vex::color(191, 10, 48));
  Brain.Screen.printAt(40, 50 + textadjustvalue, "Y-Pos:%f", robotYPosition);
  Brain.Screen.setPenColor(vex::color(141, 2, 31));
  Brain.Screen.printAt(40, 80 + textadjustvalue, "Theta:%f", Theta);
  Brain.Screen.setPenColor(vex::color(83, 2, 1));
  Brain.Screen.printAt(40, 110 + textadjustvalue, "Angle:%f", robotOrientation);
  Brain.Screen.setPenColor(vex::color(255, 255, 255));
  Brain.Screen.setFillColor(graytile);
  Brain.Screen.drawRectangle(245, 2, 234, 234);
  Brain.Screen.drawRectangle(245, 2, 39, 39);
  Brain.Screen.drawRectangle(245, 80, 39, 39);
  Brain.Screen.drawRectangle(245, 119, 39, 39);
  Brain.Screen.drawRectangle(245, 197, 39, 39);
  Brain.Screen.drawRectangle(245 + rowadjust, 2, 39, 39);
  Brain.Screen.drawRectangle(245 + rowadjust, 41, 39, 39);
  Brain.Screen.drawRectangle(245 + rowadjust, 80, 39, 39);
  Brain.Screen.drawRectangle(245 + rowadjust, 119, 39, 39);
  Brain.Screen.drawRectangle(245 + rowadjust, 158, 39, 39);
  Brain.Screen.drawRectangle(245 + rowadjust, 197, 39, 39);
  Brain.Screen.drawRectangle(245 + (2 * rowadjust), 2, 39, 39);
  Brain.Screen.drawRectangle(245 + (2 * rowadjust), 41, 39, 39);
  Brain.Screen.drawRectangle(245 + (2 * rowadjust), 80, 39, 39);
  Brain.Screen.drawRectangle(245 + (2 * rowadjust), 119, 39, 39);
  Brain.Screen.drawRectangle(245 + (2 * rowadjust), 158, 39, 39);
  Brain.Screen.drawRectangle(245 + (2 * rowadjust), 197, 39, 39);
  Brain.Screen.drawRectangle(245 + (3 * rowadjust), 2, 39, 39);
  Brain.Screen.drawRectangle(245 + (3 * rowadjust), 41, 39, 39);
  Brain.Screen.drawRectangle(245 + (3 * rowadjust), 80, 39, 39);
  Brain.Screen.drawRectangle(245 + (3 * rowadjust), 119, 39, 39);
  Brain.Screen.drawRectangle(245 + (3 * rowadjust), 158, 39, 39);
  Brain.Screen.drawRectangle(245 + (3 * rowadjust), 197, 39, 39);
  Brain.Screen.drawRectangle(245 + (4 * rowadjust), 2, 39, 39);
  Brain.Screen.drawRectangle(245 + (4 * rowadjust), 41, 39, 39);
  Brain.Screen.drawRectangle(245 + (4 * rowadjust), 80, 39, 39);
  Brain.Screen.drawRectangle(245 + (4 * rowadjust), 119, 39, 39);
  Brain.Screen.drawRectangle(245 + (4 * rowadjust), 158, 39, 39);
  Brain.Screen.drawRectangle(245 + (4 * rowadjust), 197, 39, 39);
  Brain.Screen.drawRectangle(245 + (5 * rowadjust), 2, 39, 39);
  Brain.Screen.drawRectangle(245 + (5 * rowadjust), 80, 39, 39);
  Brain.Screen.drawRectangle(245 + (5 * rowadjust), 119, 39, 39);
  Brain.Screen.drawRectangle(245 + (5 * rowadjust), 197, 39, 39);
  Brain.Screen.setFillColor(redtile);
  Brain.Screen.drawRectangle(245, 158, 39, 39);
  Brain.Screen.drawRectangle(245, 41, 39, 39);
  Brain.Screen.setFillColor(bluetile);
  Brain.Screen.drawRectangle(245 + (5 * rowadjust), 41, 39, 39);
  Brain.Screen.drawRectangle(245 + (5 * rowadjust), 158, 39, 39);
  Brain.Screen.setPenColor(vex::color(255, 255, 255));
  Brain.Screen.setFillColor(vex::color(0, 0, 0));

  // This draws the robot body for position and arm for angle
  double yfieldvalue = ((-Y) * fieldscale) + 245 - 10;
  double xfieldvalue = ((-X) * fieldscale) + 245;
  Brain.Screen.drawCircle(xfieldvalue, yfieldvalue, 15);
  Brain.Screen.setPenWidth(4);

  // Line angle calculation:
  // x1 and y1 are the robot's coordinates, which in our case is xfieldvalue and
  // yfieldvalue angle is the angle the robot is facing, which in our case is
  // Theta (x1,y1, x1 + line_length*cos(angle),y1 + line_length*sin(angle)) =
  // (x1,y1,x2,y2)
  Brain.Screen.drawLine(xfieldvalue, yfieldvalue,
                        xfieldvalue + cos(Theta - (M_PI / 2)) * 15,
                        yfieldvalue + sin(Theta - (M_PI / 2)) * 15);

}

/*

TrackPositionAndHeading: The main position tracking algorithm, tracks the
position and heading of the robot and updates the global positional and
rotational values. Utilizes odometry algorithm to calculate position and
heading, then combines those values with GPS sensor positional readings, and
inertial sensor rotational readings.

*/

void PositionTracker::TrackPositionAndHeading() 
{

  UpdateSensorValues();
  CalculatePosition();
  CalculateHeading();

  // Resets previous values for next iteration
  previousLeft = currentLeft;
  previousRight = currentRight;

  // Resets change in angle for next iteration
  deltaTheta = 0;

  // Updates global X, Y, and Heading values (in degrees)
  robotXPosition = X;
  robotYPosition = Y;
  robotOrientation = (combinedHeading * (180 / M_PI));

  // Visualize field and robot on brain for debugging purposes
  FieldVisualizer();
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0, 0);
    Controller1.Screen.print(robotOrientation);
  // Wait every iteration to not overload brain
  wait(5, msec);

}

