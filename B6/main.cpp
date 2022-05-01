#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include "statistic.hpp"

int main()
{
  Statistic stat;
  stat = std::for_each(std::istream_iterator<long int>(std::cin), std::istream_iterator<long int>(), stat);
  if (!std::cin.eof())
  {
    std::cerr << ("Reading failed");
    return 1;
  }
  std::cout << stat;
  return 0;
}
