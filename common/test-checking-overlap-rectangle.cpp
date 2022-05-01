#include <memory>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(test_for_checking_overlap_rect)

BOOST_AUTO_TEST_CASE(checking_overlap_rect_validation_test)
{
  nazarenko::Shape::ShapePtr rect = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(5.5, 3.3, { 3.15,23.25 }));
  nazarenko::Shape::ShapePtr rectangle = std::make_shared<nazarenko::Rectangle>(nazarenko::Rectangle(2.1, 1.5, { -18.6,-26.5 }));

  nazarenko::Shape::ShapePtr circ = std::make_shared<nazarenko::Circle>(nazarenko::Circle(1.7, { 5.4,26.2 }));
  nazarenko::Shape::ShapePtr circle = std::make_shared<nazarenko::Circle>(nazarenko::Circle(1.37, { 0.82,20.02 }));

  BOOST_CHECK(nazarenko::details::checkingOverlapRect(rect->getFrameRect(), rectangle->getFrameRect()) == false);
  BOOST_CHECK(nazarenko::details::checkingOverlapRect(rect->getFrameRect(), circ->getFrameRect()) == true);
  BOOST_CHECK(nazarenko::details::checkingOverlapRect(rect->getFrameRect(), circle->getFrameRect()) == true);
  BOOST_CHECK(nazarenko::details::checkingOverlapRect(rect->getFrameRect(), rect->getFrameRect()) == true);
}

BOOST_AUTO_TEST_SUITE_END();
