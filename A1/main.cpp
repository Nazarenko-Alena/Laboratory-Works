#include<iostream>

#include"rectangle.hpp"
#include"circle.hpp"
#include"shape.hpp"


int main()
{
  Rectangle rect(2.3, 5.5, point_t{ 2.308,0.5 });
  Shape* shape = &rect;

  double dx = -1.003;
  double dy = 10.5;

  std::cout << "For Rectangle" << '\n' << '\n';
  shape->print();

  shape->move(point_t{ 3.7,7.65 });
  std::cout << "  Coordinates of the center after moving to point: ( " << shape->getCenter().x
            << " ; " << shape->getCenter().y << " ) " << '\n';

  shape->move(dx, dy);
  std::cout << "  Coordinates of the center after moving : ( " << shape->getCenter().x
            << " ; " << shape->getCenter().y << " ) " << '\n' << '\n';

  Circle circle(5.3, point_t{ 6.002,-8.5 });
  shape = &circle;

  dx = 20.01;
  dy = 8.6;

  std::cout << "For Circle" << '\n' << '\n';
  shape->print();

  shape->move(point_t{ 4.506,26.03 });
  std::cout << "  Coordinates of the center after moving to point: ( " << shape->getCenter().x
            << " ; " << shape->getCenter().y << " ) " << '\n';

  shape->move(dx, dy);
  std::cout << "  Coordinates of the center after moving: ( " << shape->getCenter().x
            << " ; " << shape->getCenter().y << " ) " << '\n';

  return 0;
}
