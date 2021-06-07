/**
     * @file shape_factory.h
     * @brief Plik nagłówkowy dla klasy ShapeFactory
     * @author Piotr Lewandowski
 */

#ifndef EPS_SHAPE_FACTORY_H
#define EPS_SHAPE_FACTORY_H

#include <utility>
#include <unordered_map>
#include <string>
#include <stack>
#include <unordered_map>

#include "eps_objects.h"
#include "shape.h"
#include "graphics_state.h"

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;
using ShapePtr = std::shared_ptr<Shape>;

/**
     * @class ShapeFactory
     * @brief Klasa tworząca obiekty Shape
     * @details Klasa, która przetwarza otrzymane aliasy oraz instrukcje i tworzy obiekty typu Shape.
     * @author Piotr Lewandowski
 */

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
    std::pair<float, float> currentPoint_;
    std::vector<ShapePtr> shapes_;
    GraphicsState graphics_;
    std::stack<GraphicsState> graphicsStack_;
};


#endif //EPS_SHAPE_FACTORY_H
