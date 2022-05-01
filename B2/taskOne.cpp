#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "commands.hpp"
#include "queueWithPriority.hpp"
#include "parser.hpp"

void taskOne(std::istream& in, std::ostream& out)
{
  std::string str;
  QueueWithPriority<std::string> queue;

  while (std::getline(in, str))
  {
    std::stringstream stream(str);

    if ((stream >> std::ws).eof())
    {
      continue;
    }

    if (!stream)
    {
      throw std::runtime_error("Reading failed");
    }

    CommandFunction command = parse(stream);
    command(queue, out);
  }

  if (!in.eof())
  {
    throw std::runtime_error("Reading failed");
  }
}
