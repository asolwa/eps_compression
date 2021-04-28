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

void EpsLoader::load()
{
    int temp;
    cout << "Wczytywanie pliku " << name_ <<  " eps do kompresji" << endl;
    ifstream MyReadFile(name_);

    bool data = false;
    string myText;
    int start_pos;
    int finish_pos;
    while (getline(MyReadFile, myText))
    {
        // zapisz bo to metadane eps/ konfiguracja
        if (myText.rfind("%%", 0) == 0)
            config_ << myText << endl;
        // proces aliasy
        start_pos = myText.rfind("/");
        if (start_pos >= 0)
        {
            string key, value;
            smatch reg_value;
            finish_pos = myText.find(' ');
            key = myText.substr(start_pos + 1, finish_pos);
            regex e("\\{ ([^\\s]+) \\}");
            if (regex_search(myText, reg_value, e))
                value = reg_value[1];
            aliases[key] = value;
        }
        //process liczby
        if (data)
        {
            smatch reg_value;
            regex e("([\\d\\.]+) ([\\d\\.]+) ([\\w])");
            if (regex_search(myText, reg_value, e))
            {
                float x = stof(reg_value[1]);
                float y = stof(reg_value[2]);
                ins_.push_back(EpsInstruction(x, y, reg_value[3]));
            } else {
                draw_cmd_ << myText << endl;
            }
        }
        if (myText == string("newpath"))
            data = true;
        continue;
    }

    MyReadFile.close();
}

void EpsLoader::compress_eps()
{
    cout << name_ << "Zapisywanie" << endl;
    ofstream MyReadFile("out.eps");

    //write config
    MyReadFile << config_.str() << endl;

    //writ macros
    for (auto& el: aliases) {
        MyReadFile<<"/" << el.first << "   { " << el.second <<" } bind def" << endl;
    }

    MyReadFile << endl;
    int a;
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
