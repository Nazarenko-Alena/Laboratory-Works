#include <list>
#include <iostream>
#include "queueWithPriority.hpp"

void taskTwo(std::istream& in, std::ostream& out)
{
  std::list<int> list;
  const size_t maxSize = 20;
  int value = 0;
  const int min = 1;
  const int max = 20;
  size_t count = 0;
 
  while (in >> value)
  {
    if (count >= maxSize)
    {
      throw std::out_of_range("More than 20 numbers entered");
    }

    if ((value < min) || (value > max))
    {
      throw std::out_of_range("Incorrect value");
    }
    
    list.push_back(value);
    count++;
  }

  if (!in.eof())
  {
    throw std::runtime_error("Readed fail");
  }

  std::list<int>::iterator begin = list.begin();
  std::list<int>::iterator end = list.end();

  while (begin != end)
  {
    std::cout << *begin;

    if (std::next(begin) == end)
    {
      break;
    }

    if (std::next(begin) == std::prev(end))
    {
      out << " " << *(--end);
      break;
    }

    begin++;
    end--;
    std::cout << " " << *end << " ";
  }

  std::cout << '\n';
}
