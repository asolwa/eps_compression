#include <gtest/gtest.h>
#include "../../src/eps_parser.h"

TEST(EPSParserTest, ParseLinetoTest) {
    EpsParser parser;
    std::vector<std::vector<std::string>> tokenValues{{"7.11", "1.78", "l"}};
    ASSERT_EQ(EpsDataType::instruction, parser.parse(tokenValues)[0]->getDataType());
    ASSERT_EQ(tokenValues[0], parser.parse(tokenValues)[0]->getTokenValues());
}

TEST(EPSParserTest, ParseAliasTest) {
    EpsParser parser;
    std::vector<std::vector<std::string>> tokenValues{{"/m", "{", "moveto", "}", "bind", "def"}};
    ASSERT_EQ(EpsDataType::alias, parser.parse(tokenValues)[0]->getDataType());
}