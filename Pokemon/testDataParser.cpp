#include "testDataParser.h"

#include <vector>
#include <string>
#include <sstream>



std::vector<std::string> TestDataParser::parser(const std::string& kContent) const {
    std::vector<std::string> result;
    std::istringstream iss(kContent);
    std::string token;

    while (std::getline(iss, token, '\n')) {
        result.push_back(token);
    }

    return result;
}
