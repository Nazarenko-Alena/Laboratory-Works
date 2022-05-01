#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace nazarenko
{
  class Circle :public Shape
  {
  public:
    Circle(double rad, const point_t& center);
    double getArea() const override;
    void move(double dx, double dy) override;
    void move(const point_t& point) override;
    rectangle_t getFrameRect() const override;
    void print() const override;
    point_t getCenter() const override;
    double getRadius() const;
    void scale(const double coefficient) override;
    void rotate(double angle) override;
  private:
    double radius_;
    point_t center_;
  };
}
#endif

