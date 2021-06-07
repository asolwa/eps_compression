/**
     * @file shape.cpp
     * @brief Plik zawierajacy klasę Shape
     * @author Piotr Lewandowski
 */

#include "shape.h"

#include <utility>

Shape::Shape(std::vector<std::pair<float, float>> points, FillType fillType) : points_(std::move(points)),
                                                                               fillType_(fillType){}

std::vector<std::pair<float, float>> Shape::getPoints() const {
    return points_;
}

FillType Shape::getFillType() const {
    return fillType_;
}


