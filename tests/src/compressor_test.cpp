#include <gtest/gtest.h>
#include <sstream> 
#include <string> 
#include <memory>
#include <math.h> 
#include "../../src/skip_n_compressor.h"
#include "../../src/compressor.h"

PointData createData() {
    PointData data;
    data.push_back(std::make_pair(1, 2.2));
    data.push_back(std::make_pair(2, 3.2));
    data.push_back(std::make_pair(3, 4.2));
    data.push_back(std::make_pair(4, 5.2));
    data.push_back(std::make_pair(5, 6.2));
    data.push_back(std::make_pair(6, 7.2));
    data.push_back(std::make_pair(7, 8.2));
    
    return data;
}

int calculateNSkipLength(int input_size, int skip) { return ceil((float) (input_size - 1) / skip ) + 1 ; }

TEST(CompressorTest, DummyCompressorTest) {
    PointData data = createData();
    std::shared_ptr<Compressor> comp_ = std::make_shared<Compressor>();

    PointData compressed_data = comp_->compress(data);

    ASSERT_EQ(data.size(), compressed_data.size());
    ASSERT_EQ(data[0], compressed_data[0]);
    ASSERT_EQ(data[2], compressed_data[2]);
    ASSERT_EQ(data[3], compressed_data[3]);
}

TEST(CompressorTest, SkipN2CompressorTest) {
    int skip = 2;
    PointData data = createData();
    std::shared_ptr<Compressor> comp_ = std::make_shared<Compressor>();


    comp_ = std::make_shared<SkipNCompressor>(comp_);
    PointData compressed_data = comp_->compress(data);

    ASSERT_EQ(calculateNSkipLength(data.size(), skip), compressed_data.size());
    ASSERT_EQ(data[0], compressed_data[0]);
    ASSERT_EQ(data[2], compressed_data[1]);
    ASSERT_EQ(data[4], compressed_data[2]);
    ASSERT_EQ(data[6], compressed_data[3]);
}

TEST(CompressorTest, SkipN4CompressorTest) {
    int skip = 4;
    PointData data = createData();
    std::shared_ptr<Compressor> comp_ = std::make_shared<Compressor>();


    comp_ = std::make_shared<SkipNCompressor>(comp_, skip);
    PointData compressed_data = comp_->compress(data);

    ASSERT_EQ(calculateNSkipLength(data.size(), skip), compressed_data.size());
    ASSERT_EQ(data[0], compressed_data[0]);
    ASSERT_EQ(data[4], compressed_data[1]);
    ASSERT_EQ(data[6], compressed_data[2]);
}
