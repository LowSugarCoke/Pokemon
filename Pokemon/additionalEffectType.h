#pragma once

#include <unordered_map>

enum class ADDITIONAL_EFFECT_TYPE {
    NRML,
    PRL,
    BRN,
    PSN
};

static std::unordered_map<std::string, ADDITIONAL_EFFECT_TYPE> additionalEffectMap = {
    {"NRML", ADDITIONAL_EFFECT_TYPE::NRML},
    {"PRL", ADDITIONAL_EFFECT_TYPE::PRL},
    {"BRN", ADDITIONAL_EFFECT_TYPE::BRN},
    {"PSN", ADDITIONAL_EFFECT_TYPE::PSN}
};
