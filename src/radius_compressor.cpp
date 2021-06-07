/**
 * \file radius_compressor.cpp
 * \brief Plik zawierajacy implementacje kompresora opartego o promien
 */
#include "radius_compressor.h"

namespace epsc {
    
    RadiusCompressor::RadiusCompressor(std::shared_ptr<Compressor> dec, int radius)
        : BaseCompressorDecorator(dec), thr_(radius*radius) {}

    bool RadiusCompressor::closer_than_radius(const Point &a, const Point &b){
        float dist_x = a.first - b.first;
        float dist_y = a.second - b.second;

        return dist_x * dist_x + dist_y * dist_y < thr_;
    }

    PointData RadiusCompressor::compress(const PointData &data) {
        PointData comp_data = BaseCompressorDecorator::compress(data);

        PointData comp_result = comp_data;
        Point last_point;
        int counter = 0;
        for(auto first_el = comp_result.begin() ; first_el != comp_result.end() ; ++first_el) {
            for(auto sec_el = first_el + 1 ; sec_el != comp_result.end() ;) {
                if ( closer_than_radius(*first_el, *sec_el) ){
                    sec_el = comp_result.erase(sec_el);
                } else {
                    ++sec_el;
                }
            }
        }
        return comp_result;
    }

}