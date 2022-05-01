#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <iterator>

void taskOne(std::istream& in, std::ostream& out)
{
  std::unordered_set<std::string> set((std::istream_iterator<std::string>(in)), std::istream_iterator<std::string>());

  if (!in.eof())
  {
    throw std::runtime_error("Reading failed");
  }

  std::copy(set.begin(), set.end(), std::ostream_iterator<std::string>(out, "\n"));
}
