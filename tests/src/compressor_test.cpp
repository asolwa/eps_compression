#include <gtest/gtest.h>
#include <sstream> 
#include <string> 
#include <memory>
#include <math.h> 
#include "../../src/compressor.h"
#include "../../src/skip_n_compressor.h"
#include "../../src/radius_compressor.h"

epsc::PointData createData() {
    epsc::PointData data;
    data.push_back(std::make_pair(1, 1));
    data.push_back(std::make_pair(1.5, 1.5));
    data.push_back(std::make_pair(2, 2));
    data.push_back(std::make_pair(3.5, 3.5));
    data.push_back(std::make_pair(3, 3));
    data.push_back(std::make_pair(3.2, 3.2));
    data.push_back(std::make_pair(2, 2.0));
    
    return data;
}

int calculateNSkipLength(int input_size, int skip) { return ceil((float) (input_size - 1) / skip ) + 1 ; }

TEST(CompressorTest, DummyCompressorTest) {
    epsc::PointData data = createData();
    std::shared_ptr<epsc::Compressor> comp_ = std::make_shared<epsc::Compressor>();

    epsc::PointData compressed_data = comp_->compress(data);

    ASSERT_EQ(data.size(), compressed_data.size());
    ASSERT_EQ(data[0], compressed_data[0]);
    ASSERT_EQ(data[2], compressed_data[2]);
    ASSERT_EQ(data[3], compressed_data[3]);
}

TEST(CompressorTest, SkipN2CompressorTest) {
    int skip = 2;
    epsc::PointData data = createData();
    std::shared_ptr<epsc::Compressor> comp_ = std::make_shared<epsc::Compressor>();
    comp_ = std::make_shared<epsc::SkipNCompressor>(comp_);

    epsc::PointData compressed_data = comp_->compress(data);

    ASSERT_EQ(calculateNSkipLength(data.size(), skip), compressed_data.size());
    ASSERT_EQ(data[0], compressed_data[0]);
    ASSERT_EQ(data[2], compressed_data[1]);
    ASSERT_EQ(data[4], compressed_data[2]);
    ASSERT_EQ(data[6], compressed_data[3]);
}

TEST(CompressorTest, SkipN4CompressorTest) {
    int skip = 4;
    epsc::PointData data = createData();
    std::shared_ptr<epsc::Compressor> comp_ = std::make_shared<epsc::Compressor>();
    comp_ = std::make_shared<epsc::SkipNCompressor>(comp_, skip);

    epsc::PointData compressed_data = comp_->compress(data);

    ASSERT_EQ(calculateNSkipLength(data.size(), skip), compressed_data.size());
    ASSERT_EQ(data[0], compressed_data[0]);
    ASSERT_EQ(data[4], compressed_data[1]);
    ASSERT_EQ(data[6], compressed_data[2]);
}

TEST(CompressorTest, RadiusCompressorTest) {
    epsc::PointData data = createData();
    std::shared_ptr<epsc::Compressor> comp_ = std::make_shared<epsc::Compressor>();
    comp_ = std::make_shared<epsc::RadiusCompressor>(comp_, 2);

    epsc::PointData compressed_data = comp_->compress(data);

    ASSERT_EQ(2, compressed_data.size());
    ASSERT_EQ(data[0], compressed_data[0]);
    ASSERT_EQ(data[3], compressed_data[1]);
}
