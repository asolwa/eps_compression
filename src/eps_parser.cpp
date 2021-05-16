#include <regex>
#include "eps_parser.h"
#include "eps_objects.h"

EpsDataPtr EpsParser::create(std::istream& ifs) {
    std::string line;
    std::smatch reg_value;

    std::regex regex_header("^%.+$");
    std::regex regex_alias("^\\/(\\w+) +\\{ (.+) \\} bind def$");
    std::regex regex_ins("^([\\d\\.]+) ([\\d\\.]+) ([\\w])$");
    std::regex regex_basic_ins("^(\\w+)$");

    getline(ifs, line);

    if (regex_match(line, regex_header)) {
        return std::shared_ptr<EpsData>(new Header(line));
    }
    
    else if (regex_search(line, reg_value, regex_alias)) {
        return std::shared_ptr<Alias>(
            new Alias(std::make_pair(reg_value[1], reg_value[2]))
        );
    }
    
    else if (regex_search(line, reg_value, regex_ins)) {
        std::vector<std::string> v;
        v.push_back(reg_value[1]);
        v.push_back(reg_value[2]);
        v.push_back(reg_value[3]);
        return std::shared_ptr<EpsData>(
            new Instruction(v)
        );
    }
    else if (regex_search(line, reg_value, regex_basic_ins)){
        std::vector<std::string> v;
        v.push_back(reg_value[1]);
        return std::shared_ptr<EpsData>(
                new Instruction(v)
        );
    }

    return std::shared_ptr<EpsData>(new Command(line));
}
