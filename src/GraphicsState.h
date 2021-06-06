#ifndef EPS_GRAPHICSSTATE_H
#define EPS_GRAPHICSSTATE_H

#include <vector>
#include <string>

/**
     * @file GraphicsState.h
     * @class GraphicsState
     * @brief Klasa reprezentujaca stan graficzny
     * @details Klasa reprezentujaca stan graficzny
     *
     * @author Piotr Lewandowski
 */

class GraphicsState {
public:
    GraphicsState();
    std::vector<std::vector<std::pair<float, float>>> getPath();
    void setColor(std::vector<float> color);
    void setFont(std::string &font);
    void clearPath();
    void closePath();
    void addToPath(std::pair<float, float>& point);
    void setCurrentPoint(std::pair<float, float> &point);

private:
    std::vector<std::vector<std::pair<float, float>>> subPaths_;
    double lineWidth_{};
    std::vector<float> color_;
    std::string font_;
    std::pair<float, float> currentPoint_;
    bool lastMoveTo_;
};


#endif //EPS_GRAPHICSSTATE_H
