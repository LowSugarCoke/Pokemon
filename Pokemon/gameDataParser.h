#pragma once

#include <vector>
#include <string>

class GameEntity;
class GameDataParser {
public:
    std::vector<GameEntity> parser(const std::string& kContent) const;
};
