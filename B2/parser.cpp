#include "parser.hpp"
#include <sstream>
#include <stdexcept>
#include <functional>
#include <unordered_map>
#include "commands.hpp"

CommandFunction parseAdd(std::stringstream& stream)
{
  QueueWithPriority<std::string>::ElementPriority priorityData;

  std::string priority, data;
  stream >> priority >> std::ws;

  if (!stream)
  {
    return &printError;
  }

  std::getline(stream, data);

  if (data.empty())
  {
    return &printError;
  }

  if (priority == "high")
  {
    priorityData = QueueWithPriority<std::string>::ElementPriority::HIGH;
  }
  else if (priority == "normal")
  {
    priorityData = QueueWithPriority<std::string>::ElementPriority::NORMAL;
  }
  else if (priority == "low")
  {
    priorityData = QueueWithPriority<std::string>::ElementPriority::LOW;
  }
  else
  {
    return &printError;
  }

  return std::bind(&add, std::placeholders::_1, std::placeholders::_2, data, priorityData);
}

CommandFunction parseGet(std::stringstream& stream)
{
  std::string str;
  stream >> str;
  if (str.empty())
  {
    return &get;
  }
  else
  {
    return &printError;
  }
}

CommandFunction parseAccelerate(std::stringstream& stream)
{
  std::string str;
  stream >> str;
  if (str.empty())
  {
    return &accelerate;
  }
  else
  {
    return &printError;
  }
}

CommandFunction parse(std::stringstream& stream)
{
  std::string command;
  stream >> command;

  if (!stream)
  {
    return &printError;
  }

  const std::unordered_map<std::string, CommandFunction(*) (std::stringstream&)> commands
  {
    {"add", &parseAdd},
    {"get", &parseGet},
    {"accelerate", &parseAccelerate}
  };

  auto it = commands.find(command);

  if (it != commands.end())
  {
    return it->second(stream);
  }
  else
  {
    return &printError;
  }
}
