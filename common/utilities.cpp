#include "utilities.hpp"
#include <iostream>

Guard::Guard(std::istream& inStream) :
  stream_(inStream),
  flags_(inStream.flags())
{
}

Guard::~Guard()
{
  stream_.setf(flags_);
}

std::istream& skipSpaces(std::istream& in)
{
  while (isblank(in.peek()))
  {
    in.get();
  }

  return in;
}


