#ifndef EPS_LOADER
#define EPS_LOADER

#include <string>
#include <vector>
#include <sstream> 
#include <unordered_map>

using namespace std;

struct EpsInstruction {
    float x_, y_;
    string cmd_;
    EpsInstruction(float x, float y, string cmd);
};

class EpsLoader {
public:
    explicit EpsLoader(string name);
    void load();
    void process_metadata();
    void compress_eps();

private:
    string name_;
    string data;
    stringstream config_;
    stringstream draw_cmd_;

    unordered_map<string, string> aliases;
    vector<EpsInstruction> ins_;
};

#endif /* EPS_LOADER */
