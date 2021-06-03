#include <fstream>
#include <string>
#include "eps_loader.h"

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
    std::ofstream out_file("wynik.eps");

    out_file.close();
}