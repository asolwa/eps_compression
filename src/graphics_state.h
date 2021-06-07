/**
     * @file graphics_state.h
     * @brief Plik nagłówkowy dla klasy GraphicsState
     * @author Piotr Lewandowski
 */

#ifndef EPS_GRAPHICS_STATE_H
#define EPS_GRAPHICS_STATE_H

#include <vector>
#include <string>

/**
     * @class GraphicsState
     * @brief Klasa reprezentująca stan graficzny
     * @details Klasa reprezentująca stan graficzny, przechowuje aktualną ścieżkę oraz inne dane o grafice.
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

    void addToPath(std::pair<float, float> &point);

    void setCurrentPoint(std::pair<float, float> &point);

    void setLineWidth(double lineWidth);

    double getLineWidth();

private:
    std::vector<std::vector<std::pair<float, float>>> subPaths_;
    double lineWidth_{};
    std::vector<float> color_;
    std::string font_;
    std::pair<float, float> currentPoint_;
    bool lastMoveTo_;
};


#endif //EPS_GRAPHICS_STATE_H
