#include <iostream>
#include <exception>

#include"rectangle.hpp"
#include"circle.hpp"
#include"shape.hpp"
#include"base-types.hpp"

int main()
{
  double dx = -1.003;
  double dy = 10.5;
  nazarenko::Shape* shape;
  const nazarenko::point_t center{ 2.308,0.5 };
  try
  {
    nazarenko::Rectangle rect(2.3, 5.5, center);
    shape = &rect;

    std::cout << "For Rectangle" << '\n';
    shape->print();

    shape->move(nazarenko::point_t{ 3.7,7.65 });
    std::cout << "  Coordinates of the center after moving to point: ( " << shape->getCenter().x
              << " ; " << shape->getCenter().y << " ) " << '\n';

    shape->move(dx, dy);
    std::cout << "  Coordinates of the center after moving: ( " << shape->getCenter().x
              << " ; " << shape->getCenter().y << " ) " << '\n' << '\n';

    shape->scale(10.2);
    std::cout << "  Rectangle after scaling: " << '\n';
    shape->print();
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "The error is that " << err.what() << '\n';
    return 1;
  }

  try
  {
    nazarenko::Circle circle(5.3, center);
    shape = &circle;

    dx = 20.01;
    dy = 8.6;

    std::cout << '\n' << "For Circle" << '\n';
    shape->print();

    shape->move(nazarenko::point_t{ 4.506,26.03 });
    std::cout << "  Coordinates of the center after moving to point: ( " << shape->getCenter().x
              << " ; " << shape->getCenter().y << " ) " << '\n';

    shape->move(dx, dy);
    std::cout << "  Coordinates of the center after moving: ( " << shape->getCenter().x
              << " ; " << shape->getCenter().y << " ) " << '\n';

    shape->scale(5.3);
    std::cout << "  Circle after scaling: " << '\n';
    shape->print();
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << "The error is that " << err.what() << '\n';
    return 1;
  }
  return 0;
}
