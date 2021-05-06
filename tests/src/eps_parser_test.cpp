#include <gtest/gtest.h>
#include <sstream> 
#include <string> 
#include "../../src/eps_objects.h"
#include "../../src/eps_parser.h"

TEST(EPSParserTest, AliasTest) {
    EpsParser parser;
    std::string line = "/m { moveto } bind def";
    std::istringstream iss (line);

    EpsDataPtr obj = parser.create(iss);
    ASSERT_EQ("/m  { moveto } bind def", obj->str());
}

TEST(EPSParserTest, HeaderTest) {
    EpsParser parser;
    std::string line = "%%BoundingBox: 0 0 302 302";
    std::istringstream iss (line);

    EpsDataPtr obj = parser.create(iss);
    ASSERT_EQ("%%BoundingBox: 0 0 302 302", obj->str());
}

TEST(EPSParserTest, InstructionTest) {
    EpsParser parser;
    std::string line = "10.03 2.46 l";
    std::istringstream iss (line);

    EpsDataPtr obj = parser.create(iss);
    ASSERT_EQ("10.03 2.46 l", obj->str());
}

TEST(EPSParserTest, CommandTest) {
    EpsParser parser;
    std::string line = "newpath";
    std::istringstream iss (line);

    EpsDataPtr obj = parser.create(iss);
    ASSERT_EQ("newpath", obj->str());
}