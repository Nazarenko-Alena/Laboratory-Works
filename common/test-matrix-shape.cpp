#include <stdexcept>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "matrix-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(test_for_matrix_shape)

const double width = 5.5;
const double height = 2.3;
const double radius = 2.7;
const nazarenko::point_t centerR{ 2.308,0.5 };
const nazarenko::point_t centerC{ 1.3,2.5 };

BOOST_AUTO_TEST_CASE(matrix_shape_null_validation_test)
{
  nazarenko::MatrixShape matrix;

  BOOST_CHECK_EQUAL(matrix.getNumberOfLines(), 0);
  BOOST_CHECK_THROW(matrix[0], std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(matrix_shape_add_validation_test)
{
  nazarenko::MatrixShape matrix;

  nazarenko::Shape::ShapePtr rect = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR));
  nazarenko::Shape::ShapePtr circ = std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC));

  matrix.addLine().add(rect);
  matrix.addLine().add(circ);
  matrix[1].add(rect);

  BOOST_CHECK_EQUAL(matrix.getNumberOfLines(), 2);
  BOOST_CHECK_EQUAL(matrix[0][0], rect);
  BOOST_CHECK_EQUAL(matrix[1][0], circ);
  BOOST_CHECK_EQUAL(matrix[1][1], rect);
}

BOOST_AUTO_TEST_CASE(incorrect_index_factor_test)
{
  nazarenko::MatrixShape matrix;

  matrix.addLine().add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  matrix[0].add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  BOOST_CHECK_THROW(matrix[-2], std::invalid_argument);
  BOOST_CHECK_THROW(matrix[10], std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(matrix_shape_copy_constructor_validation_test)
{
  nazarenko::MatrixShape matrix;

  matrix.addLine().add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  matrix[0].add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  nazarenko::MatrixShape matrixShape(matrix);

  BOOST_CHECK(matrixShape[0][0] == matrix[0][0]);
  BOOST_CHECK(matrixShape[0][1] == matrix[0][1]);
  BOOST_CHECK_EQUAL(matrixShape.getNumberOfLines(), matrix.getNumberOfLines());
}

BOOST_AUTO_TEST_CASE(matrix_shape_copy_operator_validation_test)
{
  nazarenko::MatrixShape matrix;

  matrix.addLine().add(std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(height, width, centerR)));
  matrix[0].add(std::make_shared<nazarenko::Circle>(nazarenko::Circle(radius, centerC)));

  nazarenko::MatrixShape matrixShape = matrix;

  BOOST_CHECK(matrixShape[0][0] == matrix[0][0]);
  BOOST_CHECK(matrixShape[0][1] == matrix[0][1]);
  BOOST_CHECK_EQUAL(matrixShape.getNumberOfLines(), matrix.getNumberOfLines());
}

BOOST_AUTO_TEST_CASE(incorrect_shape_factor_test)
{
  nazarenko::MatrixShape matrix;
  BOOST_CHECK_THROW(matrix.addLine().add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END();
