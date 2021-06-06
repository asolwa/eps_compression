#ifndef EPS_SHAPE_H
#define EPS_SHAPE_H

#include <vector>

enum class FillType{
    none, fill, eofill
};

class Shape {
public:
    Shape(std::vector<std::pair<float, float>> points, FillType fillType);
    std::vector<std::pair<float, float>> getPoints() const;
    FillType getFillType() const;
private:
    std::vector<std::pair<float, float>> points_;
    FillType fillType_;
};


#endif //EPS_SHAPE_H
