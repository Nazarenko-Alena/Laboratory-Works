#include "rectangle.hpp"
#include <iostream>
#include <algorithm>
#include "base-types.hpp"

nazarenko::Rectangle::Rectangle(double height, double width, const point_t& pos)
{
  if (height <= 0)
  {
    throw std::invalid_argument("Incorrect height");
  }
  if (width <= 0)
  {
    throw std::invalid_argument("Incorrect width");
  }
  corner_[0] = { pos.x - width / 2, pos.y + height / 2 };
  corner_[1] = { pos.x + width / 2, pos.y + height / 2 };
  corner_[2] = { pos.x + width / 2, pos.y - height / 2 };
  corner_[3] = { pos.x - width / 2, pos.y - height / 2 };
}

double nazarenko::Rectangle::getArea() const
{
  double minX = corner_[0].x;
  double maxX = corner_[0].x;
  double minY = corner_[0].y;
  double maxY = corner_[0].y;

  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    minX = std::min(minX, corner_[i].x);
    maxX = std::max(maxX, corner_[i].x);
    minY = std::min(minY, corner_[i].y);
    maxY = std::max(maxY, corner_[i].y);
  }

  return (maxY-minY) * (maxX-minX);
}

void nazarenko::Rectangle::move(double dx, double dy)
{
  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    corner_[i].x += dx;
    corner_[i].y += dy;
  }
}

void nazarenko::Rectangle::move(const point_t& point)
{
  double minX = corner_[0].x;
  double maxX = corner_[0].x;
  double minY = corner_[0].y;
  double maxY = corner_[0].y;

  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    minX = std::min(minX, corner_[i].x);
    maxX = std::max(maxX, corner_[i].x);
    minY = std::min(minY, corner_[i].y);
    maxY = std::max(maxY, corner_[i].y);
  }

  point_t movePoint{ point.x - ((maxX + minX) / 2), point.y - ((maxY + minY) / 2) };
  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    corner_[i].x += movePoint.x;
    corner_[i].y += movePoint.y;
  }
}

nazarenko::rectangle_t nazarenko::Rectangle::getFrameRect() const
{
  double minX = corner_[0].x;
  double maxX = corner_[0].x;
  double minY = corner_[0].y;
  double maxY = corner_[0].y;

  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    minX = std::min(minX, corner_[i].x);
    maxX = std::max(maxX, corner_[i].x);
    minY = std::min(minY, corner_[i].y);
    maxY = std::max(maxY, corner_[i].y);
  }
  const point_t center{ (maxX + minX) / 2,(maxY + minY) / 2 };
  return rectangle_t{ maxX - minX, maxY - minY, center };
}

void nazarenko::Rectangle::print() const
{
  std::cout << "  Height = " << getHeight()
            << "  " << "  Width = " << getWidth() << '\n';
  Shape::print();
}

nazarenko::point_t nazarenko::Rectangle::getCenter() const
{
  double minX = corner_[0].x;
  double maxX = corner_[0].x;
  double minY = corner_[0].y;
  double maxY = corner_[0].y;

  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    minX = std::min(minX, corner_[i].x);
    maxX = std::max(maxX, corner_[i].x);
    minY = std::min(minY, corner_[i].y);
    maxY = std::max(maxY, corner_[i].y);
  }
  return point_t{ (maxX + minX) / 2,(maxY + minY) / 2 };
}

double nazarenko::Rectangle::getHeight() const
{
  double minY = corner_[0].y;
  double maxY = corner_[0].y;

  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    minY = std::min(minY, corner_[i].y);
    maxY = std::max(maxY, corner_[i].y);
  }

  return maxY - minY;
}

double nazarenko::Rectangle::getWidth() const
{
  double minX = corner_[0].x;
  double maxX = corner_[0].x;

  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    minX = std::min(minX, corner_[i].x);
    maxX = std::max(maxX, corner_[i].x);
  }

  return maxX - minX;
}

void nazarenko::Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect coefficient");
  }
  const point_t center = getCenter();
  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    corner_[i].x = center.x + coefficient * (corner_[i].x - center.x);
    corner_[i].y = center.y + coefficient * (corner_[i].y - center.y);
  }
}

void nazarenko::Rectangle::rotate(double angle)
{
  const point_t center = getCenter();

  for (size_t i = 0; i < (sizeof(corner_) / sizeof(point_t)); i++)
  {
    nazarenko::details::moveToRotate(angle, center, corner_[i]);
  }
}
