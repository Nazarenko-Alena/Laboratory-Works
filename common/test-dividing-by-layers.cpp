#include <stdexcept>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "matrix-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"
#include "dividing-by-layers.hpp"

BOOST_AUTO_TEST_SUITE(test_for_divide_by_layers)

BOOST_AUTO_TEST_CASE(divide_by_layers_validation_test)
{
  nazarenko::MatrixShape matrix;

  nazarenko::Shape::ShapeArray arr = std::make_unique<nazarenko::Shape::ShapePtr[]>(3);

  std::shared_ptr<nazarenko::Shape> rectangleTwo = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(1.0, 1.0, { -23.8,-23.0 }));
  std::shared_ptr<nazarenko::Shape> rectangle = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(2.3, 5.5, { 0,2.6 }));
  std::shared_ptr<nazarenko::Shape> circle = std::make_shared<nazarenko::Circle>(nazarenko::Circle(5.3, { 6.7,0.8 }));

  arr[0] = rectangleTwo;
  arr[1] = rectangle;
  arr[2] = circle;

  matrix = nazarenko::divideByLayers(arr,3);

  BOOST_CHECK_EQUAL(matrix.getNumberOfLines(), 2);
  BOOST_CHECK_EQUAL(matrix[0][0], rectangleTwo);
  BOOST_CHECK_EQUAL(matrix[0][1], rectangle);
  BOOST_CHECK_EQUAL(matrix[1][0], circle);
}

BOOST_AUTO_TEST_SUITE_END();
