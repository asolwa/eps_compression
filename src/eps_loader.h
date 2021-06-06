#ifndef EPS_LOADER
#define EPS_LOADER

#include <string>
#include <vector>
#include <sstream> 
#include <memory>
#include <unordered_map>
#include <utility>
#include "eps_objects.h"
#include "eps_lexer.h"
#include "eps_parser.h"
#include "shape.h"
#include "shape_factory.h"

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;
using ShapePtr = std::shared_ptr<Shape>;

class EpsLoader {
public:
    void load();
    void write();
    void setInFile(std::string& name);
    void setOutFile(std::string& name);
    EpsDatas readFromFile(std::ifstream& ifs);

private:
    void writeLine(std::ofstream &out_file, ShapePtr &shape);
    void writeAliases(std::ofstream &out_file);

    std::string in_name_;
    std::string out_name_;
    EpsDatas eps_datas_;
    EpsLexer lexer_;
    EpsParser parser_;
    std::vector<ShapePtr> shapes_;
    ShapeFactory shapeFactory_;
};

#endif /* EPS_LOADER */
