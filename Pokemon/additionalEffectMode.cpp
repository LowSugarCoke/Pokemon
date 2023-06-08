#include "additionalEffectMode.h"

#include <random>
#include <set>
#include <unordered_map>
#include <chrono>

#include "pokemonBo.h"
#include "additionalEffectType.h"
#include "pokemonLogger.h"

// Mapping from additional effect type to corresponding log postfix
static std::unordered_map<ADDITIONAL_EFFECT_TYPE, std::string> effectTypeToPostfix = {
        {ADDITIONAL_EFFECT_TYPE::PSN, " was poisoned!"},
        {ADDITIONAL_EFFECT_TYPE::BRN, " was burned!"},
        {ADDITIONAL_EFFECT_TYPE::PAR, " is paralyzed, so it may be unable to move!" }
};

// Mapping from additional effect type to corresponding damage log postfix
static std::unordered_map<ADDITIONAL_EFFECT_TYPE, std::string> effectDamageToPostfix = {
        {ADDITIONAL_EFFECT_TYPE::PSN, " is hurt by its poisoning!"},
        {ADDITIONAL_EFFECT_TYPE::BRN, " is hurt by its burn!"}
};

// Private implementation of AdditionalEffectMode
class AdditionalEffectModePrivate {
public:
    AdditionalEffectModePrivate();

    void additionalEffectLog(std::shared_ptr<PokemonBo> pPokemonBo, const MoveBo& kMoveBo);
    void additionalEffectDamageLog(std::shared_ptr<PokemonBo> pPokemonBo);
    int additionalDamageCount(std::shared_ptr<PokemonBo> pPokemonBo) const;

    PokemonLogger& mLogger;  // Reference to the PokemonLogger instance
    bool mIsTest;  // Flag indicating if the mode is in test mode
};

AdditionalEffectModePrivate::AdditionalEffectModePrivate()
    : mLogger(PokemonLogger::getInstance())
    , mIsTest(false)
{}

int AdditionalEffectModePrivate::additionalDamageCount(std::shared_ptr<PokemonBo> pPokemonBo) const {
    return pPokemonBo->getMaxHp() / 16;  // Calculate additional damage as 1/16th of maximum HP
}

void AdditionalEffectModePrivate::additionalEffectLog(std::shared_ptr<PokemonBo> pPokemonBo, const MoveBo& kMoveBo) {
    auto name = pPokemonBo->getName();
    std::string postfix = "";

    postfix = effectTypeToPostfix[kMoveBo.additionalEffectType];  // Get the corresponding postfix for the additional effect type
    if (pPokemonBo->isMyPokemon()) {
        mLogger.log(name + postfix);  // Log the effect for the player's Pokemon
    }
    else {
        mLogger.log("The opposing " + name + postfix);  // Log the effect for the opposing Pokemon
    }
}

void AdditionalEffectModePrivate::additionalEffectDamageLog(std::shared_ptr<PokemonBo> pPokemonBo) {
    std::string postfix = "";
    if (pPokemonBo->getPokemonAdditionalEffectType().empty()) {
        return;  // If there are no additional effects, return
    }

    auto pokemonAdditionalEffect = pPokemonBo->getPokemonAdditionalEffectType();
    for (auto effect : pokemonAdditionalEffect) {
        if (!effectDamageToPostfix.count(effect)) {
            continue;  // Skip if there is no corresponding damage postfix for the effect type
        }

        postfix = effectDamageToPostfix[effect];  // Get the corresponding damage postfix for the effect type
        auto name = pPokemonBo->getName();
        if (pPokemonBo->isMyPokemon()) {
            mLogger.log(name + postfix);  // Log the damage for the player's Pokemon
        }
        else {
            mLogger.log("The opposing " + name + postfix);  // Log the damage for the opposing Pokemon
        }
    }
}

// Public methods of AdditionalEffectMode

AdditionalEffectMode::AdditionalEffectMode()
    :mpPrivate(std::make_unique<AdditionalEffectModePrivate>())
{}

AdditionalEffectMode::~AdditionalEffectMode() {}

bool AdditionalEffectMode::unableToMove(std::shared_ptr<PokemonBo> pPokemonBo)const {
    if (pPokemonBo->getPokemonAdditionalEffectType().count(ADDITIONAL_EFFECT_TYPE::PAR)) {
        if (mpPrivate->mIsTest) {
            return true;  // In test mode, always return true to simulate being unable to move
        }

        // Create a random number generator with a seed based on the current time
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        // Create a distribution that will generate numbers between 1 and 4
        std::uniform_int_distribution<int> distribution(1, 4);
        // Generate a random number
        int randomNumber = distribution(generator);
        // If the random number is 1 (which has a 1 in 4 chance of happening), return true
        if (randomNumber == 1) {
            return true;  // Return true to simulate being unable to move
        }
    }
    return false;  // Return false if the Pokemon can move
}

void AdditionalEffectMode::additionalDamageAfterBattle(std::shared_ptr<PokemonBo> pPokemonBo) {
    if (pPokemonBo->getPokemonAdditionalEffectType().count(ADDITIONAL_EFFECT_TYPE::BRN)) {
        int damage = mpPrivate->additionalDamageCount(pPokemonBo);
        pPokemonBo->minusHp(damage);  // Reduce the Pokemon's HP by the additional damage
    }

    if (pPokemonBo->getPokemonAdditionalEffectType().count(ADDITIONAL_EFFECT_TYPE::PSN)) {
        int damage = mpPrivate->additionalDamageCount(pPokemonBo);
        pPokemonBo->minusHp(damage);  // Reduce the Pokemon's HP by the additional damage
    }

    mpPrivate->additionalEffectDamageLog(pPokemonBo);  // Log the additional damage effects
}

void AdditionalEffectMode::addIfMoveHasAdditionalEffect(std::shared_ptr<PokemonBo> pPokemonBo, MoveBo moveBo) {
    auto additionalEffectType = moveBo.additionalEffectType;
    if (additionalEffectType != ADDITIONAL_EFFECT_TYPE::NRM) {
        mpPrivate->additionalEffectLog(pPokemonBo, moveBo);  // Log the additional effect
        pPokemonBo->setPokemonAdditionalEffectType(additionalEffectType);  // Set the additional effect type for the Pokemon
        if (additionalEffectType == ADDITIONAL_EFFECT_TYPE::PAR) {
            pPokemonBo->reduceHalfSpeed();  // Reduce the Pokemon's speed by half if it is paralyzed
        }
    }
}

void AdditionalEffectMode::setTest() {
    mpPrivate->mIsTest = true;  // Enable test mode
}
