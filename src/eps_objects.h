#ifndef EPS_OBJECTS
#define EPS_OBJECTS

#include <string>
#include <vector>
#include <memory>


enum class EpsDataType{header, alias, instruction, command};

class EpsData {
public:
    virtual std::string str() = 0;
    virtual ~EpsData() {}
    EpsDataType getDataType();
    virtual std::vector<std::string> getValues() = 0;
protected:
    EpsDataType dataType;
};

class Header : public EpsData {
    std::string data_;
public:
    Header(std::string data);
    ~Header();
    virtual std::string str();
    virtual std::vector<std::string> getValues();
};

class Instruction : public EpsData {
    std::vector<std::string> instructions_;
public:
    Instruction(std::vector<std::string> instructions);
    ~Instruction();
    virtual std::string str();
    virtual std::vector<std::string> getValues();
};

class Alias : public EpsData {
    std::pair<std::string, std::string> map_;
public:
    Alias(std::pair<std::string, std::string> map);
    ~Alias();
    virtual std::string str();
    virtual std::vector<std::string> getValues();
};

class Command : public EpsData {
    std::string data_;
public:
    Command(std::string data);
    ~Command();
    virtual std::string str();
    virtual std::vector<std::string> getValues();
};

#endif /* EPS_OBJECTS */
