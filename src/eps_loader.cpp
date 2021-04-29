#include "eps_loader.h"
#include <fstream>
#include <iostream>
#include <fstream>    
#include <string>
#include <regex>

using namespace std;

EpsInstruction::EpsInstruction(float x, float y, string cmd)
    : x_(x), y_(y), cmd_(cmd) {}

EpsLoader::EpsLoader(string name)
    : name_(name)
{
    aliases["lineto"] = "lineto";
}

void EpsLoader::load_header(string &is)
{
    config_ << is << endl;
}

void EpsLoader::load_instructions(string &is)
{

}

void EpsLoader::process_line(string &line)
{
    smatch reg_value;

    regex regex_header("^%.+$");
    regex regex_alias("^\\/(\\w+) +\\{ (\\w+) \\} bind def$");
    regex regex_ins("([\\d\\.]+) ([\\d\\.]+) ([\\w])");

    if (regex_match(line, regex_header)) {
        // zapisz bo to metadane eps/ konfiguracja
        header_ << line << endl;
    } else if (regex_search(line, reg_value, regex_alias)) {
        // proces aliasy
        string key = reg_value[1];
        string value = reg_value[2];
        aliases[key] = value;
    } else if (regex_search(line, reg_value, regex_ins)) {
        //process liczby
        float x = stof(reg_value[1]);
        float y = stof(reg_value[2]);
        ins_.push_back(EpsInstruction(x, y, reg_value[3]));
    } else if (line != string("newpath")) {
        // draw commands
        draw_cmd_ << line << endl;
    }
}

void EpsLoader::load()
{
    cout << "Wczytywanie pliku " << name_ <<  " eps do kompresji" << endl;
    ifstream MyReadFile(name_);
    string line;

    while (getline(MyReadFile, line))
    {
        process_line(line);
    }

    MyReadFile.close();
}

void EpsLoader::compress_eps()
{
    cout << name_ << "Zapisywanie do pliku" << endl;
    ofstream MyReadFile("out.eps");

    //write header
    MyReadFile << header_.str() << endl;
    //write config
    MyReadFile << config_.str() << endl;

    //write macros
    for (auto& el: aliases) {
        MyReadFile<<"/" << el.first << "   { " << el.second <<" } bind def" << endl;
    }

    MyReadFile << "newpath" << endl;
    for(auto& el: ins_) {
        MyReadFile<< el.x_ << " " << el.y_ << " " << el.cmd_ << endl;
    }
    MyReadFile << draw_cmd_.str() << endl;

    MyReadFile.close();
}
