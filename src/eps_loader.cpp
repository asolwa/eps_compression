#include <fstream>
#include <iostream>
#include <string>
#include "eps_loader.h"

void EpsLoader::setInFile(std::string name) { in_name_ = name; };
void EpsLoader::setOutFile(std::string name) { out_name_ = name; };

EpsDatas EpsLoader::readFromFile(std::ifstream& ifs)
{
    EpsDatas datas_;
    while(ifs) {
        EpsDataPtr data = parser_.create(ifs);
        datas_.push_back(data);
    }
    return datas_;
}

void EpsLoader::load()
{
    std::ifstream in_file(in_name_);
    eps_datas_ = readFromFile(in_file);

    in_file.close();
}

void EpsLoader::write()
{
    std::ofstream out_file(out_name_);

    for(auto& data : eps_datas_)
        out_file << data->str() << std::endl;

    out_file.close();
}

void EpsLoader::print(){
    for()
  //converter_.print();
}

void EpsLoader::convert() {
    converter_.convert(eps_datas_);
};
