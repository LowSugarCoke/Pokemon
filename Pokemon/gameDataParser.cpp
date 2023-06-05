#include "GameDataParser.h"

#include <sstream>
#include <vector>

#include "GameEntity.h"


std::vector<GameEntity> GameDataParser::parser(const std::string& kContent) const {
    std::vector<GameEntity> gameEntities;

    std::stringstream ss(kContent);
    std::string line;

    // Parse number of entities
    std::getline(ss, line);
    int numEntities = std::stoi(line);

    // Parse each entity
    for (int i = 0; i < numEntities; i++) {
        std::getline(ss, line);
        std::stringstream entityStream(line);
        std::string name;
        int numMoves;
        entityStream >> name >> numMoves;

        std::getline(ss, line);
        std::stringstream movesStream(line);
        std::vector<std::string> moves;
        for (int j = 0; j < numMoves; j++) {
            std::string move;
            movesStream >> move;
            moves.push_back(move);
        }

        // Create GameEntity and add to list
        gameEntities.emplace_back(name, moves);
    }

    return gameEntities;
}
