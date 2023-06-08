#pragma once

#include <unordered_map>

// Enumeration representing additional effect types
enum class ADDITIONAL_EFFECT_TYPE {
    NRM,  // Normal
    PAR,  // Paralyze
    BRN,  // Burn
    PSN   // Poison
};

// Map to associate additional effect type strings with enum values
static std::unordered_map<std::string, ADDITIONAL_EFFECT_TYPE> additionalEffectMap = {
    {"",    ADDITIONAL_EFFECT_TYPE::NRM},  // Default (empty string) maps to Normal
    {"PAR", ADDITIONAL_EFFECT_TYPE::PAR},  // "PAR" maps to Paralyze
    {"BRN", ADDITIONAL_EFFECT_TYPE::BRN},  // "BRN" maps to Burn
    {"PSN", ADDITIONAL_EFFECT_TYPE::PSN}   // "PSN" maps to Poison
};

// Function to convert an additional effect type enum value to a string
static std::string effectTypeToString(ADDITIONAL_EFFECT_TYPE type) {
    for (const auto& pair : additionalEffectMap) {
        if (pair.second == type) {
            return pair.first;  // Return the string associated with the enum value
        }
    }
    return "Unknown";  // Return "Unknown" if the enum value is not found in the map
}
