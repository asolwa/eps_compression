#ifndef EPS_PARSER
#define EPS_PARSER

#include <iostream>
#include <memory>
#include <vector>
#include <regex>
#include "eps_objects.h"

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;

class EpsParser {
public:
    EpsDataPtr create(std::istream& ifs);
};

#endif /* EPS_PARSER */
