#include <fstream>
#include <string>
#include <algorithm>
#include "eps_loader.h"
#include "compressor.h"
#include "skip_n_compressor.h"
#include "radius_compressor.h"

void EpsLoader::setInFile(std::string &name) { in_name_ = name; };

void EpsLoader::setOutFile(std::string &name) { out_name_ = name; };

EpsDatas EpsLoader::readFromFile(std::ifstream &ifs) {
    std::vector<std::vector<std::string>> tokens;
    while (ifs) {
        tokens.push_back(lexer_.tokenize(ifs));
    }
    return parser_.parse(tokens);
}

using Point = std::pair<float, float>;
using Points = std::vector<Point>;
Points convertPoints(std::vector<ShapePtr> &shapes_) {

    Points result;
    for(auto shape : shapes_) {
        float x=0;
        float y=0;
        float rx=0;
        float ry=0;
        Points points_ = shape->getPoints();
        std::for_each(points_.begin(), points_.end()-1, [&x, &y](const Point &el) {
            x += el.first;
            y += el.second;
        });

        x /= (points_.size() - 1);
        y /= (points_.size() - 1);

        std::for_each(points_.begin(), points_.end()-1, [&x, &y, &rx, &ry](const Point &el) {
            rx += (el.first - x) * (el.first - x);
            ry += (el.second - y) * (el.second - y);
        });

        result.push_back({points_[0].first, points_[0].second});
    }
    return result;
}

void EpsLoader::load() {
    std::ifstream in_file(in_name_);
    eps_datas_ = readFromFile(in_file);
    shapes_ = shapeFactory_.create(eps_datas_);
    in_file.close();
}

void EpsLoader::write() {
    std::ofstream out_file("wynik1.eps");

    for(auto header_element : shapeFactory_.getHeader()) {
        out_file << header_element << std::endl;
        if(header_element == "%%BeginProlog ")
            break;
    }

    writeAliases(out_file);

    Points data = convertPoints(shapes_);
    std::shared_ptr<epsc::Compressor> comp_ = std::make_shared<epsc::Compressor>();
    comp_ = std::make_shared<epsc::RadiusCompressor>(comp_, 1);
    epsc::PointData compressed_data = comp_->compress(data);
    out_file << "bp" << std::endl;
    for(auto el = compressed_data.begin(); el != compressed_data.end(); ++el)
        out_file << el->first << " " << el->second << " 1.00 1.00 r p2" << std::endl;
    out_file << "ep" << std::endl;
    // for(auto shape : shapes_) {
    //     if (shape->getFillType() == FillType::none)
    //         writeLine(out_file, shape);

    // }

    out_file.close();
}

void EpsLoader::writeLine(std::ofstream &out_file, ShapePtr &shape) {
    std::shared_ptr<epsc::Compressor> comp_ = std::make_shared<epsc::Compressor>();
    comp_ = std::make_shared<epsc::SkipNCompressor>(comp_);
    epsc::PointData compressed_data = comp_->compress(shape->getPoints());
    out_file << "newpath" << std::endl;
    auto first_el = compressed_data.front();
    out_file << first_el.first << " " << first_el.second << " x" << std::endl;

    for(auto el = compressed_data.begin() + 1; el != compressed_data.end(); ++el)
        out_file << el->first << " " << el->second << " y" << std::endl;
    out_file << "2 setlinewidth\nstroke" << std::endl;
}

void EpsLoader::writeAliases(std::ofstream &out_file) {
    out_file << "/x   { moveto } bind def" << std::endl;
    out_file << "/y   { lineto } bind def" << std::endl;
    auto aliases = shapeFactory_.getAlias();
    for(auto& alias : aliases) {
        out_file << "/" << alias.first << "   { ";
        for(auto &el : alias.second) {
            out_file << el << " ";
        }
        out_file << " } bind def" << std::endl;
    }
}