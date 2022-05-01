#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <stdexcept>

template<typename Collection>
class OperatorAccess
{
public:
  using ValueType = typename Collection::value_type;
  using IteratorType = size_t;
  static ValueType& getElem(Collection& collect, const IteratorType index)
  {
    if (index >= collect.size())
    {
      throw std::out_of_range("Incorrect index");
    }
    return collect[index];
  }

  static IteratorType begin(const Collection&)
  {
    return 0;
  }

  static IteratorType end(const Collection& collect)
  {
    return collect.size();
  }
};

template<typename Collection>
class AtAccess
{
public:
  using ValueType = typename Collection::value_type;
  using IteratorType = size_t;
  static ValueType& getElem(Collection& collect, const IteratorType index)
  {
    return collect.at(index);
  }

  static IteratorType begin(const Collection&)
  {
    return 0;
  }

  static IteratorType end(const Collection& collect)
  {
    return collect.size();
  }
};

template<typename Collection>
class IteratorAccess
{
public:
  using ValueType = typename Collection::value_type;
  using IteratorType = typename Collection::iterator;
  static ValueType& getElem(Collection&, IteratorType& iterator)
  {
    return *iterator;
  }

  static IteratorType begin(Collection& collect)
  {
    return collect.begin();
  }

  static IteratorType end(Collection& collect)
  {
    return collect.end();
  }
};

#endif
