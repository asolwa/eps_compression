/**
     * @file eps_objects.h
     * @brief Plik nagłówkowy dla klasy EpsData
     * @author Piotr Lewandowski
 */

#ifndef EPS_OBJECTS
#define EPS_OBJECTS

#include <string>
#include <vector>
#include <memory>

enum class EpsDataType {
    HEADER, ALIAS, INSTRUCTION
};

/**
     * @class EpsData
     * @brief Klasa reprezentująca alias, header lub instrukcję
     * @details Klasa, która zawiera zbiór tokenów oraz typ (instrukcja, alias, lub header)
     * @author Piotr Lewandowski
 */

class EpsData {
public:

    EpsData(EpsDataType dataType, std::vector<std::string> tokenValues);
    EpsData & operator=(const EpsData&) = delete;
    EpsData(const EpsData &data) = delete;

    EpsDataType getDataType() const;

    std::vector<std::string> getTokenValues() const;

private:
    std::vector<std::string> tokenValues_;
    EpsDataType dataType_;
};

#endif /* EPS_OBJECTS */
