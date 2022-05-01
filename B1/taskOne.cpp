#include <list>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include "sorting.hpp"
#include "access.hpp"
#include "general.hpp"

void taskOne(const char* sortCriterion)
{
  int value = 0;
  std::vector<int> vector;

  while (std::cin >> value)
  {
    vector.push_back(value);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("Reading failed");
  }

  std::vector<int> vectorAt = vector;
  std::list<int> vectorIterator(vector.begin(), vector.end());

  std::function<bool(const int&, const int&)> sortCrit = getSortCriterion<int>(sortCriterion);

  sort<OperatorAccess>(vector, sortCrit);
  print(vector);

  sort<AtAccess>(vectorAt, sortCrit);
  print(vectorAt);

  sort<IteratorAccess>(vectorIterator, sortCrit);
  print(vectorIterator);
}
