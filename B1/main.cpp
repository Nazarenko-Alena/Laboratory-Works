#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

void taskOne(const char* sortCriterion);
void taskTwo(const char* fileName);
void taskThree();
void taskFour(const char* sortCriterion, const size_t size);

int main(int argc, char* argv[])
{
  try
  {
    if (argc < 2)
    {
      std::cerr << "Incorrect argc";
      return 1;
    }

    std::stringstream string(argv[1]);

    int task;
    string >> task;

    if (!string)
    {
      std::cerr << "Reading failed";
      return 1;
    }

    switch (task)
    {
    case 1: {
      if (argc < 3)
      {
        std::cerr << "Incorrect argc";
        return 1;
      }
      taskOne(argv[2]);
      break;
    }

    case 2: {
      if (argc < 3)
      {
        std::cerr << "Incorrect argc";
        return 1;
      }
      taskTwo(argv[2]);
      break;
    }

    case 3: {
      taskThree();
      break;
    }

    case 4: {
      if (argc < 4)
      {
        std::cerr << "Incorrect argc";
        return 1;
      }
      std::stringstream myString (argv[3]);

      int size;
      myString >> size;

      if (!myString)
      {
        std::cerr << "Reading failed";
        return 1;
      }
      
      taskFour(argv[2], size);
      break;
    }

    default: {
      std::cerr << "Incorrect task number";
      return 1;
    }
    }
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (const std::runtime_error& error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (const std::bad_alloc& error)
  {
    std::cerr << error.what();
    return 1;
  }
  return 0;
}
