#include "circle.hpp"
#include <iostream>

#define _USE_MATH_DEFINES

#include <cmath>
#include "base-types.hpp"

nazarenko::Circle::Circle(double rad, const point_t& center) :
  radius_(rad),
  center_(center)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Incorrect radius");
  }
}

double nazarenko::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

void nazarenko::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void nazarenko::Circle::move(const point_t& point)
{
  center_ = point;
}

nazarenko::rectangle_t nazarenko::Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, center_ };
}

void nazarenko::Circle::print() const
{
  std::cout << "  Radius = " << radius_ << '\n';
  Shape::print();
}

nazarenko::point_t nazarenko::Circle::getCenter() const
{
  return center_;
}

double nazarenko::Circle::getRadius() const
{
  return radius_;
}

void nazarenko::Circle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect coefficient");
  }
  radius_ *= coefficient;
}

void nazarenko::Circle::rotate(double)
{
}
