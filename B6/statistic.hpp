#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <iostream>

class Statistic {
public:
  Statistic();
  void operator() (const long int value);
private:
  long int max_, min_, positive_, negative_, oddSum_, evenSum_, count_, first_;
  bool empty_, firstLastEqual_;
  friend std::ostream& operator<<(std::ostream& out, const Statistic& stat);
};

#endif
