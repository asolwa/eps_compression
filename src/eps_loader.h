#ifndef EPS_LOADER
#define EPS_LOADER

#include <string>
#include <vector>
#include <sstream> 
#include <memory>
#include <unordered_map>
#include <utility>
#include "eps_objects.h"
#include "parser.h"

using namespace std;

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
    string in_name_;
    string out_name_;
    EpsDatas eps_datas;
    ParserFactory parser; 
};

#endif /* EPS_LOADER */
