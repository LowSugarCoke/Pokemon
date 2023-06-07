#include "pokemonMode.h"

#include <random>

#include "pokemonBo.h"
#include "damageMode.h"
#include "additionalEffectMode.h"
#include "pokemonLogger.h"
#include "potionMode.h"

class PokemonModePrivate {
public:
    PokemonModePrivate(std::shared_ptr<DamageMode> pDamageMode, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode,
        std::shared_ptr<PotionMode> pPotionMode);

    void damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const MoveBo& kMoveBo);
    MoveBo getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo);

    void myAttackLog(const MoveBo& kMoveBo);
    void oppositingAttackLog(const MoveBo& kMoveBo);
    void missingLog(std::shared_ptr<PokemonBo> mpOppositingPokemonBo);
    void paralyzedLog(std::shared_ptr<PokemonBo> pPokemonBo);

    std::shared_ptr<PokemonBo> mpPokemonBo;
    std::shared_ptr<PokemonBo> mpOppositingPokemonBo;
    std::shared_ptr<DamageMode> mpDamageMode;
    std::shared_ptr<AdditionalEffectMode> mpAdditionalEffectMode;
    std::shared_ptr<PotionMode> mpPotionMode;
    PokemonLogger& mLogger;
};

PokemonModePrivate::PokemonModePrivate(std::shared_ptr<DamageMode> pDamageMode,
    std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode
    , std::shared_ptr<PotionMode> pPotionMode)
    :mpDamageMode(pDamageMode)
    , mpAdditionalEffectMode(pAdditionalEffectMode)
    , mpPotionMode(pPotionMode)
    , mLogger(PokemonLogger::getInstance())
{

}


void PokemonModePrivate::myAttackLog(const MoveBo& kMoveBo) {
    auto name = mpPokemonBo->getName();
    mLogger.log(name + " used " + kMoveBo.name + "!");
}
void PokemonModePrivate::oppositingAttackLog(const MoveBo& kMoveBo) {
    auto name = mpOppositingPokemonBo->getName();
    mLogger.log("The opposing " + name + " used " + kMoveBo.name + "!");
}

void PokemonModePrivate::missingLog(std::shared_ptr<PokemonBo> mpOppositingPokemonBo) {
    auto name = mpOppositingPokemonBo->getName();
    mLogger.log(name + " avoided the attack!");
}

void PokemonModePrivate::paralyzedLog(std::shared_ptr<PokemonBo> pPokemonBo) {
    auto name = pPokemonBo->getName();
    mLogger.log(name + "is paralyzed!");
    mLogger.log("It can't move!");
}


void PokemonModePrivate::damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const MoveBo& kMoveBo) {
    if (mpDamageMode->isMissing(pAPokemonBo, pBPokemonBo, kMoveBo)) {
        missingLog(pBPokemonBo);
        return;
    }

    if (mpAdditionalEffectMode->unableToMove(pAPokemonBo)) {
        return;
    }

    if (pAPokemonBo->isMyPokemon()) {
        myAttackLog(kMoveBo);
    }
    else {
        oppositingAttackLog(kMoveBo);
    }

    int damage = mpDamageMode->damageCalculate(pAPokemonBo, pBPokemonBo, kMoveBo);
    pBPokemonBo->minusHp(damage);

    mpAdditionalEffectMode->addIfMoveHasAdditionalEffect(pBPokemonBo, kMoveBo);
}


MoveBo PokemonModePrivate::getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo) {
    auto moveBos = pOppositingPokemonBo->getMoveBos();

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, moveBos.size());

    int randomNumber = distrib(gen);

    return moveBos[randomNumber - 1];
}


PokemonMode::PokemonMode(std::shared_ptr<DamageMode> pDamageMode
    , std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode
    , std::shared_ptr<PotionMode> pPotionMode
)
    :mpPrivate(std::make_unique<PokemonModePrivate>(pDamageMode, pAdditionalEffectMode, pPotionMode))
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
    mpPrivate->mpPotionMode->setAddHPCallBack([&](const int& kHp) {
        mpPrivate->mpPokemonBo->addHp(kHp);
        });
}
void PokemonMode::setOppositingPokemon(std::shared_ptr<PokemonBo> pOppositingPokemon) {
    mpPrivate->mpOppositingPokemonBo = pOppositingPokemon;
}

void PokemonMode::nextRound(const int& kMoveIndex) {
    auto oppositingMove = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo);
    auto moveBo = mpPrivate->mpPokemonBo->findMoveBoByIndex(kMoveIndex);

    if (mpPrivate->mpPokemonBo->getPokemonStats().speed > mpPrivate->mpOppositingPokemonBo->getPokemonStats().speed) {
        mpPrivate->damage(mpPrivate->mpPokemonBo, mpPrivate->mpOppositingPokemonBo, moveBo);
        mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove);
    }
    else {
        mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove);
        mpPrivate->damage(mpPrivate->mpPokemonBo, mpPrivate->mpOppositingPokemonBo, moveBo);
    }
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo);
}


void PokemonMode::nextRoundWithoutAttack() {
    auto oppositingMove = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo);
    mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo);
}

void PokemonMode::usePotion(const int& kPotionIndex) {
    mpPrivate->mpPotionMode->usePotion(kPotionIndex);
}

std::vector<std::string> PokemonMode::getPotionsName() const {
    return mpPrivate->mpPotionMode->getPotionsName();
}
