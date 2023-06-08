#pragma once

#include <unordered_map>

// Enumeration representing different Pokémon types
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

// Map to associate type strings with enum values
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

// Map to associate enum values with type strings
static std::unordered_map<TYPE, std::string> reverseTypeMap = {
    {TYPE::NORMAL, "Normal"},
    {TYPE::FIRE, "Fire"},
    {TYPE::WATER, "Water"},
    {TYPE::ELECTRIC, "Electric"},
    {TYPE::GRASS, "Grass"},
    {TYPE::ICE, "Ice"},
    {TYPE::FIGHTING, "Fighting"},
    {TYPE::POISON, "Poison"},
    {TYPE::GROUND, "Ground"},
    {TYPE::FLYING, "Flying"},
    {TYPE::PSYCHIC, "Psychic"},
    {TYPE::BUG, "Bug"},
    {TYPE::ROCK, "Rock"},
    {TYPE::GHOST, "Ghost"},
    {TYPE::DRAGON, "Dragon"},
    {TYPE::DARK, "Dark"},
    {TYPE::STEEL, "Steel"},
    {TYPE::FAIRY, "Fairy"}
};
