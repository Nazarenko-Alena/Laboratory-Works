#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>
#include "point.hpp"

enum ShapeType
{
  TRIANGLE,
  SQUARE,
  RECTANGLE,
  PENTAGON,
  OTHER
};

using Shape = std::vector<Point>;

std::istream& operator>>(std::istream& in, Shape& shape);
std::ostream& operator<<(std::ostream& out, const Shape& shape);

ShapeType getType(const Shape& shape);

#endif

