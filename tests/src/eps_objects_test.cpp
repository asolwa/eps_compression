#include <gtest/gtest.h>
#include "../../src/eps_objects.h"

TEST(EPSObjectsTest, getMethodsTest) {
    std::vector<std::string> tokenValues{"%%BoundingBox:", "0", "0", "302", "302"};
    EpsData header_(EpsDataType::header, tokenValues);
    ASSERT_EQ(EpsDataType::header, header_.getDataType());
    ASSERT_EQ(tokenValues, header_.getTokenValues());
}