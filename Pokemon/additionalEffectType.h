#pragma once

#include <unordered_map>

enum class ADDITIONAL_EFFECT_TYPE {
    NRM,
    PAR,
    BRN,
    PSN
};

static std::unordered_map<std::string, ADDITIONAL_EFFECT_TYPE> additionalEffectMap = {
    {"",    ADDITIONAL_EFFECT_TYPE::NRM},
    {"PAR", ADDITIONAL_EFFECT_TYPE::PAR},
    {"BRN", ADDITIONAL_EFFECT_TYPE::BRN},
    {"PSN", ADDITIONAL_EFFECT_TYPE::PSN}
};

static std::string effectTypeToString(ADDITIONAL_EFFECT_TYPE type) {
    for (const auto& pair : additionalEffectMap) {
        if (pair.second == type) {
            return pair.first;
        }
    }
    return "Unknown";
}
