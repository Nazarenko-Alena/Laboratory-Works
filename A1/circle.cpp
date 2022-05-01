#include "circle.hpp"
#include <iostream>
#include <cassert>

#define _USE_MATH_DEFINES

#include <cmath>

Circle::Circle(double rad, point_t center) :
  radius_(rad),
  center_(center)
{
  assert(radius_ > 0);
}

double Circle::getArea() const 
{
  return M_PI * radius_ * radius_;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t& point)
{
  center_ = point;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, center_ };
}

void Circle::print() const
{
  std::cout << "Radius = " << radius_
            <<'\n';
  Shape::print();
}

point_t Circle::getCenter() const
{
  return center_;
}
