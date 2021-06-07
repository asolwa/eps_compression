/**
 * \file EpsLexer.cpp
 * \brief Klasa będąca reprezentacją leksera
 * \author Piotr Lewandowski
 */

#include "eps_lexer.h"

#include <regex>

#include "eps_objects.h"

std::vector<std::string> EpsLexer::tokenize(std::istream &ifs) {
    std::string line;
    getline(ifs, line);
    std::istringstream buffer(line);
    std::vector<std::string> tokenValues{std::istream_iterator<std::string>(buffer),
                                         std::istream_iterator<std::string>()};
    return tokenValues;
}

