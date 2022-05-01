#include "shape.hpp"
#include <iostream>
#include "base-types.hpp"

void nazarenko::Shape::print() const
{
  std::cout << "  Area=" << getArea() << '\n'
            << "  FrameRect:  "
            << " height=" << getFrameRect().height
            << "  width=" << getFrameRect().width
            << "  pos=(" << getFrameRect().pos.x
            << " ; " << getFrameRect().pos.y << ")" << '\n';
}
