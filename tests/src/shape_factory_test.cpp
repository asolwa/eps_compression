#include <gtest/gtest.h>
#include "../../src/shape_factory.h"

TEST(ShapeFactoryTest, CreateLineTest) {
    Shape line{{std::make_pair(67.47, 72.08), std::make_pair(77.50, 74.54), std::make_pair(84.61, 76.32),
                std::make_pair(90.13, 77.82), std::make_pair(67.47, 72.08)}, FillType::NONE};
    ShapeFactory factory;
    size_t expectedSize = 1;

    EpsDataPtr aliasRLineto(new EpsData(EpsDataType::ALIAS, {"/l", "{", "rlineto", "}", "bind", "def"}));
    EpsDataPtr aliasMoveto(new EpsData(EpsDataType::ALIAS, {"/m", "{", "moveto", "}", "bind", "def"}));
    EpsDataPtr insNewpath(new EpsData(EpsDataType::INSTRUCTION, {"newpath"}));
    EpsDataPtr insMoveto(new EpsData(EpsDataType::INSTRUCTION, {"67.47", "72.08", "m"}));
    EpsDataPtr insRLineto1(new EpsData(EpsDataType::INSTRUCTION, {"10.03", "2.46", "l"}));
    EpsDataPtr insRLineto2(new EpsData(EpsDataType::INSTRUCTION, {"7.11", "1.78", "l"}));
    EpsDataPtr insRLineto3(new EpsData(EpsDataType::INSTRUCTION, {"5.52", "1.50", "l"}));
    EpsDataPtr insClosepath(new EpsData(EpsDataType::INSTRUCTION, {"closepath"}));
    EpsDataPtr insStroke(new EpsData(EpsDataType::INSTRUCTION, {"stroke"}));
    EpsDatas data{aliasRLineto, aliasMoveto, insNewpath, insMoveto, insRLineto1, insRLineto2, insRLineto3, insClosepath,
                  insStroke};
    std::vector<ShapePtr> shapePtrs = factory.create(data);
    ASSERT_EQ(expectedSize, shapePtrs.size());
    ASSERT_EQ(FillType::NONE, shapePtrs[0]->getFillType());
    ASSERT_EQ(line.getPoints(), shapePtrs[0]->getPoints());
}

TEST(ShapeFactoryTest, MultiTokenAliasTest) {
    Shape line{{std::make_pair(67.47, 72.08), std::make_pair(77.50, 74.54), std::make_pair(84.61, 76.32),
                std::make_pair(90.13, 77.82), std::make_pair(67.47, 72.08)}, FillType::NONE};
    ShapeFactory factory;
    size_t expectedSize = 1;

    EpsDataPtr aliasRLineto(new EpsData(EpsDataType::ALIAS, {"/l", "{", "rlineto", "}", "bind", "def"}));
    EpsDataPtr aliasMoveto(new EpsData(EpsDataType::ALIAS, {"/m", "{", "moveto", "}", "bind", "def"}));
    EpsDataPtr aliasLine(new EpsData(EpsDataType::ALIAS, {"/p", "{", "10.03", "2.46", "rlineto", "}", "bind", "def"}));
    EpsDataPtr insNewpath(new EpsData(EpsDataType::INSTRUCTION, {"newpath"}));
    EpsDataPtr insMoveto(new EpsData(EpsDataType::INSTRUCTION, {"67.47", "72.08", "m"}));
    EpsDataPtr insRLineto1(new EpsData(EpsDataType::INSTRUCTION, {"p"}));
    EpsDataPtr insRLineto2(new EpsData(EpsDataType::INSTRUCTION, {"7.11", "1.78", "l"}));
    EpsDataPtr insRLineto3(new EpsData(EpsDataType::INSTRUCTION, {"5.52", "1.50", "l"}));
    EpsDataPtr insClosepath(new EpsData(EpsDataType::INSTRUCTION, {"closepath"}));
    EpsDataPtr insStroke(new EpsData(EpsDataType::INSTRUCTION, {"stroke"}));
    EpsDatas data{aliasRLineto, aliasMoveto, aliasLine, insNewpath, insMoveto, insRLineto1, insRLineto2, insRLineto3,
                  insClosepath,
                  insStroke};
    std::vector<ShapePtr> shapePtrs = factory.create(data);
    ASSERT_EQ(expectedSize, shapePtrs.size());
    ASSERT_EQ(FillType::NONE, shapePtrs[0]->getFillType());
    ASSERT_EQ(line.getPoints(), shapePtrs[0]->getPoints());
}

TEST(ShapeFactoryTest, RecursiveAliasTest) {
    Shape line{{std::make_pair(67.47, 72.08), std::make_pair(77.50, 74.54), std::make_pair(84.61, 76.32),
                std::make_pair(90.13, 77.82), std::make_pair(67.47, 72.08)}, FillType::NONE};
    ShapeFactory factory;
    size_t expectedSize = 1;

    EpsDataPtr aliasRLineto(new EpsData(EpsDataType::ALIAS, {"/l", "{", "rlineto", "}", "bind", "def"}));
    EpsDataPtr aliasMoveto(new EpsData(EpsDataType::ALIAS, {"/m", "{", "moveto", "}", "bind", "def"}));
    EpsDataPtr aliasLine(new EpsData(EpsDataType::ALIAS, {"/p", "{", "10.03", "2.46", "l", "}", "bind", "def"}));
    EpsDataPtr insNewpath(new EpsData(EpsDataType::INSTRUCTION, {"newpath"}));
    EpsDataPtr insMoveto(new EpsData(EpsDataType::INSTRUCTION, {"67.47", "72.08", "m"}));
    EpsDataPtr insRLineto1(new EpsData(EpsDataType::INSTRUCTION, {"p"}));
    EpsDataPtr insRLineto2(new EpsData(EpsDataType::INSTRUCTION, {"7.11", "1.78", "l"}));
    EpsDataPtr insRLineto3(new EpsData(EpsDataType::INSTRUCTION, {"5.52", "1.50", "l"}));
    EpsDataPtr insClosepath(new EpsData(EpsDataType::INSTRUCTION, {"closepath"}));
    EpsDataPtr insStroke(new EpsData(EpsDataType::INSTRUCTION, {"stroke"}));
    EpsDatas data{aliasRLineto, aliasMoveto, aliasLine, insNewpath, insMoveto, insRLineto1, insRLineto2, insRLineto3,
                  insClosepath,
                  insStroke};
    std::vector<ShapePtr> shapePtrs = factory.create(data);
    ASSERT_EQ(expectedSize, shapePtrs.size());
    ASSERT_EQ(FillType::NONE, shapePtrs[0]->getFillType());
    ASSERT_EQ(line.getPoints(), shapePtrs[0]->getPoints());
}

TEST(ShapeFactoryTest, SimplePointTest) {
    Shape line{{std::make_pair(295.16, 298.01), std::make_pair(295.16, 299.01), std::make_pair(296.16, 299.01),
                std::make_pair(296.16, 298.01), std::make_pair(295.16, 298.01)}, FillType::FILL};
    ShapeFactory factory;
    size_t expectedSize = 1;

    EpsDataPtr aliasR(new EpsData(EpsDataType::ALIAS,
                                  {"/r", "{", "4", "2", "roll", "moveto", "1", "copy", "3", "-1", "roll", "exch", "0",
                                   "exch", "rlineto", "0", "rlineto", "-1", "mul", "0", "exch", "rlineto", "closepath",
                                   "}", "bind", "def"}));
    EpsDataPtr aliasP(
            new EpsData(EpsDataType::ALIAS, {"/p", "{", "gsave", "fill", "grestore", "newpath", "}", "bind", "def"}));
    EpsDataPtr insPoint(new EpsData(EpsDataType::INSTRUCTION, {"295.16", "298.01", "1.00", "1.00", "r", "p"}));
    EpsDatas data{aliasR, aliasP, insPoint};
    std::vector<ShapePtr> shapePtrs = factory.create(data);
    ASSERT_EQ(expectedSize, shapePtrs.size());
    ASSERT_EQ(FillType::FILL, shapePtrs[0]->getFillType());
    ASSERT_EQ(line.getPoints(), shapePtrs[0]->getPoints());
}

TEST(ShapeFactoryTest, PointTest) {
    Shape line{{std::make_pair(295.16, 298.01), std::make_pair(295.16, 299.01), std::make_pair(296.16, 299.01),
                std::make_pair(296.16, 298.01), std::make_pair(295.16, 298.01)}, FillType::FILL};
    ShapeFactory factory;
    size_t expectedSize = 2;

    EpsDataPtr aliasR(new EpsData(EpsDataType::ALIAS,
                                  {"/r", "{", "4", "2", "roll", "moveto", "1", "copy", "3", "-1", "roll", "exch", "0",
                                   "exch", "rlineto", "0", "rlineto", "-1", "mul", "0", "exch", "rlineto", "closepath",
                                   "}", "bind", "def"}));
    EpsDataPtr aliasP(
            new EpsData(EpsDataType::ALIAS,
                        {"/p", "{", "gsave", "fill", "grestore", "stroke", "newpath", "}", "bind", "def"}));
    EpsDataPtr insPoint(new EpsData(EpsDataType::INSTRUCTION, {"295.16", "298.01", "1.00", "1.00", "r", "p"}));
    EpsDatas data{aliasR, aliasP, insPoint};
    std::vector<ShapePtr> shapePtrs = factory.create(data);
    ASSERT_EQ(expectedSize, shapePtrs.size());
    ASSERT_EQ(FillType::FILL, shapePtrs[0]->getFillType());
    ASSERT_EQ(line.getPoints(), shapePtrs[0]->getPoints());
    ASSERT_EQ(FillType::NONE, shapePtrs[1]->getFillType());
    ASSERT_EQ(line.getPoints(), shapePtrs[1]->getPoints());
}
