#include <gtest/gtest.h>
#include "../../src/shape.h"

TEST(ShapeTest, getMethodsTest) {
    std::vector<std::pair<float, float>> points{std::make_pair(5.12,2.41),std::make_pair(5.98,2.32)};
    FillType fillType(FillType::fill);
    Shape shape(points, fillType);
    ASSERT_EQ(fillType, shape.getFillType());
    ASSERT_EQ(points, shape.getPoints());
}