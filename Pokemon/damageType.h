#pragma once

#include <unordered_map>

// Enumeration representing different types of damage
enum class DAMAGE_TYPE
{
    PHYSICAL,  // Physical damage type
    SPECIAL,   // Special damage type
    STATUS     // Status damage type
};

// Map to associate damage type strings with enum values
static std::unordered_map<std::string, DAMAGE_TYPE> damageTypeMap = {
    {"Physical", DAMAGE_TYPE::PHYSICAL},  // "Physical" maps to Physical damage type
    {"Special", DAMAGE_TYPE::SPECIAL},    // "Special" maps to Special damage type
    {"Status", DAMAGE_TYPE::STATUS}       // "Status" maps to Status damage type
};
