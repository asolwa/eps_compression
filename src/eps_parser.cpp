/**
 * \file EpsParser.cpp
 * \brief Klasa będąca reprezentacją parsera
 */

#include <iostream>
#include <regex>
#include "eps_parser.h"

EpsParser::EpsParser() = default;

EpsDatas EpsParser::parse(std::vector<std::vector<std::string>> &tokenData) {
    std::regex regex_header("^%.*$");
    std::regex regex_alias_beginning("^\\/\\w+$");
    std::vector<std::string> currentTokens;
    eps_datas_.clear();

    for (auto &tokens:tokenData) {
        currentTokens.insert(currentTokens.end(), tokens.begin(), tokens.end());
        if (!currentTokens.empty()) {
            if (regex_match(currentTokens[0], regex_header)) {
                EpsDataPtr header(new EpsData(EpsDataType::header, currentTokens));
                eps_datas_.push_back(std::move(header));
                currentTokens.clear();
            } else if (regex_match(currentTokens[0], regex_alias_beginning) && (tokens.size() == 1 || currentTokens[1] == "{")) {
                int size = currentTokens.size();
                if (size >= 5) {
                    if (currentTokens[1] == "{" && currentTokens[size - 2] == "}" && currentTokens[size - 1] == "def") {
                        EpsDataPtr alias(new EpsData(EpsDataType::alias, currentTokens));
                        eps_datas_.push_back(std::move(alias));
                        currentTokens.clear();
                    } else if (size >= 6 && currentTokens[1] == "{" && currentTokens[size - 3] == "}" &&
                               currentTokens[size - 2] == "bind" && currentTokens[size - 1] == "def") {
                        EpsDataPtr alias(new EpsData(EpsDataType::alias, currentTokens));
                        eps_datas_.push_back(std::move(alias));
                        currentTokens.clear();
                    }
                }
            } else {
                EpsDataPtr instruction(new EpsData(EpsDataType::instruction, currentTokens));
                eps_datas_.push_back(std::move(instruction));
                currentTokens.clear();
            }
        }
    }
    return eps_datas_;
}
