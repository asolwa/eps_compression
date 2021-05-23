#ifndef EPS_OBJECTS
#define EPS_OBJECTS

#include <string>
#include <vector>
#include <memory>

enum class EpsDataType {
    header, alias, instruction
};

class EpsData {
public:
    EpsData(EpsDataType dataType, std::vector<std::string> tokenValues);

    EpsDataType getDataType() const;

    std::vector<std::string> getTokenValues() const;

private:
    std::vector<std::string> tokenValues_;
    EpsDataType dataType_;
};

#endif /* EPS_OBJECTS */
