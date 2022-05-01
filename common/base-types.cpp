#include "base-types.hpp"
#include <iostream>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath>

bool nazarenko::details::checkingOverlapRect(const rectangle_t& rectOne, const rectangle_t& rectTwo)
{
  return ((abs(rectOne.pos.x - rectTwo.pos.x) < (rectOne.width / 2 + rectTwo.width / 2)) &&
          (abs(rectOne.pos.y - rectTwo.pos.y) < (rectOne.height / 2 + rectTwo.height / 2)));
}

void nazarenko::details::moveToRotate(double angle, const point_t& stationaryPoint, point_t& pointOfRotation)
{
  const double sin = std::sin(M_PI * angle / 180);
  const double cos = std::cos(M_PI * angle / 180);
  double moveOnX = cos * (pointOfRotation.x - stationaryPoint.x) - sin * (pointOfRotation.y - stationaryPoint.y);
  double moveOnY = sin * (pointOfRotation.x - stationaryPoint.x) + cos * (pointOfRotation.y - stationaryPoint.y);
  pointOfRotation = { stationaryPoint.x + moveOnX, stationaryPoint.y + moveOnY };
}
