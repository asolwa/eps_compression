#ifndef EPS_SHAPE_FACTORY_H
#define EPS_SHAPE_FACTORY_H

#include "eps_objects.h"
#include "shape.h"

#include <utility>
#include <unordered_map>
#include <string>
#include <stack>

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;
using ShapePtr = std::shared_ptr<Shape>;

class ShapeFactory {

public:
    ShapeFactory();

    std::vector<ShapePtr> create(EpsDatas epsData);

private:
    void convertAlias(EpsDataPtr &);

    void convertHeader(EpsDataPtr &);

    void convertInstruction(EpsDataPtr &dataPtr);

    bool replaceAlias(std::string &name, std::stack<std::string> &pendingInstructions);

    std::stack<std::string> pendingInstructions_;
    std::unordered_map<std::string, std::vector<std::string>> declaredAliases_;
    std::vector<std::pair<float, float>> currentLine_;
    std::pair<float, float> currentPoint_;
    FillType currentFillType_;
    std::vector<ShapePtr> shapes_;
};


#endif //EPS_SHAPE_FACTORY_H
