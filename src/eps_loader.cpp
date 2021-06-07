#include <fstream>
#include <string>
#include <algorithm>
#include "eps_loader.h"
#include "compressor.h"
#include "skip_n_compressor.h"
#include "radius_compressor.h"
#include <cmath>
#include <tuple>

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
using PointA = std::tuple<float, float, float, float>;
using Points = std::vector<Point>;
using PointsA = std::vector<PointA>;
PointsA convertPoints(std::vector<ShapePtr> &shapes_) {

    PointsA result;
    PointsA result2;
    int thr = 0.5;
    for(auto shape : shapes_) {
        float x=0;
        float y=0;
        float rx=0;
        float ry=0;
        Points points_ = shape->getPoints();


        int factor = 20;
        x = trunc(points_[0].first*factor)/factor;
        y = trunc(points_[0].second*factor)/factor;
        rx = trunc((points_[1].second - points_[0].second)*factor)/factor;
        ry = trunc((points_[2].first - points_[1].first)*factor)/factor;
        result.push_back({x, y, rx, ry});
    }

    std::sort(result.begin(), result.end(), [](const PointA &a, const PointA &b) {
        return (std::get<0>(a) < std::get<0>(b));
    });

    for(auto element = result.begin(); element != result.end(); ++element) {
        float curent_line = std::get<0>(*element);
        float curent_line1 = std::get<1>(*element);
        auto upper = std::upper_bound(result.begin(), result.end(), curent_line, [](float curent_line, PointA &a) {
            return curent_line < std::get<0>(a);
        });
        if(upper != result.end() && (upper-1) != element ) {
            std::sort(element, upper, [](const PointA &a, const PointA &b) {
                return (std::get<1>(a) < std::get<1>(b));
            });
        }
    }

    for(auto first = result.begin(); first != result.end()-1; ++first) {
        if(std::get<0>(*first) != -1) {
            for(auto sec = first + 1; sec != result.end() && ( std::get<0>(*first) == std::get<0>(*sec) || std::get<0>(*sec) == -1); ++sec) {
                if(std::get<0>(*sec) != -1) {
                    if (abs(std::get<1>(*first) - std::get<1>(*sec)) < thr) {
                        std::get<0>(*sec) = -1;
                    } else if (abs(std::get<1>(*first) - std::get<1>(*sec)) < thr + std::get<2>(*first)) {
                        std::get<3>(*first) += std::get<3>(*sec);
                        std::get<3>(*first) -= (std::get<1>(*sec) - std::get<1>(*first));
                        std::get<0>(*sec) = -1;
                    } else
                        break;
                }
            }
        }
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

    bool done = false;
    for(auto shape : shapes_) {
        if (shape->getFillType() == FillType::none)
            writeLine(out_file, shape);
        else if(!done) {
            done = true;
            writePoints(out_file);
        }
    }
    out_file.close();
}

void EpsLoader::writePoints(std::ofstream &out_file) {
    PointsA data = convertPoints(shapes_);

    out_file << "bp" << std::endl;
    for(auto el = data.begin(); el != data.end(); ++el) {
        if(std::get<0>(*el) != -1) {
            out_file << std::get<0>(*el) << " " << std::get<1>(*el)<< " " << std::get<2>(*el)<< " " << std::get<3>(*el) << " r p2" << std::endl;
        }
    }
    out_file << "ep" << std::endl;
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