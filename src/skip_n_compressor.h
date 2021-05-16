#ifndef SKIP_N_COMPRESSOR
#define SKIP_N_COMPRESSOR

#include "compressor_decorator.h"

class SkipNCompressor: public BaseCompressorDecorator {
private:
    int skip_n_;
public:
    SkipNCompressor() = delete;
    SkipNCompressor(std::shared_ptr<Compressor> dec, int skip_n=2);
    virtual PointData compress(PointData data);
};

#endif /* SKIP_N_COMPRESSOR */
