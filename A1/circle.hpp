#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle :public Shape
{
public:
  Circle(double rad, point_t center);
  double getArea() const;
  void move(double dx, double dy);
  void move(const point_t& point);
  rectangle_t getFrameRect() const;
  void print() const;
  point_t getCenter() const;
private:
  double radius_;
  point_t center_;
};

#endif
