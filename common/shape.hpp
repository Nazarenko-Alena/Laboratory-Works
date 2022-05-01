#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>

namespace nazarenko
{
  struct point_t;
  struct rectangle_t;
  class Shape
  {
  public:
    using ShapePtr = std::shared_ptr<Shape>;
    using ShapeArray = std::unique_ptr<ShapePtr[]>;
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t& point) = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void print() const = 0;
    virtual point_t getCenter() const = 0;
    virtual void scale(const double coefficient) = 0;
    virtual void rotate(double angle) = 0;
  };
}
#endif
