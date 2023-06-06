#include "additionalEffectMode.h"

#include <random>
#include <set>

#include "pokemonBo.h"
#include "additionalEffectType.h"

class AdditionalEffectModePrivate {
public:
    int additionalDamageCount(std::shared_ptr<PokemonBo> pPokemonBo) const;
};

int AdditionalEffectModePrivate::additionalDamageCount(std::shared_ptr<PokemonBo> pPokemonBo) const {
    return pPokemonBo->getMaxHp() / 16;
}

AdditionalEffectMode::AdditionalEffectMode()
    :mpPrivate(std::make_unique<AdditionalEffectModePrivate>())
{
}

AdditionalEffectMode::~AdditionalEffectMode() {}




bool AdditionalEffectMode::unableToMove(std::shared_ptr<PokemonBo> pPokemonBo)const {

    if (pPokemonBo->getPokemonAdditionalEffectType().count(ADDITIONAL_EFFECT_TYPE::PRL)) {
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
}


void AdditionalEffectMode::addIfMoveHasAdditionalEffect(std::shared_ptr<PokemonBo> pPokemonBo, MoveBo moveBo) {
    if (moveBo.additionalEffectType != ADDITIONAL_EFFECT_TYPE::NRM) {
        pPokemonBo->setPokemonAdditionalEffectType(moveBo.additionalEffectType);
    }
}
