#include "moveDataParser.h"

#include "moveEntity.h"

#include <sstream>

// Function to parse move data and return a vector of MoveEntity objects
std::vector<MoveEntity> MoveDataParser::parser(const std::string& kContent) const {
    // Vector to store MoveEntity objects
    std::vector<MoveEntity> moves;

    // Create a string stream to read the content
    std::stringstream ss(kContent);

    // String to store each line of the content
    std::string line;

    // Read each line from the string stream
    while (std::getline(ss, line)) {
        // Create a string stream for the current line
        std::stringstream lineStream(line);

        // Variables to store different attributes of the move
        std::string name, type, damageType, additionalEffectType;
        MoveStats moveStats;

        // Extract the move attributes from the line
        lineStream >> name >> type >> damageType >> moveStats.power >> moveStats.accuracy >> moveStats.powerPoint;

        // Check if there is an additional effect type specified
        if (!lineStream.eof()) {
            lineStream >> additionalEffectType;
        }
        else {
            // Set default additional effect type if not specified
            additionalEffectType = "NRML";
        }

        // Map the move type, damage type, and additional effect type to their respective enum values
        TYPE moveType = typeMap[type];
        DAMAGE_TYPE moveDamageType = damageTypeMap[damageType];
        ADDITIONAL_EFFECT_TYPE moveAdditionalEffectType = additionalEffectMap[additionalEffectType];

        // Create a MoveEntity object with the extracted attributes and add it to the vector
        moves.push_back(MoveEntity(name, moveType, moveDamageType, moveStats, moveAdditionalEffectType));
    }

    // Return the vector of MoveEntity objects
    return moves;
}
