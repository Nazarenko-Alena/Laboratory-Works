#include "commands.hpp"
#include <iostream>
#include "queueWithPriority.hpp"


void add(QueueWithPriority<std::string>& queue, std::ostream&, std::string& data, QueueWithPriority<std::string>::ElementPriority priorityData)
{
  queue.putElement(data, priorityData);
}

void get(QueueWithPriority<std::string>& queue, std::ostream& out)
{
  if (queue.empty())
  {
    out << "<EMPTY>\n";
    return;
  }

  out << queue.getElement() << '\n';
  queue.deleteElement();
}

void accelerate(QueueWithPriority<std::string>& queue, std::ostream&)
{
  queue.accelerate();
}

void printError(QueueWithPriority<std::string>&, std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}
