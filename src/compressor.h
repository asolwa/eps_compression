#ifndef COMPRESSOR
#define COMPRESSOR

#include <vector>
#include <utility>

using PointData = std::vector<std::pair<float, float>>;

class Compressor {
public:
    Compressor();
    virtual PointData compress(PointData data);
    virtual ~Compressor();
};

#endif /* COMPRESSOR */
