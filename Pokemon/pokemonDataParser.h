/**************************************************************
 * File : pokemonDataParser.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: This header file contains the declaration of the PokemonDataParser class, which is responsible for parsing a given string of content and returning a vector of PokemonEntity objects.
 *************************************************************/

#pragma once

#include <vector>
#include <string>

class PokemonEntity;
class PokemonDataParser {
public:
    /**
     * @brief Parses the provided content and returns a vector of PokemonEntity objects.
     *
     * @param kContent The string content to be parsed.
     * @return std::vector<PokemonEntity> A vector of PokemonEntity objects.
     */
    std::vector<PokemonEntity> parser(const std::string& kContent) const;
};
