#include "general.hpp"
#include <iostream>
#include <numeric>
#include <iterator>
#include <algorithm>

size_t countVeritcies(const std::list<Shape>& shapes)
{
  auto operation = [](size_t sum, const Shape& el) { return sum += el.size(); };
  return std::accumulate(shapes.begin(), shapes.end(), 0, operation);
}

void removePentagons(std::list<Shape>& shapes)
{
  auto check = [](const Shape& elem) { return getType(elem) == ShapeType::PENTAGON; };
  auto newEnd = std::remove_if(shapes.begin(), shapes.end(), check);
  shapes.erase(newEnd, shapes.end());
}

std::ostream& operator<<(std::ostream& out, const CountFigures& elem)
{
  out << "Triangles: " << elem.numberOfTriangles << '\n'
    << "Squares: " << elem.numberOfSquares << '\n'
    << "Rectangles: " << elem.numberOfRectangles << '\n' << "Points: ";

  return out;
}


