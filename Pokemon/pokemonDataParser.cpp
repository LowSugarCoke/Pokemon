#include "pokemonDataParser.h"

#include <sstream>
#include <vector>

#include "pokemonEntity.h"
#include "type.h"


std::vector<PokemonEntity> PokemonDataParser::parser(const std::string& kContent) const {
    std::vector<PokemonEntity> pokemonEntities;

    std::stringstream ss(kContent);
    std::string line;

    while (std::getline(ss, line)) {
        // Parse Pokémon name
        std::string name = line;

        // Parse Pokémon types
        std::getline(ss, line);
        std::stringstream typeStream(line);
        int typeCount;
        typeStream >> typeCount;
        std::vector<TYPE> types;
        for (int i = 0; i < typeCount; ++i) {
            std::string typeStr;
            typeStream >> typeStr;
            types.push_back(typeMap[typeStr]);
        }

        // Parse Pokémon stats
        std::getline(ss, line);
        std::stringstream statsStream(line);
        PokemonStats stats;
        statsStream >> stats.hp >> stats.attack >> stats.defense >> stats.specialAttack >> stats.specialDefence >> stats.speed;

        // Create Pokémon entity and add to list
        pokemonEntities.emplace_back(name, types, stats);
    }

    return pokemonEntities;
}
