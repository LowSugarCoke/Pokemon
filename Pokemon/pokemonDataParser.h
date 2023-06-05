#pragma once

#include <vector>
#include <string>

class PokemonEntity;
class PokemonDataParser {
public:
    std::vector<PokemonEntity> parser(const std::string& kContent) const;
};
