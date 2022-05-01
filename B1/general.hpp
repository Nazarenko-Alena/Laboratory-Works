#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <functional>

template <typename T>
std::function <bool(const T&, const T&)> getSortCriterion(const char* sortCriterion)
{
  if (sortCriterion == nullptr)
  {
    throw std::invalid_argument("Incorrect criterion");
  }

  if (std::strcmp(sortCriterion, "ascending") == 0)
  {
    return std::greater<const T>();
  }
  else if (std::strcmp(sortCriterion, "descending") == 0)
  {
    return std::less<const T>();
  }
  else
  {
    throw std::invalid_argument("Incorrect argument");
  }
}

template <typename T>
void print(const T& collection)
{
  for (typename T::const_iterator i = collection.begin(); i != collection.end(); i++)
  {
    std::cout << *i << " ";
  }
  std::cout << '\n';
}

#endif 
