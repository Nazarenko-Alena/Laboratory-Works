#include <fstream>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>
#include <memory>

void taskTwo(const char* fileName)
{
  if (fileName == nullptr)
  {
    throw std::invalid_argument("Incorrect file name");
  }
  std::ifstream file(fileName);
  if (!file)
  {
    throw std::runtime_error("File not open");
  }

  size_t maxSize = 128;
  size_t index = 0;
  std::unique_ptr<char[], decltype(&free)> arr(static_cast<char*>(calloc(maxSize, sizeof(char))), &free);
  if (!arr)
  {
    throw std::bad_alloc();
  }

  while (file)
  {
    file.read(&arr[index], maxSize - index);
    index += file.gcount();
    if (index == maxSize)
    {
      maxSize *= 2;
      std::unique_ptr<char[], decltype(&free)> tmp(static_cast<char*>(realloc(arr.get(), maxSize)), &free);
      if (!tmp)
      {
        throw std::bad_alloc();
      }
      std::swap(tmp, arr);
      tmp.release();
    }
  }

  std::vector<char> vector(arr.get(), arr.get() + index);

  for (auto i = vector.begin(); i != vector.end(); i++)
  {
    std::cout << *i;
  }
}
