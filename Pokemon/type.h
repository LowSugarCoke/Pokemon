#pragma once

#include <unordered_map>

enum class TYPE {
    NORMAL = 0,
    FIRE,
    WATER,
    ELECTRIC,
    GRASS,
    ICE,
    FIGHTING,
    POISON,
    GROUND,
    FLYING,
    PSYCHIC,
    BUG,
    ROCK,
    GHOST,
    DRAGON,
    DARK,
    STEEL,
    FAIRY
};

static std::unordered_map<std::string, TYPE> typeMap = {
        {"NORMAL", TYPE::NORMAL},
        {"FIRE", TYPE::FIRE},
        {"WATER", TYPE::WATER},
        {"ELECTRIC", TYPE::ELECTRIC},
        {"GRASS", TYPE::GRASS},
        {"ICE", TYPE::ICE},
        {"FIGHTING", TYPE::FIGHTING},
        {"POISON", TYPE::POISON},
        {"GROUND", TYPE::GROUND},
        {"FLYING", TYPE::FLYING},
        {"PSYCHIC", TYPE::PSYCHIC},
        {"BUG", TYPE::BUG},
        {"ROCK", TYPE::ROCK},
        {"GHOST", TYPE::GHOST},
        {"DRAGON", TYPE::DRAGON},
        {"DARK", TYPE::DARK},
        {"STEEL", TYPE::STEEL},
        {"FAIRY", TYPE::FAIRY}
};
