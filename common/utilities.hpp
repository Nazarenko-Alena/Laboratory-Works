#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>

class Guard
{
public:
  Guard(std::istream& inStream);
  ~Guard();
private:
  std::istream& stream_;
  std::istream::fmtflags flags_;
};

std::istream& skipSpaces(std::istream& in);

#endif
