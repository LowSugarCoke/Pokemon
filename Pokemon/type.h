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
        {"Normal", TYPE::NORMAL},
        {"Fire", TYPE::FIRE},
        {"Water", TYPE::WATER},
        {"Electric", TYPE::ELECTRIC},
        {"Grass", TYPE::GRASS},
        {"Ice", TYPE::ICE},
        {"Fighting", TYPE::FIGHTING},
        {"Poison", TYPE::POISON},
        {"Ground", TYPE::GROUND},
        {"Flying", TYPE::FLYING},
        {"Psychic", TYPE::PSYCHIC},
        {"Bug", TYPE::BUG},
        {"Rock", TYPE::ROCK},
        {"Ghost", TYPE::GHOST},
        {"Dragon", TYPE::DRAGON},
        {"Dark", TYPE::DARK},
        {"Steel", TYPE::STEEL},
        {"Fairy", TYPE::FAIRY}
};
