#ifndef DIVIDING_BY_LAYERS_HPP
#define DIVIDING_BY_LAYERS_HPP

#include "matrix-shape.hpp"
#include "shape.hpp"

namespace nazarenko
{
  MatrixShape divideByLayers(const Shape::ShapeArray& array, size_t countArray);
}

#endif 
