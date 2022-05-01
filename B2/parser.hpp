#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <functional>
#include "queueWithPriority.hpp"

using CommandFunction = std::function<void(QueueWithPriority<std::string>&, std::ostream&)>;

CommandFunction parse(std::stringstream& stream);
CommandFunction parseAdd(std::stringstream& stream);
CommandFunction parseGet(std::stringstream& stream);
CommandFunction parseAccelerate(std::stringstream& stream);

#endif
