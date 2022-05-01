#ifndef MATRIXSHAPE_HPP
#define MATRIXSHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace nazarenko
{
  class MatrixShape
  {
  public:

    class MatrixLineConst
    {
    public:
      nazarenko::Shape::ShapePtr operator[](const size_t index) const;
      size_t getSize() const;
    protected:
      size_t index_;
    private:
      const MatrixShape* matrixConst_;
      MatrixLineConst(const MatrixShape* matrix, const size_t index);
      friend MatrixShape;
    };

    class MatrixLine : public MatrixLineConst
    {
    public:
      void add(const Shape::ShapePtr& shape);
    private:
      MatrixLine(MatrixShape* matrix, const size_t index);
      MatrixShape* matrix_;
      friend MatrixShape;
    };

    MatrixShape();
    MatrixShape(const MatrixShape& matrix);
    MatrixShape(MatrixShape&& matrix) noexcept;
    ~MatrixShape() = default;

    MatrixShape& operator=(const MatrixShape& matrix);
    MatrixShape& operator=(MatrixShape&& matrix) noexcept;
    MatrixLine operator[](size_t index);
    MatrixLineConst operator[](size_t index) const;

    void print() const;

    nazarenko::MatrixShape::MatrixLine addLine();
    size_t getNumberOfLines() const;
  private:
    void addToDesiredLine(const Shape::ShapePtr& shape, size_t index);
    size_t numberOfLines_;
    size_t numberOfColumns_;
    Shape::ShapeArray shapeArray_;
    void addColumn();
  };
}
#endif
