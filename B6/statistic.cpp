#include "statistic.hpp"
#include <algorithm>
#include <iostream>

Statistic::Statistic() :
  max_(0),
  min_(0),
  positive_(0),
  negative_(0),
  oddSum_(0),
  evenSum_(0),
  count_(0),
  first_(0),
  empty_(true),
  firstLastEqual_(false)
{}

void Statistic::operator()(const long int value)
{
  if (!empty_)
  {
    max_ = std::max(value, max_);
    min_ = std::min(value, min_);
  }
  else
  {
    empty_ = false;
    max_ = value;
    min_ = value;
    first_ = value;
  }

  count_++;

  if (value > 0)
  {
    positive_++;
  }
  else if (value < 0)
  {
    negative_++;
  }

  if (value % 2 != 0)
  {
    oddSum_ += value;
  }
  else
  {
    evenSum_ += value;
  }

  firstLastEqual_ = (first_ == value);
}

std::ostream& operator<<(std::ostream& out, const Statistic& stat)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    if (!stat.empty_)
    {
      double mean = static_cast<double>((stat.evenSum_ + stat.oddSum_) / stat.count_);
      out << "Max: " << stat.max_ << '\n' << "Min: " << stat.min_ << '\n' << "Mean: " << mean << '\n'
        << "Positive: " << stat.positive_ << '\n' << "Negative: " << stat.negative_ << '\n'
        << "Odd Sum: " << stat.oddSum_ << '\n' << "Even Sum: " << stat.evenSum_ << '\n'
        << "First/Last Equal: ";
      if (stat.firstLastEqual_)
      {
        out << "yes" << '\n';
      }
      else
      {
        out << "no" << '\n';
      }
    }
    else
    {
      out << "No Data" << '\n';
    }
  }
  return out;
}


