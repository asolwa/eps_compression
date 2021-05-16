#include <sstream>
#include "eps_objects.h"

EpsDataType EpsData::getDataType() {return dataType;}

Command::Command(std::string data) : data_(data) {dataType = EpsDataType::command;}
Command::~Command() {}
std::string Command::str(){ return data_; }
std::vector<std::string> Command::getValues(){
    std::vector<std::string> values{data_};
    return values;
}

Header::Header(std::string data) : data_(data) {dataType = EpsDataType::header;}
Header::~Header() {}
std::string Header::str(){ return data_; }
std::vector<std::string> Header::getValues(){
    std::vector<std::string> values{data_};
    return values;
}

Instruction::Instruction(std::vector<std::string> instructions)
    : instructions_(instructions) {dataType = EpsDataType::instruction;}
Instruction::~Instruction() {}
std::string Instruction::str(){
    std::ostringstream result;
    for(int i = 0; i < instructions_.size() - 1; ++i)
        result << instructions_[i] << " ";
    if(instructions_.size() > 0)
        result << instructions_[instructions_.size() - 1];
    return result.str();
}
std::vector<std::string> Instruction::getValues(){;
    return instructions_;
}

Alias::Alias(std::pair<std::string, std::string> map) : map_(map) {dataType = EpsDataType::alias;}
Alias::~Alias() {}
std::string Alias::str(){ 
    std::ostringstream result;
    result << "/" << map_.first << "  " 
        << "{ " << map_.second <<" } bind def";
    return result.str();
}
std::vector<std::string> Alias::getValues(){
    std::vector<std::string> values{map_.first, map_.second};
    return values;
}