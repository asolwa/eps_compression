#ifndef EPS_SHAPE_FACTORY_H
#define EPS_SHAPE_FACTORY_H

#include <utility>
#include <unordered_map>
#include <string>
#include <stack>
#include <unordered_map>

#include "eps_objects.h"
#include "shape.h"
#include "GraphicsState.h"

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;
using ShapePtr = std::shared_ptr<Shape>;

class ShapeFactory {

public:
    std::vector<ShapePtr> create(EpsDatas epsData);

    std::vector<std::string> getHeader();

    std::unordered_map<std::string, std::vector<std::string>> getAlias();

private:
    void convertAlias(EpsDataPtr &);

    void convertHeader(EpsDataPtr &);

    void convertInstruction(EpsDataPtr &dataPtr);

    bool replaceAlias(std::string &name, std::stack<std::string> &pendingInstructions);

    std::stack<std::string> pendingInstructions_;
    std::vector<std::string> header_;
    std::unordered_map<std::string, std::vector<std::string>> declaredAliases_;
    std::vector<std::pair<float, float>> currentPath_;
    std::pair<float, float> currentPoint_;
    std::vector<ShapePtr> shapes_;
    GraphicsState graphics_;
    std::stack<GraphicsState> graphicsStack_;
};


#endif //EPS_SHAPE_FACTORY_H
