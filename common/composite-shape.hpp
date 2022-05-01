#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace nazarenko
{
  class MatrixShape;

  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& composite);
    CompositeShape(CompositeShape&& composite) noexcept;
    CompositeShape& operator =(const CompositeShape& composite);
    CompositeShape& operator =(CompositeShape&& composite) noexcept;
    ShapePtr operator[](size_t index) const;
    double getArea() const override;
    void move(double dx, double dy) override;
    void move(const point_t& point) override;
    rectangle_t getFrameRect() const override;
    void print() const override;
    void scale(const double coefficient) override;
    point_t getCenter() const override;
    void add(const ShapePtr& shape);
    void remove(size_t index);
    size_t getSize() const;
    void rotate(double angle) override;
    MatrixShape divideByLayers();
  private:
    size_t size_;
    ShapeArray shapeArr_;
  };
}

#endif
