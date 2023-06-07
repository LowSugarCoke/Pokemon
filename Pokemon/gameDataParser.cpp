#include "GameDataParser.h"

#include <sstream>
#include <vector>


#include "GameEntity.h"


std::pair<std::vector<GameEntity>, std::vector<GameEntity>> GameDataParser::parser(const std::string& kContent) const {

    std::vector<GameEntity> myGameEntities;
    std::vector<GameEntity> oppositingGameEntities;


    std::stringstream ss(kContent);
    std::string line;
    for (int i = 0; i < 2; i++) {
        // Parse number of entities
        std::getline(ss, line);
        int numEntities = std::stoi(line);

        // Parse each entity
        for (int j = 0; j < numEntities; j++) {
            GameEntity entity;
            std::getline(ss, line);
            std::stringstream entityStream(line);
            std::string name;
            int numMoves;
            entityStream >> name >> numMoves;
            entity.setName(name);

            std::getline(ss, line);
            std::stringstream movesStream(line);
            std::vector<std::string> moves;
            for (int k = 0; k < numMoves; k++) {
                std::string move;
                movesStream >> move;
                entity.addMove(move);
            }

            if (i == 0) {
                // Create GameEntity and add to list
                myGameEntities.emplace_back(entity);
            }
            else {
                oppositingGameEntities.emplace_back(entity);
            }
        }
    }





    return { myGameEntities ,oppositingGameEntities };
}
