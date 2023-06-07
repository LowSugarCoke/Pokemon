#pragma once

#include <vector>
#include <string>

class GameEntity;
class GameDataParser {
public:
    std::pair<std::vector<GameEntity>, std::vector<GameEntity>> parser(const std::string& kContent) const;


};
