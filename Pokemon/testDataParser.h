/**************************************************************
 * File : testDataParser.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: This header file contains the declaration of the TestDataParser class, which is responsible for parsing a given string of content and returning a vector of strings.
 *************************************************************/

#pragma once

#include <vector>
#include <string>

class TestDataParser {
public:
    /**
     * @brief Parses the provided content and returns a vector of strings.
     *
     * @param kContent The string content to be parsed.
     * @return std::vector<std::string> A vector of strings.
     */
    std::vector<std::string> parser(const std::string& kContent) const;
};
