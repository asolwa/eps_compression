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

class EpsParser {
public:
    EpsDatas parse(std::vector<std::vector<std::string>> &tokens);

    EpsParser();

private:
    EpsDatas eps_datas_;
};


#endif //EPS_PARSER
