#include <gtest/gtest.h>
#include "../../src/eps_objects.h"

TEST(EPSObjectsTest, getMethodsTest) {
    std::vector<std::string> tokenValues{"%%BoundingBox:", "0", "0", "302", "302"};
    EpsData header_(EpsDataType::HEADER, tokenValues);
    ASSERT_EQ(EpsDataType::HEADER, header_.getDataType());
    ASSERT_EQ(tokenValues, header_.getTokenValues());
}