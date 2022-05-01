#include "matrix-shape.hpp"
#include <stdexcept>
#include <iostream>
#include <memory>
#include "base-types.hpp"

nazarenko::MatrixShape::MatrixShape() :
  numberOfLines_(0),
  numberOfColumns_(0),
  shapeArray_(nullptr)
{}

nazarenko::MatrixShape::MatrixShape(const MatrixShape& matrix) :
  numberOfLines_(matrix.numberOfLines_),
  numberOfColumns_(matrix.numberOfColumns_),
  shapeArray_(nullptr)
{
  if (numberOfLines_ != 0)
  {
    shapeArray_ = std::make_unique<Shape::ShapePtr[]>(numberOfLines_ * numberOfColumns_);
    for (size_t i = 0; i < numberOfLines_ * numberOfColumns_; i++)
    {
      shapeArray_[i] = matrix.shapeArray_[i];
    }
  }
}

nazarenko::MatrixShape::MatrixShape(MatrixShape&& matrix) noexcept :
  numberOfLines_(matrix.numberOfLines_),
  numberOfColumns_(matrix.numberOfColumns_),
  shapeArray_(std::move(matrix.shapeArray_))
{
  matrix.numberOfLines_ = 0;
  matrix.numberOfColumns_ = 0;
}

nazarenko::MatrixShape& nazarenko::MatrixShape::operator=(MatrixShape&& matrix) noexcept
{
  numberOfLines_ = matrix.numberOfLines_;
  numberOfColumns_ = matrix.numberOfColumns_;
  shapeArray_ = std::move(matrix.shapeArray_);
  matrix.numberOfLines_ = 0;
  matrix.numberOfColumns_ = 0;
  return *this;
}

nazarenko::MatrixShape& nazarenko::MatrixShape::operator=(const MatrixShape& matrix)
{
  if (this != &matrix)
  {
    if (matrix.numberOfLines_ == 0)
    {
      numberOfColumns_ = 0;
      numberOfLines_ = 0;
      shapeArray_ = nullptr;
    }
    else
    {
      shapeArray_ = std::make_unique<Shape::ShapePtr[]>(matrix.numberOfColumns_ * matrix.numberOfLines_);
      numberOfLines_ = matrix.numberOfLines_;
      numberOfColumns_ = matrix.numberOfColumns_;
      for (size_t i = 0; i < numberOfLines_ * numberOfColumns_; i++)
      {
        shapeArray_[i] = matrix.shapeArray_[i];
      }
    }
  }
  return *this;
}

nazarenko::MatrixShape::MatrixLine nazarenko::MatrixShape::operator[](size_t index)
{
  if (index >= numberOfLines_ * numberOfColumns_)
  {
    throw std::invalid_argument("Incorrect index");
  }
  return MatrixLine(this, index + 1);
}

nazarenko::MatrixShape::MatrixLineConst nazarenko::MatrixShape::operator[](size_t index) const
{
  if (index >= numberOfLines_ * numberOfColumns_)
  {
    throw std::invalid_argument("Incorrect index");
  }
  return MatrixLineConst(this, index + 1);
}

size_t nazarenko::MatrixShape::getNumberOfLines() const
{
  return numberOfLines_;
}

void nazarenko::MatrixShape::print() const
{
  for (size_t i = 0; i < numberOfColumns_ * numberOfLines_; i++)
  {
    if (shapeArray_[i])
    {
      std::cout << " Shapes " << i << " :" << '\n';
      shapeArray_[i]->print();
    }
    else
    {
      std::cout << " There is no figure here " << i << '\n';
    }
  }
}

nazarenko::MatrixShape::MatrixLine nazarenko::MatrixShape::addLine()
{
  Shape::ShapeArray tmp(new Shape::ShapePtr[numberOfColumns_ * (numberOfLines_ + 1)]);
  ++numberOfLines_;
  for (size_t index = 0; index < numberOfColumns_ * (numberOfLines_ - 1); index++)
  {
    tmp[index] = shapeArray_[index];
  }
  shapeArray_ = std::move(tmp);
  return MatrixLine(this, numberOfLines_);
}

void nazarenko::MatrixShape::addColumn()
{
  size_t i = 0;
  ++numberOfColumns_;
  Shape::ShapeArray tmp(new Shape::ShapePtr[numberOfColumns_ * numberOfLines_]);
  for (size_t index = 0; index < numberOfLines_; index++)
  {
    for (size_t j = 0; j < numberOfColumns_; j++)
    {
      if (j != (numberOfColumns_ - 1))
      {
        tmp[index * numberOfColumns_ + j] = shapeArray_[i];
        i++;
      }
    }
  }
  shapeArray_ = std::move(tmp);
}

nazarenko::MatrixShape::MatrixLineConst::MatrixLineConst(const MatrixShape* matrix, const size_t index) :
  index_(index),
  matrixConst_(matrix)
{
}

nazarenko::Shape::ShapePtr nazarenko::MatrixShape::MatrixLineConst::operator[](const size_t index) const
{
  if (index >= getSize())
  {
    throw std::invalid_argument("Incorrect index");
  }
  return matrixConst_->shapeArray_[(index_ - 1) * matrixConst_->numberOfColumns_ + index];
}

size_t nazarenko::MatrixShape::MatrixLineConst::getSize() const
{
  size_t count = 0;
  for (size_t i = 0; i < matrixConst_->numberOfColumns_; i++)
  {
    if (matrixConst_->shapeArray_[(index_ - 1) * matrixConst_->numberOfColumns_ + i])
    {
      count++;
    }
  }
  return count;
}

nazarenko::MatrixShape::MatrixLine::MatrixLine(MatrixShape* matrix, const size_t index) :
  MatrixLineConst(matrix, index),
  matrix_(matrix)
{
}

void nazarenko::MatrixShape::MatrixLine::add(const Shape::ShapePtr& shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Incorrect shape");
  }

  matrix_->addToDesiredLine(shape, index_);
}

void nazarenko::MatrixShape::addToDesiredLine(const Shape::ShapePtr& shape, size_t index)
{
  if (!shape)
  {
    throw std::invalid_argument("Incorrect shape");
  }
  for (size_t i = (index - 1) * numberOfColumns_; i < index * numberOfColumns_; i++)
  {
    if (shapeArray_[i] == nullptr)
    {
      shapeArray_[i] = shape;
      return;
    }
  }
  addColumn();
  shapeArray_[index * numberOfColumns_ - 1] = shape;
}
