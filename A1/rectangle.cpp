#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(double height, double width, point_t pos):
  height_(height),
  width_(width),
  pos_(pos)
{
  assert((height_ > 0) && (width_ > 0));
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::move(const point_t& point)
{
  pos_ = point;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{ height_, width_, pos_ };
}

void Rectangle::print() const
{
  std::cout << "Height = " << height_ 
            << "  " << "Width = " << width_
            <<'\n';
  Shape::print();
}

point_t Rectangle::getCenter() const
{
  return pos_;
}
