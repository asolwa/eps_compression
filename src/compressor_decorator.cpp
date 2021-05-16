/**
 * \file compressor_decorator.cpp
 * \brief Klasa bedaca dekoratorem bazowym klas kompresji
 */
#include "compressor_decorator.h"

BaseCompressorDecorator::BaseCompressorDecorator(std::shared_ptr<Compressor> compressor) : compressor_(compressor) {};

PointData BaseCompressorDecorator::compress(PointData data) {
    return compressor_->compress(data);
};