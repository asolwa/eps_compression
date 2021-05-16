/**
 * \file skip_n_compressor.cpp
 * \brief Plik zawierajacy implementacje kompresora pomijajacego co n-ty element 
 */
#include "skip_n_compressor.h"

SkipNCompressor::SkipNCompressor(std::shared_ptr<Compressor> dec, int skip)
    : BaseCompressorDecorator(dec), skip_n_(skip) {}

PointData SkipNCompressor::compress(PointData data) {
    PointData comp_data = BaseCompressorDecorator::compress(data);

    PointData comp_result;
    int counter = 0;
    for(auto &element : comp_data) {
        if (counter == 0 || element == comp_data.back())
            comp_result.push_back(element);
        counter = (++counter) % skip_n_;
    }
    return comp_result;
}