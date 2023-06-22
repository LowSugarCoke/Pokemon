/**************************************************************
 * File : moveDataParser.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: This header file contains the declaration of the MoveDataParser class, which is responsible for parsing a given string of content and returning a vector of MoveEntity objects.
 *************************************************************/

#pragma once

#include <vector>
#include <string>

class MoveEntity;

class MoveDataParser {
public:
    /**
     * @brief Parses the provided content and returns a vector of MoveEntity objects.
     *
     * @param kContent The string content to be parsed.
     * @return std::vector<MoveEntity> A vector of MoveEntity objects.
     */
    std::vector<MoveEntity> parser(const std::string& kContent) const;
};
