#include "pokemonMode.h"

#include <random>

#include "pokemonBo.h"
#include "damageSystem.h"

class PokemonModePrivate {
public:
    PokemonModePrivate(std::shared_ptr<DamageSystem> pDamageSystem);

    void damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const std::string& kMoveName);
    void statusDamage(std::shared_ptr<PokemonBo> pPokemonBo);
    MoveBo getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo);

    std::shared_ptr<PokemonBo> mpPokemonBo;
    std::shared_ptr<PokemonBo> mpOppositingPokemonBo;
    std::shared_ptr<DamageSystem> mpDamageSystem;
};

PokemonModePrivate::PokemonModePrivate(std::shared_ptr<DamageSystem> pDamageSystem)
    :mpDamageSystem(pDamageSystem)
{

}

void PokemonModePrivate::damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const std::string& kMoveName) {
    if (mpDamageSystem->isMiss(pAPokemonBo, pBPokemonBo, kMoveName)) {
        return;
    }
    int damage = mpDamageSystem->damageCalculate(pAPokemonBo, pBPokemonBo, kMoveName);
    pBPokemonBo->minusHp(damage);
}

void PokemonModePrivate::statusDamage(std::shared_ptr<PokemonBo> pPokemonBo) {
    int damage = mpDamageSystem->statusDamageCalculate(pPokemonBo);
    pPokemonBo->minusHp(damage);
}

MoveBo PokemonModePrivate::getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo) {
    auto moveBos = pOppositingPokemonBo->getMoveBos();

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, moveBos.size());

    int randomNumber = distrib(gen);

    return moveBos[randomNumber - 1];
}


PokemonMode::PokemonMode(std::shared_ptr<DamageSystem> pDamageSystem)
    :mpPrivate(std::make_unique<PokemonModePrivate>(pDamageSystem))
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
    mpPrivate->statusDamage(mpPrivate->mpPokemonBo);
    mpPrivate->statusDamage(mpPrivate->mpOppositingPokemonBo);
}


void PokemonMode::nextRoundWithoutAttack() {
    auto oppositingMoveName = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo).name;
    mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMoveName);
    mpPrivate->statusDamage(mpPrivate->mpPokemonBo);
    mpPrivate->statusDamage(mpPrivate->mpOppositingPokemonBo);
}
