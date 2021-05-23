#include <gtest/gtest.h>
#include <sstream> 
#include <string> 
#include "../../src/eps_objects.h"
#include "../../src/eps_lexer.h"



TEST(EPSLexerTest, TokenizeHeaderTest) {
    EpsLexer lexer;
    std::string line = "%%BoundingBox: 0 0 302 302";
    std::istringstream iss (line);
    std::vector<std::string> tokenValues{"%%BoundingBox:", "0", "0", "302", "302"};

    ASSERT_EQ(tokenValues, lexer.tokenize(iss));
}

TEST(EPSLexerTest, TokenizeAliasTest) {
    EpsLexer lexer;
    std::string line = "/ep  { showpage gr gr } bind def";
    std::istringstream iss (line);
    std::vector<std::string> tokenValues{"/ep", "{", "showpage", "gr", "gr", "}", "bind", "def"};

    ASSERT_EQ(tokenValues, lexer.tokenize(iss));
}
