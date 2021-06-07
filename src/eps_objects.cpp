/**
     * @file eps_objects.cpp
     * @brief Plik zawierajacy klasę EpsData
     * @author Piotr Lewandowski
 */
#include <sstream>
#include <utility>

#include "eps_objects.h"

EpsData::EpsData(EpsDataType dataType, std::vector<std::string> tokenValues) : tokenValues_(std::move(tokenValues)),
                                                                               dataType_(dataType) {};

EpsDataType EpsData::getDataType() const { return dataType_; }

std::vector<std::string> EpsData::getTokenValues() const {
    return tokenValues_;
}

