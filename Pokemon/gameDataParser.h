/**************************************************************
 * File: gameDataParser.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor: Jack Lee
 * Update Date: 2023-06-08
 * Description: Header file for the GameDataParser class, which is responsible for parsing game data.
 *************************************************************/

#pragma once

#include <vector>
#include <string>

class GameEntity;
class GameDataParser {
public:

    /**
     * Intent: Parses the provided content and extracts game entities.
     * Pre: The content should be a valid string representing game data.
     * Post: Returns a pair of vectors containing parsed game entities, where the first vector contains
     *       one type of entities and the second vector contains another type of entities.
     * \param kContent The string containing the game data to be parsed.
     * \return A pair of vectors containing parsed game entities.
     */
    std::pair<std::vector<GameEntity>, std::vector<GameEntity>> parser(const std::string& kContent) const;

};
