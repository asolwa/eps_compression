#include "parser.h"
#include "eps_objects.h"
#include <regex>

EpsDataPtr ParserFactory::create(std::istream& ifs) {
    std::string line;
    std::smatch reg_value;

    std::regex regex_header("^%.+$");
    std::regex regex_alias("^\\/(\\w+) +\\{ (\\w+) \\} bind def$");
    std::regex regex_ins("([\\d\\.]+) ([\\d\\.]+) ([\\w])");

    getline(ifs, line);

    if (regex_match(line, regex_header)) {
        // zapisz bo to metadane eps/ konfiguracja
        return std::shared_ptr<EpsData>(new Header(line));
    } else if (regex_search(line, reg_value, regex_alias)) {
        // proces aliasy
        return std::shared_ptr<Alias>(
            new Alias(std::make_pair(reg_value[1], reg_value[2]))
        );
    } else if (regex_search(line, reg_value, regex_ins)) {
        //process liczby
        float x = stof(reg_value[1]);
        float y = stof(reg_value[2]);
        std::string cmd = reg_value[3].str();
        return std::shared_ptr<EpsData>(
            new Instruction(x, y, cmd)
        );
    }
    else {
        return std::shared_ptr<EpsData>(new Command(line));
    }
}
