#include "composite-shape.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <memory>
#include "base-types.hpp"
#include "dividing-by-layers.hpp"
#include "matrix-shape.hpp"

nazarenko::CompositeShape::CompositeShape() :
  size_(0),
  shapeArr_(nullptr)
{}

nazarenko::CompositeShape::CompositeShape(const CompositeShape& composite) :
  size_(composite.size_),
  shapeArr_(nullptr)
{
  if (composite.size_ != 0)
  {
    shapeArr_ = std::make_unique<ShapePtr[]>(size_);
    for (size_t i = 0; i < size_; i++)
    {
      shapeArr_[i] = composite.shapeArr_[i];
    }
  }
}

nazarenko::CompositeShape::CompositeShape(CompositeShape&& composite) noexcept :
  size_(composite.size_),
  shapeArr_(std::move(composite.shapeArr_))
{
  composite.size_ = 0;
}

nazarenko::CompositeShape& nazarenko::CompositeShape::operator=(CompositeShape&& composite) noexcept
{
  size_ = composite.size_;
  shapeArr_ = std::move(composite.shapeArr_);
  composite.size_ = 0;
  return *this;
}

nazarenko::CompositeShape& nazarenko::CompositeShape::operator=(const CompositeShape& composite)
{
  if (this != &composite)
  {
    if (composite.size_ != 0)
    {
      shapeArr_ = std::make_unique<ShapePtr[]>(composite.size_);
      size_ = composite.size_;
      for (size_t i = 0; i < size_; i++)
      {
        shapeArr_[i] = composite.shapeArr_[i];
      }
    }
    else
    {
      shapeArr_ = nullptr;
      size_ = 0;
    }
  }
  return *this;
}

nazarenko::Shape::ShapePtr nazarenko::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::invalid_argument("Incorrect index");
  }
  return shapeArr_[index];
}

double nazarenko::CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    area += shapeArr_[i]->getArea();
  }
  return area;
}

void nazarenko::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    shapeArr_[i]->move(dx, dy);
  }
}

void nazarenko::CompositeShape::move(const point_t& point)
{
  move(point.x - getFrameRect().pos.x, point.y - getFrameRect().pos.y);
}

nazarenko::rectangle_t nazarenko::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return rectangle_t{ 0.0, 0.0,{0,0} };
  }
  double minX = shapeArr_[0]->getFrameRect().pos.x - shapeArr_[0]->getFrameRect().width / 2;
  double maxX = shapeArr_[0]->getFrameRect().pos.x + shapeArr_[0]->getFrameRect().width / 2;

  double minY = shapeArr_[0]->getFrameRect().pos.y - shapeArr_[0]->getFrameRect().height / 2;
  double maxY = shapeArr_[0]->getFrameRect().pos.y + shapeArr_[0]->getFrameRect().height / 2;

  for (size_t i = 0; i < size_; i++)
  {
    const rectangle_t frameRect = shapeArr_[i]->getFrameRect();
    minX = std::min(minX, frameRect.pos.x - frameRect.width / 2);
    maxX = std::max(maxX, frameRect.pos.x + frameRect.width / 2);
    minY = std::min(minY, frameRect.pos.y - frameRect.height / 2);
    maxY = std::max(maxY, frameRect.pos.y + frameRect.height / 2);
  }
  const point_t center{ (maxX + minX) / 2,(maxY + minY) / 2 };
  return rectangle_t{ maxX - minX, maxY - minY,center };
}

void nazarenko::CompositeShape::print() const
{
  for (size_t i = 0; i < size_; i++)
  {
    std::cout << " Shape " << i << '\n';
    shapeArr_[i]->print();
  }
  std::cout << " CompositeShape" << '\n';
  Shape::print();
}

void nazarenko::CompositeShape::scale(const double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Incorrect coefficient");
  }
  const point_t centerComposite = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    shapeArr_[i]->scale(coefficient);
    const point_t centerShape = shapeArr_[i]->getCenter();
    shapeArr_[i]->move((centerShape.x - centerComposite.x) * (coefficient - 1),
                       (centerShape.y - centerComposite.y) * (coefficient - 1));
  }
}

nazarenko::point_t nazarenko::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

void nazarenko::CompositeShape::add(const ShapePtr& shape)
{
  if ((!shape))
  {
    throw std::invalid_argument("Incorrect shape");
  }
  if (this == shape.get())
  {
    throw std::logic_error("You cannot add yourself");
  }
  ShapeArray newArr(new ShapePtr[size_ + 1]);
  for (size_t i = 0; i < size_; i++)
  {
    newArr[i] = shapeArr_[i];
  }
  newArr[size_++] = shape;
  shapeArr_ = std::move(newArr);
}

void nazarenko::CompositeShape::remove(size_t index)
{
  if (index >= size_)
  {
    throw std::invalid_argument("Removal is not possible");
  }
  for (size_t i = index; i < size_ - 1; i++)
  {
    shapeArr_[i] = shapeArr_[i + 1];
  }
  shapeArr_[--size_].reset();
}

size_t nazarenko::CompositeShape::getSize() const
{
  return size_;
}

void nazarenko::CompositeShape::rotate(double angle)
{
  const nazarenko::point_t compositeFrameCenter = getFrameRect().pos;
  for (size_t i=0; i < size_; i++)
  {
    nazarenko::point_t shapeCenter = shapeArr_[i]->getCenter();
    nazarenko::details::moveToRotate(angle, compositeFrameCenter, shapeCenter);
    shapeArr_[i]->rotate(angle);
  }
}

nazarenko::MatrixShape nazarenko::CompositeShape::divideByLayers()
{
  return nazarenko::divideByLayers(shapeArr_, size_);
}
