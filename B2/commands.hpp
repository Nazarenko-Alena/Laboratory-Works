#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iostream>
#include "queueWithPriority.hpp"

void add(QueueWithPriority<std::string>& queue, std::ostream&, std::string& data, QueueWithPriority<std::string>::ElementPriority priorityData);
void get(QueueWithPriority<std::string>& queue, std::ostream& out);
void accelerate(QueueWithPriority<std::string>& queue, std::ostream&);
void printError(QueueWithPriority<std::string>&, std::ostream& out);

#endif 
