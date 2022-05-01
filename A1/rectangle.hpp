#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle:public Shape
{
public:
  Rectangle(double height2, double width2, point_t pos2);
  double getArea() const;
  void move(const double dx, const double dy);
  void move(const point_t& point);
  rectangle_t getFrameRect() const;
  void print() const;
  point_t getCenter() const;
private:
  double height_;
  double width_;
  point_t pos_;
};
#endif
