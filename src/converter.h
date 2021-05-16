#ifndef EPS_CONVERTER_H
#define EPS_CONVERTER_H

#include <utility>
#include <map>
#include <string>
#include <vector>
#include <stack>

#include "eps_objects.h"

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;

class Converter {
public:
    void convert(EpsDatas epsData);
    void print();
    Converter ();
private:
    void convertAlias(EpsDataPtr);
    void convertHeader(EpsDataPtr);
    void convertCommand(EpsDataPtr dataPtr);
    void convertInstruction(EpsDataPtr dataPtr);
    void checkAlias(std::string& name);
    std::map<std::string, std::string> declaredAliases;
    std::vector<std::pair<float, float>> currentLine;
    std::vector<std::vector<std::pair<float, float>>> convertedLines;
    std::vector<std::pair<float, float>> convertedPoints;
    std::pair<float, float> currentPoint;
    std::stack<std::pair<float, float>> startingPoints;
};


#endif //EPS_CONVERTER_H
