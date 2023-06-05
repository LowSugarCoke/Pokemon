#pragma once

#include <vector>
#include <string>

class MoveEntity;
class MoveDataParser {
public:
    std::vector<MoveEntity> parser(const std::string& kContent) const;
};
