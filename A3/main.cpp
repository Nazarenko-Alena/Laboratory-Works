#include <iostream>
#include <stdexcept>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"

int main()
{
  nazarenko::CompositeShape composite;
  try
  {
    nazarenko::Shape::ShapePtr rectangle = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(2.3, 5.5, { 2.308,0.5 }));
    composite.add(rectangle);

    nazarenko::Shape::ShapePtr circle = std::make_shared<nazarenko::Circle>(nazarenko::Circle(5.3, { 8.3,2.5 }));
    composite.add(circle);
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "The error is that " << err.what() << '\n';
    return 1;
  }

  std::cout << '\n' << " For Composite Shape " << '\n';
  composite.print();

  composite.move(nazarenko::point_t{ 3.7,7.65 });
  std::cout << '\n' << "  After moving to point: " << '\n';
  composite.print();

  composite.move(-1.003, 10.5);
  std::cout << '\n' << "  After moving by dx and dy: " << '\n';
  composite.print();

  try
  {
    composite.scale(5.3);
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "The error is that " << err.what() << '\n';
    return 1;
  }
  
  std::cout << '\n' << "  Composite after scaling: " << '\n';
  composite.print();

  try
  {
    composite.remove(0);
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "The error is that " << err.what() << '\n';
    return 1;
  }
  std::cout << '\n' << "  Composite after removing: " << '\n';
  composite.print();

  return 0;
}
