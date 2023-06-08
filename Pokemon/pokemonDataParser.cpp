#include "pokemonDataParser.h"

#include <sstream>
#include <vector>

#include "pokemonEntity.h"
#include "type.h"

// Function to parse Pokémon data and return a vector of PokemonEntity objects
std::vector<PokemonEntity> PokemonDataParser::parser(const std::string& kContent) const {
    // Vector to store PokemonEntity objects
    std::vector<PokemonEntity> pokemonEntities;

    // Create a string stream to read the content
    std::stringstream ss(kContent);

    // String to store each line of the content
    std::string line;

    // Read each line from the string stream
    while (std::getline(ss, line)) {
        // Parse the Pokémon name from the line
        std::string name = line;

        // Get the line containing the Pokémon types
        std::getline(ss, line);

        // Create a string stream for the Pokémon types line
        std::stringstream typeStream(line);

        // Integer to store the number of types for the Pokémon
        int typeCount;

        // Extract the number of types from the typeStream
        typeStream >> typeCount;

        // Vector to store the Pokémon types
        std::vector<TYPE> types;

        // Iterate through each type and add it to the types vector
        for (int i = 0; i < typeCount; ++i) {
            std::string typeStr;
            typeStream >> typeStr;
            types.push_back(typeMap[typeStr]);
        }

        // Get the line containing the Pokémon stats
        std::getline(ss, line);

        // Create a string stream for the Pokémon stats line
        std::stringstream statsStream(line);

        // PokemonStats struct to store the Pokémon's stats
        PokemonStats stats;

        // Extract the Pokémon's stats from the statsStream
        statsStream >> stats.hp >> stats.attack >> stats.defense >> stats.specialAttack >> stats.specialDefence >> stats.speed;

        // Create a Pokémon entity with the parsed data and add it to the pokemonEntities vector
        pokemonEntities.emplace_back(name, types, stats);
    }

    // Return the vector of PokemonEntity objects
    return pokemonEntities;
}
