/**
     * @file graphics_state.cpp
     * @brief Plik zawierajacy klasę GraphicsState
     * @author Piotr Lewandowski
 */

#include "graphics_state.h"

#include <utility>

GraphicsState::GraphicsState() : lastMoveTo_(false), lineWidth_(1) {}

std::vector<std::vector<std::pair<float, float>>> GraphicsState::getPath() {
    return subPaths_;
}

void GraphicsState::setColor(std::vector<float> color) {
    color_ = std::move(color);
}

void GraphicsState::setFont(std::string &font) {
    font_ = font;
}

void GraphicsState::clearPath() {
    subPaths_.clear();
}

void GraphicsState::closePath() {
    if (!subPaths_.empty())
        if (!subPaths_.back().empty())
            subPaths_.back().push_back(subPaths_.back().front());
}

void GraphicsState::addToPath(std::pair<float, float> &point) {
    if (lastMoveTo_) {
        subPaths_.push_back(std::vector<std::pair<float, float>>{currentPoint_, point});
        currentPoint_ = point;
    } else if (!subPaths_.empty())
        subPaths_.back().push_back(point);
    lastMoveTo_ = false;
}

void GraphicsState::setCurrentPoint(std::pair<float, float> &point) {
    currentPoint_ = point;
    lastMoveTo_ = true;
}

void GraphicsState::setLineWidth(double lineWidth) {
    lineWidth_ = lineWidth;
}

double GraphicsState::getLineWidth() const {
    return lineWidth_;
}