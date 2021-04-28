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

void EpsLoader::load()
{
    cout << "Wczytywanie pliku " << name_ <<  " eps do kompresji" << endl;
    ifstream MyReadFile(name_);

    bool data = false;
    string myText;
    smatch reg_value;
    int start_pos, finish_pos;

    regex regex_header("^%.+$");
    regex regex_alias("^\\/(\\w+) +\\{ (\\w+) \\} bind def$");
    regex regex_ins("([\\d\\.]+) ([\\d\\.]+) ([\\w])");



    while (getline(MyReadFile, myText))
    {
        // zapisz bo to metadane eps/ konfiguracja
        if (regex_match(myText, regex_header))
        {
            header_ << myText << endl;

        } else if (regex_search(myText, reg_value, regex_alias)) {
            // proces aliasy
            string key = reg_value[1];
            string value = reg_value[2];
            aliases[key] = value;
        } else if (regex_search(myText, reg_value, regex_ins)) {
            //process liczby
            float x = stof(reg_value[1]);
            float y = stof(reg_value[2]);
            ins_.push_back(EpsInstruction(x, y, reg_value[3]));
        } else if (myText != string("newpath")) {
            // draw commands
            draw_cmd_ << myText << endl;
        }
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

    //writ macros
    for (auto& el: aliases) {
        MyReadFile<<"/" << el.first << "   { " << el.second <<" } bind def" << endl;
    }

    MyReadFile << "newpath" << endl;
    int num = 0;
    for(auto& el: ins_) {
        if( el.cmd_ == "lineto")
            MyReadFile<< el.x_ << " " << el.y_ << " " << el.cmd_ << endl;
        if( num%2 == 1){
            num = 0;
            continue;
        }
        else
            MyReadFile<< el.x_ << " " << el.y_ << " " << el.cmd_ << endl;
        ++num;
    }

    MyReadFile << draw_cmd_.str() << endl;

    MyReadFile.close();
}
