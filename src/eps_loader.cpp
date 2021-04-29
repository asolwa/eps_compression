#include "eps_loader.h"
#include <fstream>
#include <iostream>
#include <string>

void EpsLoader::setInFile(std::string name) { in_name_ = name; };
void EpsLoader::setOutFile(std::string name) { out_name_ = name; };

EpsDatas EpsLoader::readFromFile(std::ifstream& ifs)
{
    EpsDatas datas_;
    while(ifs) {
        EpsDataPtr data = parser.create(ifs);
        datas_.push_back(data);
    }
    return datas_;
}

void EpsLoader::load()
{
    cout << "Wczytywanie pliku " << in_name_ <<  " eps do kompresji" << endl;

    ifstream in_file(in_name_);
    eps_datas = readFromFile(in_file);

    in_file.close();
}


void EpsLoader::write()
{
    cout << "Zapisywanie do pliku " << out_name_ << endl;

    ofstream out_file(out_name_);

    for(auto data : eps_datas)
        out_file << data->str() << endl;

    out_file.close();
}
