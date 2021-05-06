#include <regex>
#include "eps_parser.h"
#include "eps_objects.h"

EpsDataPtr EpsParser::create(std::istream& ifs) {
    std::string line;
    std::smatch reg_value;

    std::regex regex_header("^%.+$");
    std::regex regex_alias("^\\/(\\w+) +\\{ (\\w+) \\} bind def$");
    std::regex regex_ins("([\\d\\.]+) ([\\d\\.]+) ([\\w])");

    getline(ifs, line);

    if (regex_match(line, regex_header)) {
        return std::shared_ptr<EpsData>(new Header(line));
    }
    
    if (regex_search(line, reg_value, regex_alias)) {
        return std::shared_ptr<Alias>(
            new Alias(std::make_pair(reg_value[1], reg_value[2]))
        );
    }
    
    if (regex_search(line, reg_value, regex_ins)) {
        float x = stof(reg_value[1]);
        float y = stof(reg_value[2]);
        std::string cmd = reg_value[3].str();
        return std::shared_ptr<EpsData>(
            new Instruction(x, y, cmd)
        );
    }

    return std::shared_ptr<EpsData>(new Command(line));
}
