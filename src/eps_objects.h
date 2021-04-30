#ifndef EPS_OBJECTS
#define EPS_OBJECTS

#include <string>

class EpsData {
public:
    virtual std::string str() = 0;
    virtual ~EpsData() {}
};

class Header : public EpsData {
    std::string data_;
public:
    Header(std::string data);
    ~Header();
    virtual std::string str();
};

class Instruction : public EpsData {
    std::string cmd_;
    float x_, y_;
public:
    Instruction(float x, float y, std::string cmd);
    ~Instruction();
    virtual std::string str();
};

class Alias : public EpsData {
    std::pair<std::string, std::string> map_;
public:
    Alias(std::pair<std::string, std::string> map);
    ~Alias();
    virtual std::string str();
};

class Command : public EpsData {
    std::string data_;
public:
    Command(std::string data);
    ~Command();
    virtual std::string str();
};

#endif /* EPS_OBJECTS */
