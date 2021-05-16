#ifndef BASE_COMPRESSOR_DECORATOR
#define BASE_COMPRESSOR_DECORATOR

#include <memory>
#include "compressor.h"


class BaseCompressorDecorator : public Compressor {
private:
    std::shared_ptr<Compressor> compressor_;
public:
    BaseCompressorDecorator(std::shared_ptr<Compressor> compressor);
    virtual PointData compress(PointData data);
};

#endif /* BASE_COMPRESSOR_DECORATOR */
