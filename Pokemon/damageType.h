#pragma once

#include <unordered_map>

enum class DAMAGE_TYPE
{
    PHYSICAL,
    SPECIAL,
    STATUS
};

static std::unordered_map<std::string, DAMAGE_TYPE> damageTypeMap = {
    {"Physical", DAMAGE_TYPE::PHYSICAL},
    {"Special", DAMAGE_TYPE::SPECIAL},
    {"Status",DAMAGE_TYPE::STATUS}
};
