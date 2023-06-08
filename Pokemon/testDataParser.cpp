#include "testDataParser.h"

#include <vector>
#include <string>
#include <sstream>

// Function to parse test data and return a vector of strings
std::vector<std::string> TestDataParser::parser(const std::string& kContent) const {
    // Vector to store the parsed strings
    std::vector<std::string> result;

    // Create an input string stream to read the content
    std::istringstream iss(kContent);

    // String to store each token
    std::string token;

    // Read each line from the input string stream and store it in the result vector
    while (std::getline(iss, token, '\n')) {
        result.push_back(token);
    }

    // Return the vector of parsed strings
    return result;
}
