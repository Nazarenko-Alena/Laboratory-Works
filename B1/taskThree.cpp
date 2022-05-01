#include <iostream>
#include <vector>
#include "general.hpp"

void taskThree()
{
  int value = 1;
  std::vector<int> vector;
  while (std::cin >> value)
  {
    if (value == 0)
    {
      break;
    }
    vector.push_back(value);
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Reading failed");
  }

  if (vector.empty())
  {
    return;
  }
  if (value != 0)
  {
    throw std::invalid_argument("Incorrect argument");
  }
  if (vector.back() == 1)
  {
    for (auto i = vector.begin(); i != vector.end();)
    {
      if (*i % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        i++;
      }
    }
  }
  else if (vector.back() == 2)
  {
    for (auto i = vector.begin(); i != vector.end();)
    {
      if (*i % 3 == 0)
      {
        i = vector.insert(++i, 3, 1) + 3;
      }
      else
      {
        i++;
      }
    }
  }

  print(vector);
}
