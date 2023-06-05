#include "moveDataParser.h"

#include "moveEntity.h"

#include <sstream>


std::vector<MoveEntity> MoveDataParser::parser(const std::string& kContent) const {
    std::vector<MoveEntity> moves;
    std::stringstream ss(kContent);
    std::string line;

    while (std::getline(ss, line)) {
        std::stringstream lineStream(line);
        std::string name, type, damageType, additionalEffectType;
        MoveStats moveStats;

        lineStream >> name >> type >> damageType >> moveStats.power >> moveStats.accuracy >> moveStats.powerPoint;

        if (!lineStream.eof()) {
            lineStream >> additionalEffectType;
        }
        else {
            additionalEffectType = "NRML";
        }

        TYPE moveType = typeMap[type];
        DAMAGE_TYPE moveDamageType = damageTypeMap[damageType];
        ADDITIONAL_EFFECT_TYPE moveAdditionalEffectType = additionalEffectMap[additionalEffectType];

        moves.push_back(MoveEntity(name, moveType, moveDamageType, moveStats, moveAdditionalEffectType));
    }

    return moves;
}
