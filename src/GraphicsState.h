#ifndef EPS_GRAPHICSSTATE_H
#define EPS_GRAPHICSSTATE_H

#include <vector>
#include <string>

class GraphicsState {
public:
    GraphicsState();
    std::vector<std::vector<std::pair<float, float>>> getPath();
    void setColor(std::string &color);
    void setFont(std::string &font);
    void clearPath();
    void closePath();
    void addToPath(std::pair<float, float> &point);
    void changeCurrentPoint(std::pair<float, float> &point);

private:
    std::vector<std::vector<std::pair<float, float>>> subPaths_;
    double lineWidth_{};
    std::string color_;
    std::string font_;
    std::pair<float, float> currentPoint_;
    bool lastMoveTo_;
};


#endif //EPS_GRAPHICSSTATE_H
