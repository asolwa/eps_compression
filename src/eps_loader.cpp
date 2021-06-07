#include <fstream>
#include <string>
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
        if (shape->getFillType() == FillType::NONE)
            writeLine(out_file, shape);
        else if(!done) {
            done = true;
            writePoints(out_file);
        }
    }
    out_file.close();
}

void EpsLoader::writePoints(std::ofstream &out_file) {
    PointsJoiner joiner(20, 0.5);
    Points data = joiner.join(shapes_);

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