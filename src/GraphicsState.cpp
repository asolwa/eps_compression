#include "GraphicsState.h"

GraphicsState::GraphicsState() : lastMoveTo_(false), lineWidth_(0) {}

std::vector<std::vector<std::pair<float, float>>> GraphicsState::getPath() {
    return subPaths_;
}

void GraphicsState::setColor(std::string &color) {
    color_ = color;
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

void GraphicsState::changeCurrentPoint(std::pair<float, float> &point) {
    currentPoint_ = point;
    lastMoveTo_ = true;
}