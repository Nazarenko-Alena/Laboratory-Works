#include <vector>
#include <cstring>
#include <random>
#include <ctime>
#include "sorting.hpp"

void fillRandom(double* array, int size)
{
  std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> distrib(-1, 1);
  for (int i = 0; i < size; i++)
  {
    array[i] = distrib(gen);
  }
}

void taskFour(const char* sortCriterion, const size_t size)
{
  if (size == 0)
  {
    throw std::invalid_argument("Incorrect size");
  }

  std::function<bool(double, double)> sortCrit = getSortCriterion<double>(sortCriterion);

  std::vector<double> vector(size);
  fillRandom(&vector[0], size);

  print(vector);

  sort<IteratorAccess>(vector, sortCrit);
  print(vector);
}
