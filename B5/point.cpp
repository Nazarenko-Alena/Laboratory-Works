#include "point.hpp"
#include <iostream>
#include <stdexcept>
#include "utilities.hpp"

std::istream& operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);

  if (sentry)
  {
    Guard guard(in);
    in >> std::noskipws;

    if ((in >> skipSpaces).peek() != '(')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in.get();

    int x = 0;
    int y = 0;

    in >> skipSpaces >> x;

    if (in.fail())
    {
      return in;
    }

    if ((in >> skipSpaces).peek() != ';')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in.get();

    in >> skipSpaces >> y;
    if (in.fail())
    {
      return in;
    }

    if ((in >> skipSpaces).peek() != ')')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in.get();

    point = { x, y };
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

