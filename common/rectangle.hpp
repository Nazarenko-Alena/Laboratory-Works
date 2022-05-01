#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace nazarenko
{
  class Rectangle :public Shape
  {
  public:
    Rectangle(double height, double width, const point_t& pos);
    double getArea() const override;
    void move(double dx, double dy) override;
    void move(const point_t& point) override;
    rectangle_t getFrameRect() const override;
    void print() const override;
    point_t getCenter() const override;
    double getHeight() const;
    double getWidth() const;
    void scale(const double coefficient) override;
    void rotate(double angle) override;
  private:
    point_t corner_[4];
  };
}
#endif

