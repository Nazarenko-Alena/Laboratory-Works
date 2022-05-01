#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(test_for_rectangle)

const double width = 5.5;
const double height = 2.3;
const double coefficient = 10;
const double epsilon = 0.000001;
const nazarenko::point_t center{ 2.308,0.5 };
const nazarenko::point_t point{ 3.7,7.65 };
const double dx = 5.5;
const double dy = -2.6;

BOOST_AUTO_TEST_CASE(rectangle_after_moving_to_a_point_validation_test)
{
  nazarenko::Rectangle rectangle(height, width, center);
  rectangle.move(point);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, point.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, point.y, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), height * width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, point.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, point.y, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_after_moving_to_dx_dy_validation_test)
{
  nazarenko::Rectangle rectangle(height, width, center);
  rectangle.move(dx, dy);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x + dx, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y + dy, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), height * width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, center.x + dx, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, center.y + dy, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_after_scaling_validation_test)
{
  nazarenko::Rectangle rectangle(height, width, center);
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height * coefficient, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width * coefficient, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), height * width * coefficient * coefficient, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height * coefficient, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width * coefficient, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_validation_test)
{
  nazarenko::Rectangle rectangle(height, width, center);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), height * width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(incorrect_rectangle_height_test)
{
  BOOST_CHECK_THROW(nazarenko::Rectangle rectangle(0.0, width, center), std::invalid_argument);
  BOOST_CHECK_THROW(nazarenko::Rectangle rectangle(-2.6, width, center), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(incorrect_rectangle_width_test)
{
  BOOST_CHECK_THROW(nazarenko::Rectangle rectangle(height, 0.0, center), std::invalid_argument);
  BOOST_CHECK_THROW(nazarenko::Rectangle rectangle(height, -2.5, center), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(incorrect_scaling_factor_test)
{
  nazarenko::Rectangle rectangle(height, width, center);
  BOOST_CHECK_THROW(rectangle.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(-2.7), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_after_rotate_validation_test)
{
  nazarenko::Rectangle rectangle(height, width, center);

  const nazarenko::point_t center = rectangle.getCenter();

  nazarenko::point_t corner[4];

  corner[0] = { center.x - width / 2, center.y + height / 2 };
  corner[1] = { center.x + width / 2, center.y + height / 2 };
  corner[2] = { center.x + width / 2, center.y - height / 2 };
  corner[3] = { center.x - width / 2, center.y - height / 2 };

  const double sin = std::sin(M_PI * 90 / 180);
  const double cos = std::cos(M_PI * 90 / 180);

  rectangle.rotate(90.0);
   
  corner[0] = { center.x + cos * (corner[0].x - center.x) - sin * (corner[0].y - center.y),
                center.y + sin * (corner[0].x - center.x) + cos * (corner[0].y - center.y) };
  corner[1] = { center.x + cos * (corner[1].x - center.x) - sin * (corner[1].y - center.y),
                center.y + sin * (corner[1].x - center.x) + cos * (corner[1].y - center.y) };
  corner[2] = { center.x + cos * (corner[2].x - center.x) - sin * (corner[2].y - center.y),
                center.y + sin * (corner[2].x - center.x) + cos * (corner[2].y - center.y) };
  corner[3] = { center.x + cos * (corner[3].x - center.x) - sin * (corner[3].y - center.y),
                center.y + sin * (corner[3].x - center.x) + cos * (corner[3].y - center.y) };

  double minX = corner[0].x;
  double maxX = corner[0].x;
  double minY = corner[0].y;
  double maxY = corner[0].y;

  for (int i = 0; i < 4; i++)
  {
    minX = std::min(minX, corner[i].x);
    maxX = std::max(maxX, corner[i].x);
    minY = std::min(minY, corner[i].y);
    maxY = std::max(maxY, corner[i].y);
  }

  BOOST_CHECK_CLOSE(rectangle.getHeight(), maxY - minY, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), maxX - minX, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), (maxY - minY) * (maxX - minX), epsilon);

  rectangle.rotate(-90.0);

  BOOST_CHECK_CLOSE(rectangle.getHeight(), height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), height * width, epsilon);
}

BOOST_AUTO_TEST_SUITE_END();
