#include "GameDataParser.h"

#include <sstream>
#include <vector>

#include "GameEntity.h"

// Function to parse the game data and return two vectors of GameEntity objects
std::pair<std::vector<GameEntity>, std::vector<GameEntity>> GameDataParser::parser(const std::string& kContent) const {

    // Vector to store GameEntity objects for the player's entities
    std::vector<GameEntity> myGameEntities;

    // Vector to store GameEntity objects for the opposing entities
    std::vector<GameEntity> opposingGameEntities;


    // Create a string stream to read the content
    std::stringstream ss(kContent);

    // String to store each line of the content
    std::string line;

    // Iterate twice to parse data for both player's entities and opposing entities
    for (int i = 0; i < 2; i++) {
        // Parse the number of entities
        std::getline(ss, line);
        int numEntities = std::stoi(line);

        // Parse each entity
        for (int j = 0; j < numEntities; j++) {
            // Create a GameEntity object
            GameEntity entity;

            // Get the line containing the entity's name and the number of moves
            std::getline(ss, line);

            // Create a string stream to parse the entity's data
            std::stringstream entityStream(line);

            // String to store the entity's name
            std::string name;

            // Integer to store the number of moves for the entity
            int numMoves;

            // Extract the name and number of moves from the entityStream
            entityStream >> name >> numMoves;

            // Set the name for the entity
            entity.setName(name);

            // Get the line containing the entity's moves
            std::getline(ss, line);

            // Create a string stream to parse the entity's moves
            std::stringstream movesStream(line);

            // Vector to store the entity's moves
            std::vector<std::string> moves;

            // Iterate through each move and add it to the moves vector
            for (int k = 0; k < numMoves; k++) {
                std::string move;
                movesStream >> move;
                entity.addMove(move);
            }

            // Check if the entity belongs to the player or the opposing side
            if (i == 0) {
                // Add the GameEntity object to the player's entity vector
                myGameEntities.emplace_back(entity);
            }
            else {
                // Add the GameEntity object to the opposing entity vector
                opposingGameEntities.emplace_back(entity);
            }
        }
    }

    // Return a pair of vectors containing the player's entities and the opposing entities
    return { myGameEntities ,opposingGameEntities };
}
