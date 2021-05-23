#include <gtest/gtest.h>
#include "../../src/shape_factory.h"

TEST(ShapeFactoryTest, CreateLineTest) {
    Shape line{{std::make_pair(67.47, 72.08), std::make_pair(77.50, 74.54), std::make_pair(84.61, 76.32),
                       std::make_pair(90.13, 77.82), std::make_pair(67.47, 72.08)}, FillType::none};
    ShapeFactory factory;
    size_t expectedSize = 1;

    EpsDataPtr aliasRLineto(new EpsData(EpsDataType::alias, {"/l", "{", "rlineto", "}", "bind", "def"}));
    EpsDataPtr aliasMoveto(new EpsData(EpsDataType::alias, {"/m", "{", "moveto", "}", "bind", "def"}));
    EpsDataPtr insNewpath(new EpsData(EpsDataType::instruction, {"newpath"}));
    EpsDataPtr insMoveto(new EpsData(EpsDataType::instruction, {"67.47", "72.08", "m"}));
    EpsDataPtr insRLineto1(new EpsData(EpsDataType::instruction, {"10.03", "2.46", "l"}));
    EpsDataPtr insRLineto2(new EpsData(EpsDataType::instruction, {"7.11", "1.78", "l"}));
    EpsDataPtr insRLineto3(new EpsData(EpsDataType::instruction, {"5.52", "1.50", "l"}));
    EpsDataPtr insClosepath(new EpsData(EpsDataType::instruction, {"closepath"}));
    EpsDataPtr insStroke(new EpsData(EpsDataType::instruction, {"stroke"}));
    EpsDatas data{aliasRLineto, aliasMoveto, insNewpath, insMoveto, insRLineto1, insRLineto2, insRLineto3, insClosepath,
                  insStroke};
    std::vector<ShapePtr> shapePtrs = factory.create(data);
    ASSERT_EQ(expectedSize, shapePtrs.size());
    ASSERT_EQ(FillType::none, shapePtrs[0]->getFillType());
    ASSERT_EQ(line.getPoints(), shapePtrs[0]->getPoints());
}