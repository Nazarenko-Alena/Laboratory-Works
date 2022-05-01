#include <memory>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(test_for_composite)

const double width = 5.5;
const double height = 2.3;
const double radius = 2.7;
const double coefficient = 10;
const double epsilon = 0.000001;
const nazarenko::point_t centerR{ 2.308,0.5 };
const nazarenko::point_t centerC{ 8.3,2.5 };
const nazarenko::point_t point{ 3.7,7.65 };
const double dx = 5.5;
const double dy = -2.6;

BOOST_AUTO_TEST_CASE(composite_after_moving_to_a_point_validation_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  const double heightComposite = composite.getFrameRect().height;
  const double widthComposite = composite.getFrameRect().width;

  composite.move(point);

  BOOST_CHECK_EQUAL(composite.getSize(), 2);
  BOOST_CHECK_CLOSE(composite.getArea(), composite[0]->getArea() + composite[1]->getArea(), epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().height, heightComposite, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().width, widthComposite, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.x, point.x, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.y, point.y, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_after_moving_to_dx_dy_validation_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  const double heightComposite = composite.getFrameRect().height;
  const double widthComposite = composite.getFrameRect().width;
  const nazarenko::point_t centerComposite = composite.getFrameRect().pos;

  composite.move(dx, dy);

  BOOST_CHECK_EQUAL(composite.getSize(), 2);
  BOOST_CHECK_CLOSE(composite.getArea(), composite[0]->getArea() + composite[1]->getArea(), epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().height, heightComposite, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().width, widthComposite, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.x, centerComposite.x + dx, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.y, centerComposite.y + dy, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_after_scaling_validation_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  const double heightComposite = composite.getFrameRect().height;
  const double widthComposite = composite.getFrameRect().width;

  const nazarenko::point_t centerComposite = composite.getFrameRect().pos;
  const nazarenko::point_t centerRect = composite[0]->getFrameRect().pos;
  const nazarenko::point_t centerCircle = composite[1]->getFrameRect().pos;

  const nazarenko::point_t movePointCircle{ (coefficient - 1) * (centerCircle.x - centerComposite.x),
                                            (coefficient - 1) * (centerCircle.y - centerComposite.y) };

  const nazarenko::point_t movePointRect{ (coefficient - 1) * (centerRect.x - centerComposite.x),
                                          (coefficient - 1) * (centerRect.y - centerComposite.y) };

  composite.scale(coefficient);

  BOOST_CHECK_EQUAL(composite.getSize(), 2);
  BOOST_CHECK_CLOSE(composite.getArea(), composite[0]->getArea() + composite[1]->getArea(), epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().height, heightComposite * coefficient, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().width, widthComposite * coefficient, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.x, centerComposite.x, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.y, centerComposite.y, epsilon);

  BOOST_CHECK_CLOSE(composite[0]->getFrameRect().pos.x, movePointRect.x + centerRect.x, epsilon);
  BOOST_CHECK_CLOSE(composite[0]->getFrameRect().pos.y, movePointRect.y + centerRect.y, epsilon);

  BOOST_CHECK_CLOSE(composite[1]->getFrameRect().pos.x, movePointCircle.x + centerCircle.x, epsilon);
  BOOST_CHECK_CLOSE(composite[1]->getFrameRect().pos.y, movePointCircle.y + centerCircle.y, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_validation_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));
  
  const double minX = composite[0]->getFrameRect().pos.x - composite[0]->getFrameRect().width / 2;
  const double maxX = composite[1]->getFrameRect().pos.x + composite[1]->getFrameRect().width / 2;
  const double minY = composite[0]->getFrameRect().pos.y - composite[0]->getFrameRect().height / 2;
  const double maxY = composite[1]->getFrameRect().pos.y + composite[1]->getFrameRect().height / 2;

  BOOST_CHECK_EQUAL(composite.getSize(), 2);
  BOOST_CHECK_CLOSE(composite.getArea(), composite[0]->getArea() + composite[1]->getArea(), epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().height, maxY - minY, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().width, maxX - minX, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.x, (maxX + minX) / 2, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.y, (maxY + minY) / 2, epsilon);

  nazarenko::CompositeShape composite_two;

  composite_two.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite_two.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  composite.add(std::make_shared<nazarenko::CompositeShape>(composite_two));
  BOOST_CHECK_EQUAL(composite.getSize(), 3);
  BOOST_CHECK_CLOSE(composite.getArea(), composite[0]->getArea() + composite[1]->getArea() + composite[2]->getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(composite_add_yourself_test)
{
  std::shared_ptr<nazarenko::CompositeShape> composite = std::make_shared<nazarenko::CompositeShape>();
  composite->add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite->add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  BOOST_CHECK_THROW(composite->add(composite), std::logic_error);
}

BOOST_AUTO_TEST_CASE(incorrect_scaling_factor_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  BOOST_CHECK_THROW(composite.scale(0.0), std::invalid_argument);
  BOOST_CHECK_THROW(composite.scale(-2.7), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(incorrect_shape_factor_test)
{
  nazarenko::CompositeShape composite;
  BOOST_CHECK_THROW(composite.add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(incorrect_index_factor_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  BOOST_CHECK_THROW(composite[-2], std::invalid_argument);
  BOOST_CHECK_THROW(composite[3], std::invalid_argument);

  BOOST_CHECK_THROW(composite.remove(-3), std::invalid_argument);
  BOOST_CHECK_THROW(composite.remove(2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(composite_add_validation_test)
{
  nazarenko::CompositeShape composite;

  nazarenko::Shape::ShapePtr rect = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR));
  nazarenko::Shape::ShapePtr circ = std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC));

  composite.add(rect);
  composite.add(circ);

  BOOST_CHECK_EQUAL(composite.getSize(), 2);
  BOOST_CHECK(composite[0] == rect);
  BOOST_CHECK(composite[1] == circ);

  BOOST_CHECK_CLOSE(composite.getArea(), composite[0]->getArea() + composite[1]->getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(composite_remove_validation_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  composite.remove(0);

  BOOST_CHECK_EQUAL(composite.getSize(), 1);
  BOOST_CHECK_CLOSE(composite.getArea(), radius * radius * M_PI, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.x, centerC.x, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.y, centerC.y, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().height, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().width, 2 * radius, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_null_validation_test)
{
  nazarenko::CompositeShape composite;

  BOOST_CHECK_EQUAL(composite.getSize(), 0);
  BOOST_CHECK_CLOSE(composite.getArea(), 0.0, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().height, 0.0, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().width, 0.0, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.x, 0, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.y, 0, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_copy_constructor_validation_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  nazarenko::CompositeShape compositeShape(composite);

  BOOST_CHECK(compositeShape[0] == composite[0]);
  BOOST_CHECK(compositeShape[1] == composite[1]);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), composite.getSize());
  BOOST_CHECK_CLOSE(compositeShape.getArea(), composite.getArea(), epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, composite.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, composite.getFrameRect().pos.y, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, composite.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, composite.getFrameRect().width, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_copy_operator_validation_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  nazarenko::CompositeShape compositeShape = composite;

  BOOST_CHECK_EQUAL(compositeShape.getSize(), composite.getSize());
  BOOST_CHECK(compositeShape[0] == composite[0]);
  BOOST_CHECK(compositeShape[1] == composite[1]);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), composite.getArea(), epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, composite.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, composite.getFrameRect().pos.y, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, composite.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, composite.getFrameRect().width, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_rotate_validation_test)
{
  nazarenko::CompositeShape composite;

  composite.add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  composite.add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  const nazarenko::rectangle_t frameRect = composite.getFrameRect();

  composite.rotate(90.0);

  const double minX = composite[0]->getFrameRect().pos.x - composite[0]->getFrameRect().width / 2;
  const double maxX = composite[1]->getFrameRect().pos.x + composite[1]->getFrameRect().width / 2;
  const double minY = composite[0]->getFrameRect().pos.y - composite[0]->getFrameRect().height / 2;
  const double maxY = composite[1]->getFrameRect().pos.y + composite[1]->getFrameRect().height / 2;

  BOOST_CHECK_CLOSE(composite.getFrameRect().height, maxY - minY, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().width, maxX - minX, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.x, (maxX + minX) / 2, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.y, (maxY + minY) / 2, epsilon);
  BOOST_CHECK_EQUAL(composite.getSize(), 2);
  BOOST_CHECK_CLOSE(composite.getArea(), composite[0]->getArea() + composite[1]->getArea(), epsilon);

  composite.rotate(-90.0);

  BOOST_CHECK_CLOSE(composite.getFrameRect().height, frameRect.height, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().width, frameRect.width, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.x, frameRect.pos.x, epsilon);
  BOOST_CHECK_CLOSE(composite.getFrameRect().pos.y, frameRect.pos.y, epsilon);
  BOOST_CHECK_EQUAL(composite.getSize(), 2);
  BOOST_CHECK_CLOSE(composite.getArea(), composite[0]->getArea() + composite[1]->getArea(), epsilon);
}

BOOST_AUTO_TEST_SUITE_END();
