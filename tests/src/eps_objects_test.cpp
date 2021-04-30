#include "../../src/eps_objects.h"
#include <gtest/gtest.h>

TEST(EPSObjectsTest, HeaderTest) {
    Header header_("%%BoundingBox: 0 0 302 302");
    ASSERT_EQ("%%BoundingBox: 0 0 302 302", header_.str());
}

TEST(EPSObjectsTest, InstructionTest) {
    Instruction ins_(5.11, 6.12, "moveto");
    ASSERT_EQ("5.11 6.12 moveto", ins_.str());
}

TEST(EPSObjectsTest, CommandTest) {
    Command cmd_("newpath");
    ASSERT_EQ("newpath", cmd_.str());
}

TEST(EPSObjectsTest, AliasTest) {
    Alias alias_(std::pair<std::string, std::string>("m", "moveto"));
    ASSERT_EQ("/m  { moveto } bind def", alias_.str());
}