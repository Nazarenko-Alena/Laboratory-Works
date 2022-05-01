#include <iostream>
#include <stdexcept>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"
#include "dividing-by-layers.hpp"

int main()
{
  nazarenko::CompositeShape composite;
  try
  {
    std::shared_ptr<nazarenko::Shape> rectangle = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(2.3, 5.5, { 0,2.6 }));
    composite.add(rectangle);

    std::shared_ptr<nazarenko::Shape> circle = std::make_shared<nazarenko::Circle>(nazarenko::Circle(5.3, { 6.7,0.8 }));
    composite.add(circle);
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "The error is that " << err.what() << '\n';
    return 1;
  }
  catch (const std::logic_error& err)
  {
    std::cerr << "The error is that " << err.what() << '\n';
    return 1;
  }

  std::cout << "  For Composite Shape " << '\n';
  composite.print();

  composite.rotate(0.0);
  std::cout << '\n' << "  Composite after the turn: " << '\n';
  composite.print();

  nazarenko::MatrixShape matrix;

  matrix = composite.divideByLayers();
  std::cout << '\n' << "  Composite after the dividing: " << '\n';
  matrix.print();

  nazarenko::MatrixShape matrixOne;
  nazarenko::MatrixShape matrixTwo;
  nazarenko::Shape::ShapeArray arr = std::make_unique<nazarenko::Shape::ShapePtr[]>(5);

  try
  {
    std::shared_ptr<nazarenko::Shape> rectangleTwo = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(1.0, 1.0, { -23.8,-23.0 }));
    std::shared_ptr<nazarenko::Shape> rectangle = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(2.3, 5.5, { 0,2.6 }));

    std::shared_ptr<nazarenko::Shape> circle = std::make_shared<nazarenko::Circle>(nazarenko::Circle(5.3, { 6.7,0.8 }));
    std::shared_ptr<nazarenko::Shape> rect = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(2.0, 4.0, { 0,2.0 }));
    std::shared_ptr<nazarenko::Shape> circ = std::make_shared<nazarenko::Circle>(nazarenko::Circle(6.0, { 1.0,1.0 }));

    arr[0] = rectangleTwo;
    arr[1] = rectangle;
    arr[2] = circle;
    arr[3] = rect;
    arr[4] = circ;

    matrixTwo.addLine().add(circ);
    matrixTwo[0].add(rect);
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "The error is that " << err.what() << '\n';
    return 1;
  }

  matrixOne = nazarenko::divideByLayers(arr, 5);

  std::cout << '\n' << "  Matrix after fragmentation: " << '\n';
  matrixOne.print();

  std::cout << '\n' << "  Matrix after add : " << '\n';
  matrixTwo.print();

  return 0;
}

