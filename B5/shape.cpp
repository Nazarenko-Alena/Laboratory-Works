#include "shape.hpp"
#include <iostream>
#include <iterator>
#include <cmath>
#include "utilities.hpp"

const int TRIANGLE_VERTICES = 3;
const int RECTANGLE_VERTICES = 4;
const int PENTAGON_VERTICES = 5;

std::istream& operator>>(std::istream& in, Shape& shape)
{
  std::istream::sentry sentry(in);

  if (sentry)
  {
    size_t numberVertices;

    Guard guard(in);
    in >> std::noskipws;

    in >> std::ws >> skipSpaces >> numberVertices;

    Shape tmpShape(numberVertices);

    for (size_t i = 0; i < numberVertices; i++)
    {
      Point point;
      if (!(in >> skipSpaces >> point))
      {
        return in;
      }
      tmpShape[i] = point;
    }

    shape = std::move(tmpShape);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  std::ostream::sentry sentry(out);

  if (sentry)
  {
    out << shape.size() << ' ';

    std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(out, " "));
  }

  return out;
}

bool isOrthogonal(const Point& vertex1, const Point& vertex2, const Point& vertex3)
{
  return (vertex2.x - vertex1.x) * (vertex2.x - vertex3.x) + (vertex2.y - vertex1.y) * (vertex2.y - vertex3.y) == 0;
}

bool isRect(const Shape& shape)
{
  return (shape.size() == RECTANGLE_VERTICES) && isOrthogonal(shape[0], shape[1], shape[2])
      && isOrthogonal(shape[1], shape[2], shape[3]) && isOrthogonal(shape[2], shape[3], shape[0]);
}

bool isSqr(const Shape& shape)
{
  if (!isRect(shape))
  {
    return false;
  }

  size_t sumSquares1 = (shape[0].x - shape[1].x) * (shape[0].x - shape[1].x) +
                       (shape[0].y - shape[1].y) * (shape[0].y - shape[1].y);

  size_t sumSquares2 = (shape[1].x - shape[2].x) * (shape[1].x - shape[2].x) +
                       (shape[1].y - shape[2].y) * (shape[1].y - shape[2].y);

  return (sumSquares1 == sumSquares2);
}

ShapeType getType(const Shape& shape)
{
  if (shape.size() == TRIANGLE_VERTICES)
  {
    return ShapeType::TRIANGLE;
  }

  if ((shape.size() == RECTANGLE_VERTICES) && (isRect(shape)))
  {
    if (isSqr(shape))
    {
      return ShapeType::SQUARE;
    }

    return ShapeType::RECTANGLE;
  }

  if (shape.size() == PENTAGON_VERTICES)
  {
    return ShapeType::PENTAGON;
  }

  return ShapeType::OTHER;
}

