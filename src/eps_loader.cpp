#include "eps_loader.h"
#include <fstream>
#include <iostream>
#include <fstream>    
#include <string>
#include <regex>

EpsInstruction::EpsInstruction(float x, float y, std::string cmd)
    : x_(x), y_(y), cmd_(cmd) {}

Command::Command(std::string data) : data_(data) {}
std::string Command::str(){ return data_; }

Header::Header(std::string data) : data_(data) {}
std::string Header::str(){ return data_; }

Instruction::Instruction(float x, float y, std::string cmd)
    : x_(x), y_(y), cmd_(cmd) {}
std::string Instruction::str(){
    std::ostringstream result;
    result << x_ << " " << y_ << " " << cmd_;
    return result.str();
}

Alias::Alias(std::pair<std::string, std::string> map) : map_(map) {}
std::string Alias::str(){ 
    std::ostringstream result;
    result << "/" << map_.first << "  " 
        << "{ " << map_.second << " } bind def";
    return result.str();
}

class UnknownTypeException : public std::exception { };

class EpsDataFactory {
public:
    static EpsDataFactory& getInstance() {
        static EpsDataFactory instance;
        return instance;
    }

    EpsDataPtr create(std::istream& ifs) {
        std::string line;
        smatch reg_value;

        regex regex_header("^%.+$");
        regex regex_alias("^\\/(\\w+) +\\{ (\\w+) \\} bind def$");
        regex regex_ins("([\\d\\.]+) ([\\d\\.]+) ([\\w])");

        getline(ifs, line);

        if (regex_match(line, regex_header)) {
            // zapisz bo to metadane eps/ konfiguracja
            return std::shared_ptr<EpsData>(new Header(line));
        } else if (regex_search(line, reg_value, regex_alias)) {
            // proces aliasy
            return std::shared_ptr<Alias>(
                new Alias(std::make_pair(reg_value[1], reg_value[2]))
            );
        } else if (regex_search(line, reg_value, regex_ins)) {
            //process liczby
            float x = stof(reg_value[1]);
            float y = stof(reg_value[2]);
            std::string cmd = reg_value[3].str();
            return std::shared_ptr<EpsData>(
                new Instruction(x, y, cmd)
            );
        }
        else {
            return std::shared_ptr<EpsData>(new Command(line));
        }
    }
};

void EpsLoader::setInFile(std::string name) { in_name_ = name; };
void EpsLoader::setOutFile(std::string name) { out_name_ = name; };

EpsDatas EpsLoader::readFromFile(std::ifstream& ifs)
{
    EpsDatas datas_;
    while(ifs) {
        try{
            EpsDataPtr data = EpsDataFactory::getInstance().create(ifs);
            datas_.push_back(data);
        }
        catch(UnknownTypeException&) {}
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
