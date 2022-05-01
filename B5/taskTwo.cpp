#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include "shape.hpp"
#include "general.hpp"

void taskTwo(std::istream& in, std::ostream& out)
{
  std::list<Shape> shapes((std::istream_iterator<Shape>(in)), std::istream_iterator<Shape>());

  if (!in.eof())
  {
    throw std::runtime_error("Reading in the second task failed");
  }

  size_t numberOfVeritcies = countVeritcies(shapes);

  auto count = std::for_each(shapes.begin(), shapes.end(), CountFigures());

  removePentagons(shapes);

  std::vector<Point> points(shapes.size());

  auto operation = [](const Shape& elem) { return elem[0]; };

  std::transform(shapes.begin(), shapes.end(), points.begin(), operation);

  shapes.sort([](const Shape& shapeOne, const Shape& shapeTwo) { return getType(shapeOne) < getType(shapeTwo); });

  out << "Vertices: " << numberOfVeritcies << '\n' << count;

  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));

  out << '\n' << "Shapes: " << '\n';

  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}



