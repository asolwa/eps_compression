/**
 * \file radius_compressor.cpp
 * \brief Plik zawierajacy implementacje kompresora opartego o promien
 */
#include "radius_compressor.h"

RadiusCompressor::RadiusCompressor(std::shared_ptr<Compressor> dec, int radius)
    : BaseCompressorDecorator(dec), thr_(1) {}

bool RadiusCompressor::closer_than_radius(const Point &a, const Point &b){
    float dist_x = a.first - b.first;
    float dist_y = a.second - b.second;

    return dist_x * dist_x + dist_y * dist_y < thr_;
}

PointData RadiusCompressor::compress(const PointData &data) {
    PointData comp_data = BaseCompressorDecorator::compress(data);

    PointData comp_result;
    Point last_point;
    int counter = 0;
    for(auto &element : comp_data) {
        if (
            &element == &comp_data.front() ||
            &element == &comp_data.back() ||
            !closer_than_radius(last_point, element)
        ){
            comp_result.push_back(element);
            last_point = element;
        }
    }
    return comp_result;
}