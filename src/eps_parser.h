/**
     * @file eps_parser.h
     * @brief Plik nagłówkowy dla klasy EpsParser
     * @author Piotr Lewandowski
 */

#ifndef EPS_PARSER
#define EPS_PARSER

#include <utility>
#include <map>
#include <string>
#include <vector>
#include <stack>

#include "eps_objects.h"

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;

/**
     * @class EpsParser
     * @brief Klasa będąca reprezentacją parsera
     * @details Klasa, której zadaniem jest podzielenielenie
                otrzymanych tokenów na instrukcje, aliasy i headery.
     * @author Piotr Lewandowski
 */

class EpsParser {
public:
    EpsParser();
    EpsParser & operator=(const EpsParser&) = delete;
    EpsParser(const EpsParser &parser) = delete;

    /**
         * Metoda, która dzieli wczytane tokeny na grupy tworzące alias, instrukcję lub header,
         * tworzy z nich obiekty typu EpsData i zwraca wektor wskaźników na utworzone obiekty.
         * @param tokens Wektor wektorów tokenów do parsowania.
    */
    EpsDatas parse(std::vector<std::vector<std::string>> &tokens);

private:
    EpsDatas eps_datas_;
};


#endif //EPS_PARSER
