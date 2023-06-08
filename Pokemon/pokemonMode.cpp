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

    bool mIsTest;
    bool mIsLastOppositePokemon;
};

PokemonModePrivate::PokemonModePrivate(std::shared_ptr<DamageMode> pDamageMode,
    std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode
    , std::shared_ptr<PotionMode> pPotionMode)
    :mpDamageMode(pDamageMode)
    , mpAdditionalEffectMode(pAdditionalEffectMode)
    , mpPotionMode(pPotionMode)
    , mIsTest(false)
    , mIsLastOppositePokemon(false)
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
        paralyzedLog(pAPokemonBo);
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
}
void PokemonMode::setOppositingPokemon(std::shared_ptr<PokemonBo> pOppositingPokemon) {
    mpPrivate->mpOppositingPokemonBo = pOppositingPokemon;
}

void PokemonMode::nextRound(const int& kMoveIndex, const int& kOppositeIndex) {

    MoveBo oppositingMove;
    if (!mpPrivate->mIsTest) {
        oppositingMove = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo);
    }
    else {
        oppositingMove = mpPrivate->mpOppositingPokemonBo->findMoveBoByIndex(kOppositeIndex);
    }

    auto moveBo = mpPrivate->mpPokemonBo->findMoveBoByIndex(kMoveIndex);

    mpPrivate->mpPokemonBo->minusMovePowerPoint(moveBo);

    if (mpPrivate->mpPokemonBo->getPokemonStats().speed >= mpPrivate->mpOppositingPokemonBo->getPokemonStats().speed) {
        mpPrivate->damage(mpPrivate->mpPokemonBo, mpPrivate->mpOppositingPokemonBo, moveBo);
        if (mpPrivate->mpOppositingPokemonBo->isFainting()) {
            mpPrivate->mLogger.log("The opposing " + mpPrivate->mpOppositingPokemonBo->getName() + " fainted!");
            if (!mpPrivate->mIsLastOppositePokemon) {
                mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo);
                mpPrivate->mLogger.addTurn();
            }

            return;
        }
        mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove);
    }
    else {
        mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove);
        if (mpPrivate->mpPokemonBo->isFainting()) {
            mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo);
            mpPrivate->mLogger.addTurn();
            return;
        }
        mpPrivate->damage(mpPrivate->mpPokemonBo, mpPrivate->mpOppositingPokemonBo, moveBo);
    }
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo);

    mpPrivate->mLogger.addTurn();
}

void PokemonMode::nextRoundWithoutAttack(const int& kOppositingIndex) {

    MoveBo oppositingMove;
    if (!mpPrivate->mIsTest) {
        oppositingMove = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo);
    }
    else {
        oppositingMove = mpPrivate->mpOppositingPokemonBo->findMoveBoByIndex(kOppositingIndex);
    }

    mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo);
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo);

    mpPrivate->mLogger.addTurn();
}

void PokemonMode::usePotion(std::shared_ptr<PokemonBo> pPokemonBo, const int& kPotionIndex) {
    mpPrivate->mpPotionMode->addHp(pPokemonBo, kPotionIndex);

}

std::vector<std::string> PokemonMode::getPotionsName() const {
    return mpPrivate->mpPotionMode->getPotionsName();
}

void PokemonMode::setTest() {
    mpPrivate->mpDamageMode->setTest();
    mpPrivate->mpAdditionalEffectMode->setTest();
    mpPrivate->mIsTest = true;
}

void PokemonMode::setLastOppositePokemon() {
    mpPrivate->mIsLastOppositePokemon = true;
}
