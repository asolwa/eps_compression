#ifndef EPS_LOADER
#define EPS_LOADER

#include <string>
#include <vector>
#include <sstream> 
#include <memory>
#include <unordered_map>
#include <utility>

using namespace std;

class EpsData {
public:
    virtual std::string str() = 0;
};

class Header : public EpsData {
    std::string data_;
public:
    Header(std::string data);
    virtual std::string str();
};

class Instruction : public EpsData {
    std::string cmd_;
    float x_, y_;
public:
    Instruction(float x, float y, std::string cmd);
    virtual std::string str();
};

class Alias : public EpsData {
    std::pair<std::string, std::string> map_;
public:
    Alias(std::pair<std::string, std::string> map);
    virtual std::string str();
};

class Command : public EpsData {
    std::string data_;
public:
    Command(std::string data);
    virtual std::string str();
};

struct EpsInstruction {
    float x_, y_;
    string cmd_;
    EpsInstruction(float x, float y, string cmd);
};

using EpsDataPtr = std::shared_ptr<EpsData>;
using EpsDatas = std::vector<EpsDataPtr>;

class EpsLoader {
public:
    void load();
    void write();
    void setInFile(std::string name);
    void setOutFile(std::string name);
    EpsDatas readFromFile(std::ifstream& ifs);

private:
    string in_name_;
    string out_name_;
    EpsDatas eps_datas;
};

#endif /* EPS_LOADER */
