#include <gtest/gtest.h>
#include "../../src/GraphicsState.h"

TEST(GraphicsStateTest, ClearPathTest) {
    GraphicsState graphicsState;
    graphicsState.clearPath();
    std::vector<std::vector<std::pair<float, float>>> v;

    ASSERT_EQ(graphicsState.getPath(), v);
}
