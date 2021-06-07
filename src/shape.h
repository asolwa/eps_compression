/**
     * @file shape.h
     * @brief Plik nagłówkowy dla klasy Shape
     * @author Piotr Lewandowski
 */

#ifndef EPS_SHAPE_H
#define EPS_SHAPE_H

#include <vector>

enum class FillType {
    NONE, FILL, EOFILL
};

/**
     * @class Shape
     * @brief Klasa będąca reprezentacją figury
     * @details Klasa, która zawiera istotne przy kompresji składowe figur
     * @author Piotr Lewandowski
 */

class Shape {
public:
    Shape(std::vector<std::pair<float, float>> points, FillType fillType);
    Shape & operator=(const Shape&) = delete;
    Shape(const Shape &shape) = delete;

    std::vector<std::pair<float, float>> getPoints() const;

    FillType getFillType() const;

private:
    std::vector<std::pair<float, float>> points_;
    FillType fillType_;
};


#endif //EPS_SHAPE_H
