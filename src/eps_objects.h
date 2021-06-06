/**
     * @file EpsObjects.h
     * @class EpsData
     * @brief Klasa reprezentująca alias, header lub instrukcję
     * @details Klasa, która zawiera zbiór tokenów oraz typ (instrukcja, alias, lub header)
     *
     * @author Piotr Lewandowski
 */

#ifndef EPS_OBJECTS
#define EPS_OBJECTS

#include <string>
#include <vector>
#include <memory>

enum class EpsDataType {
    header, alias, instruction
};

class EpsData {
public:
    EpsData(EpsDataType dataType, std::vector<std::string> tokenValues);

    EpsDataType getDataType() const;

    std::vector<std::string> getTokenValues() const;

private:
    std::vector<std::string> tokenValues_;
    EpsDataType dataType_;
};

#endif /* EPS_OBJECTS */
