#include "pokemonMode.h"

#include <random>

#include "pokemonBo.h"
#include "damageSystem.h"
#include "additionalEffectMode.h"

class PokemonModePrivate {
public:
    PokemonModePrivate(std::shared_ptr<DamageSystem> pDamageSystem, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode);

    void damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const std::string& kMoveName);
    MoveBo getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo);

    std::shared_ptr<PokemonBo> mpPokemonBo;
    std::shared_ptr<PokemonBo> mpOppositingPokemonBo;
    std::shared_ptr<DamageSystem> mpDamageSystem;
    std::shared_ptr<AdditionalEffectMode> mpAdditionalEffectMode;
};

PokemonModePrivate::PokemonModePrivate(std::shared_ptr<DamageSystem> pDamageSystem, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode)
    :mpDamageSystem(pDamageSystem)
    , mpAdditionalEffectMode(pAdditionalEffectMode)
{

}

void PokemonModePrivate::damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const std::string& kMoveName) {
    if (mpDamageSystem->isMissing(pAPokemonBo, pBPokemonBo, kMoveName)) {
        return;
    }

    if (mpAdditionalEffectMode->unableToMove(pAPokemonBo)) {
        return;
    }
    int damage = mpDamageSystem->damageCalculate(pAPokemonBo, pBPokemonBo, kMoveName);
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


PokemonMode::PokemonMode(std::shared_ptr<DamageSystem> pDamageSystem, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode)
    :mpPrivate(std::make_unique<PokemonModePrivate>(pDamageSystem, pAdditionalEffectMode))
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
