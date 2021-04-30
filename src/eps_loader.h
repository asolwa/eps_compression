#ifndef EPS_LOADER
#define EPS_LOADER

#include <string>
#include <vector>
#include <sstream> 
#include <memory>
#include <unordered_map>
#include <utility>
#include "eps_objects.h"
#include "eps_parser.h"

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;

class EpsLoader {
public:
    void load();
    void write();
    void setInFile(std::string name);
    void setOutFile(std::string name);
    EpsDatas readFromFile(std::ifstream& ifs);

private:
    std::string in_name_;
    std::string out_name_;
    EpsDatas eps_datas_;
    EpsParser parser_; 
};

#endif /* EPS_LOADER */
