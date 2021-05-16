#include "compressor_decorator.h"

BaseCompressorDecorator::BaseCompressorDecorator(std::shared_ptr<Compressor> compressor) : compressor_(compressor) {};

PointData BaseCompressorDecorator::compress(PointData data) {
    return compressor_->compress(data);
};