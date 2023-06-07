#include "additionalEffectMode.h"

#include <random>
#include <set>
#include <unordered_map>

#include "pokemonBo.h"
#include "additionalEffectType.h"
#include "pokemonLogger.h"

static std::unordered_map<ADDITIONAL_EFFECT_TYPE, std::string> effectTypeToPostfix = {
        {ADDITIONAL_EFFECT_TYPE::PSN, " was poisoned!"},
        {ADDITIONAL_EFFECT_TYPE::BRN, " was burned!"},
        {ADDITIONAL_EFFECT_TYPE::PAR, " is paralyzed, so it may be unable to move!" }
};

static std::unordered_map<ADDITIONAL_EFFECT_TYPE, std::string> effectDamageToPostfix = {
        {ADDITIONAL_EFFECT_TYPE::PSN, " is hurt by its poisoning!"},
        {ADDITIONAL_EFFECT_TYPE::BRN, " is hurt by its burn!"},
};


class AdditionalEffectModePrivate {
public:
    AdditionalEffectModePrivate();

    void additionalEffectLog(std::shared_ptr<PokemonBo> pPokemonBo, const MoveBo& kMoveBo);
    void additionalEffectDamageLog(std::shared_ptr<PokemonBo> pPokemonBo);
    int additionalDamageCount(std::shared_ptr<PokemonBo> pPokemonBo) const;

    PokemonLogger& mLogger;
};

AdditionalEffectModePrivate::AdditionalEffectModePrivate()
    : mLogger(PokemonLogger::getInstance())
{}

int AdditionalEffectModePrivate::additionalDamageCount(std::shared_ptr<PokemonBo> pPokemonBo) const {
    return pPokemonBo->getMaxHp() / 16;
}

void AdditionalEffectModePrivate::additionalEffectLog(std::shared_ptr<PokemonBo> pPokemonBo, const MoveBo& kMoveBo) {
    auto name = pPokemonBo->getName();
    std::string postfix = "";

    postfix = effectTypeToPostfix[kMoveBo.additionalEffectType];
    if (pPokemonBo->isMyPokemon()) {
        mLogger.log(name + postfix);
    }
    else {
        if (kMoveBo.additionalEffectType == ADDITIONAL_EFFECT_TYPE::PSN) {
            mLogger.log("The opposing " + name + postfix);
        }
    }
}

void AdditionalEffectModePrivate::additionalEffectDamageLog(std::shared_ptr<PokemonBo> pPokemonBo) {
    std::string postfix = "";
    if (pPokemonBo->getPokemonAdditionalEffectType().empty()) {
        return;
    }

    auto pokemonAdditionalEffect = pPokemonBo->getPokemonAdditionalEffectType();
    for (auto effect : pokemonAdditionalEffect) {
        if (!effectDamageToPostfix.count(effect)) {
            continue;
        }

        postfix = effectDamageToPostfix[effect];
        auto name = pPokemonBo->getName();
        mLogger.log(name + postfix);
    }
}

AdditionalEffectMode::AdditionalEffectMode()
    :mpPrivate(std::make_unique<AdditionalEffectModePrivate>())
{
}

AdditionalEffectMode::~AdditionalEffectMode() {}




bool AdditionalEffectMode::unableToMove(std::shared_ptr<PokemonBo> pPokemonBo)const {

    if (pPokemonBo->getPokemonAdditionalEffectType().count(ADDITIONAL_EFFECT_TYPE::PAR)) {
        // create a random number generator
        std::default_random_engine generator;
        // create a distribution that will generate numbers between 1 and 4
        std::uniform_int_distribution<int> distribution(1, 4);
        // generate a random number
        int randomNumber = distribution(generator);
        // if the random number is 1 (which has a 1 in 4 chance of happening), return true
        if (randomNumber == 1) {
            return true;
        }
    }
    return false;
}

void AdditionalEffectMode::additionalDamageAfterBattle(std::shared_ptr<PokemonBo> pPokemonBo) {
    if (pPokemonBo->getPokemonAdditionalEffectType().count(ADDITIONAL_EFFECT_TYPE::BRN)) {
        int damage = mpPrivate->additionalDamageCount(pPokemonBo);
        pPokemonBo->minusHp(damage);
    }

    if (pPokemonBo->getPokemonAdditionalEffectType().count(ADDITIONAL_EFFECT_TYPE::PSN)) {
        int damage = mpPrivate->additionalDamageCount(pPokemonBo);
        pPokemonBo->minusHp(damage);
    }

    mpPrivate->additionalEffectDamageLog(pPokemonBo);
}


void AdditionalEffectMode::addIfMoveHasAdditionalEffect(std::shared_ptr<PokemonBo> pPokemonBo, MoveBo moveBo) {
    auto additionalEffectType = moveBo.additionalEffectType;
    if (additionalEffectType != ADDITIONAL_EFFECT_TYPE::NRM) {
        if (pPokemonBo->getPokemonAdditionalEffectType().count(additionalEffectType)) {
            return;
        }
        mpPrivate->additionalEffectLog(pPokemonBo, moveBo);
        pPokemonBo->setPokemonAdditionalEffectType(additionalEffectType);
        if (additionalEffectType == ADDITIONAL_EFFECT_TYPE::PAR) {
            pPokemonBo->reduceHalfSpeed();
        }
    }
}
