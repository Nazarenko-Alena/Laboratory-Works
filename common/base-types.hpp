#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace nazarenko
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

  namespace details
  {
    bool checkingOverlapRect(const rectangle_t& rectOne, const rectangle_t& rectTwo);
    void moveToRotate(double angle, const point_t& stationaryPoint, point_t& pointOfRotation);
  }
}

#endif 
