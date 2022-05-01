#define _USE_MATH_DEFINES
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(test_for_circle)

const double radius = 2.3;
const double coefficient = 10.2;
const double epsilon = 0.000001;
const nazarenko::point_t center{ 2.308,0.5 };
const nazarenko::point_t point{ 3.7,7.65 };
const double dx = 5.3;
const double dy = -2.8;

BOOST_AUTO_TEST_CASE(circle_after_moving_to_a_point_validation_test)
{
  nazarenko::Circle circle(radius, center);
  circle.move(point);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, point.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, point.y, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * radius * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, point.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, point.y, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_after_moving_to_dx_dy_validation_test)
{
  nazarenko::Circle circle(radius, center);
  circle.move(dx, dy);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, center.x + dx, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, center.y + dy, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * radius * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, center.x + dx, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, center.y + dy, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_after_scaling_validation_test)
{
  nazarenko::Circle circle(radius, center);
  circle.scale(coefficient);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius * coefficient, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * radius * radius * coefficient * coefficient, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radius * coefficient, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radius * coefficient, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_validation_test)
{
  nazarenko::Circle circle(radius, center);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * radius * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(incorrect_circle_radius_test)
{
  BOOST_CHECK_THROW(nazarenko::Circle circle(0.0, center), std::invalid_argument);
  BOOST_CHECK_THROW(nazarenko::Circle circle(-2.3, center), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(incorrect_scaling_factor_test)
{
  nazarenko::Circle circle(5.3, center);
  BOOST_CHECK_THROW(circle.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(-2.7), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(circle_after_rotate_validation_test)
{
  nazarenko::Circle circle(radius, center);
  const double radiusCirc = circle.getRadius();
  const nazarenko::point_t centerCirc = circle.getFrameRect().pos;

  circle.rotate(60.0);

  BOOST_CHECK_CLOSE(circle.getRadius(), radiusCirc, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, centerCirc.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, centerCirc.y, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * radiusCirc * radiusCirc, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radiusCirc, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radiusCirc, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, centerCirc.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, centerCirc.y, epsilon);
}

BOOST_AUTO_TEST_SUITE_END();



