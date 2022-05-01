#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <vector>
#include <list>
#include "shape.hpp"

struct CountFigures {
  size_t numberOfTriangles, numberOfSquares, numberOfRectangles;

  CountFigures() :
    numberOfTriangles(0),
    numberOfSquares(0),
    numberOfRectangles(0)
  {}

  void operator()(const Shape& elem)
  {
    if (getType(elem) == ShapeType::TRIANGLE)
    {
      ++numberOfTriangles;
    }
    else if (getType(elem) == ShapeType::SQUARE)
    {
      ++numberOfSquares;
      ++numberOfRectangles;
    }
    else if (getType(elem) == ShapeType::RECTANGLE)
    {
      ++numberOfRectangles;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const CountFigures& elem);
};

size_t countVeritcies(const std::list<Shape>& shapes);
void removePentagons(std::list<Shape>& shapes);

#endif
