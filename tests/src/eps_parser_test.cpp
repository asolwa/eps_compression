#include <gtest/gtest.h>
#include "../../src/eps_parser.h"

TEST(EPSParserTest, ParseLinetoTest) {
    EpsParser parser;
    std::vector<std::vector<std::string>> tokenValues{{"7.11", "1.78", "l"}};
    ASSERT_EQ(EpsDataType::INSTRUCTION, parser.parse(tokenValues)[0]->getDataType());
    ASSERT_EQ(tokenValues[0], parser.parse(tokenValues)[0]->getTokenValues());
}

TEST(EPSParserTest, ParseAliasTest) {
    EpsParser parser;
    std::vector<std::vector<std::string>> tokenValues{{"/m", "{", "moveto", "}", "bind", "def"}};
    ASSERT_EQ(EpsDataType::ALIAS, parser.parse(tokenValues)[0]->getDataType());
}

TEST(EPSParserTest, MultiLineAliasTest) {
    EpsParser parser;
    size_t expectedSize = 1;
    std::vector<std::string> tokens{"/m", "{", "moveto", "}", "bind", "def"};
    std::vector<std::vector<std::string>> tokenValues{{"/m", "{"},
                                                      {"moveto"},
                                                      {"}",  "bind", "def"}};
    EpsDatas datas = parser.parse(tokenValues);
    ASSERT_EQ(expectedSize, datas.size());
    ASSERT_EQ(EpsDataType::ALIAS, datas[0]->getDataType());
    ASSERT_EQ(tokens, datas[0]->getTokenValues());
}

TEST(EPSParserTest, EmptyTokensTest) {
    EpsParser parser;
    size_t expectedSize = 0;
    std::vector<std::vector<std::string>> tokenValues{{}};
    EpsDatas datas = parser.parse(tokenValues);
    ASSERT_EQ(expectedSize, datas.size());
}