#ifndef SORTING_HPP
#define SORTING_HPP

#include <iostream>
#include <iterator>
#include "access.hpp"
#include "general.hpp"

template<template <typename> typename AccessType, typename Collection>
void sort(Collection& collect, std::function<bool(const typename Collection::value_type, const typename Collection::value_type)> comparator)
{
  using AccessT = AccessType<Collection>;
  const auto begin = AccessT::begin(collect);
  const auto end = AccessT::end(collect);

  for (auto i = begin; i != end; i++)
  {
    for (auto j = i; j != end; j++)
    {
      if (comparator(AccessT::getElem(collect, i), AccessT::getElem(collect, j)))
      {
        std::swap(AccessT::getElem(collect, i), AccessT::getElem(collect, j));
      }
    }
  }
}

#endif 
