#include "SpotLight.h"
#include <math.h>

SpotLight::SpotLight(){} //constructor

#define ANGLE_PER_HOUR (M_PI/6.0)
#define ANGLE_PER_MINUTE (ANGLE_PER_HOUR/60.0)
#define RADIUS 100 // pixels
#define OUTER_RADIUS (M_SQRT2 * RADIUS)

// calculate the angle of the hour hand in ANGLE
double SpotLight::timeAngle() {
  return currentTime.Hour * ANGLE_PER_HOUR + currentTime.Minute * ANGLE_PER_MINUTE;
}

// draw a line through the center of the screen
// we overdraw to a circle circumscribing the screen
// perhaps a little bit wasteful, like 80 pixels
void SpotLight::centeredLine(double angle) {
  double sina = sin(angle);
  double cosa = cos(angle);
  display.drawLine( fma( sina, OUTER_RADIUS, RADIUS), fma(-cosa, OUTER_RADIUS, RADIUS), 
                    fma(-sina, OUTER_RADIUS, RADIUS), fma( cosa, OUTER_RADIUS, RADIUS), GxEPD_BLACK);

  // let's draw them a little fat
  double lo_sina = sin(angle - ANGLE_PER_MINUTE * 2.0);
  double lo_cosa = cos(angle - ANGLE_PER_MINUTE * 2.0);
  double hi_sina = sin(angle + ANGLE_PER_MINUTE * 2.0);
  double hi_cosa = cos(angle + ANGLE_PER_MINUTE * 2.0);

  display.drawLine( fma( lo_sina, OUTER_RADIUS, RADIUS), fma(-lo_cosa, OUTER_RADIUS, RADIUS), 
                    fma(-hi_sina, OUTER_RADIUS, RADIUS), fma( hi_cosa, OUTER_RADIUS, RADIUS), GxEPD_BLACK);
  display.drawLine( fma( hi_sina, OUTER_RADIUS, RADIUS), fma(-hi_cosa, OUTER_RADIUS, RADIUS), 
                    fma(-lo_sina, OUTER_RADIUS, RADIUS), fma( lo_cosa, OUTER_RADIUS, RADIUS), GxEPD_BLACK);
}

// draw a 200x200 window from the source bitmap 
// centered on a point on a circle 200px radius
// around 300, 300 where it intersects with the
// computed angle of the time.
void SpotLight::drawWindow(double angle) {
  double sina = sin(angle);
  double cosa = cos(angle);

  int x = fma( sina, RADIUS * 2, RADIUS * 2);
  int y = fma(-cosa, RADIUS * 2, RADIUS * 2);

  display.drawBitmap(-x,-y,spotFace,600,600,GxEPD_WHITE,GxEPD_BLACK);
}

void SpotLight::drawWatchFace() {
  double angle = timeAngle();
  drawWindow(angle);
  centeredLine(angle);
}
