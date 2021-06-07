/**
     * @file eps_lexer.h
     * @brief Plik nagłówkowy dla klasy EpsLexer
     * @author Piotr Lewandowski
 */

#ifndef EPS_LEXER
#define EPS_LEXER

#include <iostream>
#include <memory>
#include <vector>
#include <regex>

#include "eps_objects.h"


using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;

/**
     * @class EpsLexer
     * @brief Klasa będąca reprezentacją leksera
     * @details Klasa, której zadaniem jest podzielenielenie
                danych otrzymanych ze strumienia na tokeny.
     * @author Piotr Lewandowski
 */

class EpsLexer {
public:
    std::vector<std::string> tokenize(std::istream& ifs);
};

#endif /* EPS_LEXER */
