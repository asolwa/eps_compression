#include <sstream>
#include "eps_objects.h"


Command::Command(std::string data) : data_(data) {}
Command::~Command() {}
std::string Command::str(){ return data_; }

Header::Header(std::string data) : data_(data) {}
Header::~Header() {}
std::string Header::str(){ return data_; }

Instruction::Instruction(float x, float y, std::string cmd)
    : x_(x), y_(y), cmd_(cmd) {}
Instruction::~Instruction() {}
std::string Instruction::str(){
    std::ostringstream result;
    result << x_ << " " << y_ << " " << cmd_;
    return result.str();
}

Alias::Alias(std::pair<std::string, std::string> map) : map_(map) {}
Alias::~Alias() {}
std::string Alias::str(){ 
    std::ostringstream result;
    result << "/" << map_.first << "  " 
        << "{ " << map_.second << " } bind def";
    return result.str();
}