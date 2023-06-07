#include "pokemonMode.h"

#include <random>

#include "pokemonBo.h"
#include "damageMode.h"
#include "additionalEffectMode.h"

class PokemonModePrivate {
public:
    PokemonModePrivate(std::shared_ptr<DamageMode> pDamageMode, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode);

    void damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const std::string& kMoveName);
    MoveBo getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo);

    std::shared_ptr<PokemonBo> mpPokemonBo;
    std::shared_ptr<PokemonBo> mpOppositingPokemonBo;
    std::shared_ptr<DamageMode> mpDamageMode;
    std::shared_ptr<AdditionalEffectMode> mpAdditionalEffectMode;
};

PokemonModePrivate::PokemonModePrivate(std::shared_ptr<DamageMode> pDamageMode, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode)
    :mpDamageMode(pDamageMode)
    , mpAdditionalEffectMode(pAdditionalEffectMode)
{

}

void PokemonModePrivate::damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const std::string& kMoveName) {
    if (mpDamageMode->isMissing(pAPokemonBo, pBPokemonBo, kMoveName)) {
        return;
    }

    if (mpAdditionalEffectMode->unableToMove(pAPokemonBo)) {
        return;
    }
    int damage = mpDamageMode->damageCalculate(pAPokemonBo, pBPokemonBo, kMoveName);
    pBPokemonBo->minusHp(damage);

    MoveBo moveBo = pAPokemonBo->findMoveBoByName(kMoveName);
    mpAdditionalEffectMode->addIfMoveHasAdditionalEffect(pBPokemonBo, moveBo);
}


MoveBo PokemonModePrivate::getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo) {
    auto moveBos = pOppositingPokemonBo->getMoveBos();

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, moveBos.size());

    int randomNumber = distrib(gen);

    return moveBos[randomNumber - 1];
}


PokemonMode::PokemonMode(std::shared_ptr<DamageMode> pDamageMode, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode)
    :mpPrivate(std::make_unique<PokemonModePrivate>(pDamageMode, pAdditionalEffectMode))
{

}

PokemonMode::PokemonMode(const PokemonMode& kPokemonMode)
    : mpPrivate(std::make_unique<PokemonModePrivate>(*kPokemonMode.mpPrivate))
{

}

PokemonMode::~PokemonMode() {
}

void PokemonMode::setMyPokemon(std::shared_ptr<PokemonBo> pMyPokemon) {
    mpPrivate->mpPokemonBo = pMyPokemon;
}
void PokemonMode::setOppositingPokemon(std::shared_ptr<PokemonBo> pOppositingPokemon) {
    mpPrivate->mpOppositingPokemonBo = pOppositingPokemon;
}

void PokemonMode::nextRound(const std::string& kMoveName) {
    auto oppositingMoveName = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo).name;
    if (mpPrivate->mpPokemonBo->getPokemonStats().speed > mpPrivate->mpOppositingPokemonBo->getPokemonStats().speed) {
        mpPrivate->damage(mpPrivate->mpPokemonBo, mpPrivate->mpOppositingPokemonBo, kMoveName);
        mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMoveName);
    }
    else {
        mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMoveName);
        mpPrivate->damage(mpPrivate->mpPokemonBo, mpPrivate->mpOppositingPokemonBo, kMoveName);
    }
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo);
}


void PokemonMode::nextRoundWithoutAttack() {
    auto oppositingMoveName = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo).name;
    mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMoveName);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo);
}
