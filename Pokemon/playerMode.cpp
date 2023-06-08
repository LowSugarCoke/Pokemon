#include "playerMode.h"

#include <unordered_map>
#include <QString>

#include "pokemonBo.h"
#include "pokemonMode.h"
#include "pokemonLogger.h"
#include "additionalEffectType.h"



static  std::unordered_map<std::string, int> convertPotionToIndexMap{
    {"Potion", 0},
    {"SuperPotion", 1},
    {"HyperPotion", 2},
    {"MaxPotion", 3},
};

class PlayerModePrivate {
public:

    PlayerModePrivate(std::shared_ptr<PokemonMode> pPokemonMode);

    void swapBeforeLog();
    void swapAfterLog();

    std::vector<std::shared_ptr<PokemonBo>> mpPokemonBoVec;
    std::vector<std::shared_ptr<PokemonBo>> mpOppositingPokemonBoVec;
    std::shared_ptr<PokemonMode> mpPokemonMode;
    PokemonLogger& mLogger;
    int mPokemonIndex;
    int mOppositingPokemonIndex;
    bool mIsTest;
    int findPokemonIndexByName(const std::string& kPokemonName) const;
    std::shared_ptr<PokemonBo> findPokemonBoByName(const std::string& kPokemonName) const;
};

int PlayerModePrivate::findPokemonIndexByName(const std::string& kPokemonName) const {
    for (int i = 0; i < mpPokemonBoVec.size(); i++) {
        if (mpPokemonBoVec[i]->getName() == kPokemonName) {
            return i;
        }
    }
}

PlayerModePrivate::PlayerModePrivate(std::shared_ptr<PokemonMode> pPokemonMode)
    :mpPokemonMode(pPokemonMode)
    , mLogger(PokemonLogger::getInstance())
{
    mPokemonIndex = 0;
    mOppositingPokemonIndex = 0;
}

void PlayerModePrivate::swapBeforeLog() {
    auto name = mpPokemonBoVec[mPokemonIndex]->getName();
    mLogger.log(name + ", switch out!");
}

void PlayerModePrivate::swapAfterLog() {
    auto name = mpPokemonBoVec[mPokemonIndex]->getName();
    mLogger.log("Come back!");
    mLogger.log("Go! " + name + "!");
}


std::shared_ptr<PokemonBo> PlayerModePrivate::findPokemonBoByName(const std::string& kPokemonName) const {
    for (int i = 0; i < mpPokemonBoVec.size(); i++) {
        if (mpPokemonBoVec[i]->getName() == kPokemonName) {
            return mpPokemonBoVec[i];
        }
    }

}


PlayerMode::PlayerMode(std::shared_ptr<PokemonMode> pPokemonMode)
    : mpPrivate(std::make_unique<PlayerModePrivate>(pPokemonMode))
{

}

PlayerMode::PlayerMode(const PlayerMode& kPlayerMode)
    : mpPrivate(std::make_unique<PlayerModePrivate>(*kPlayerMode.mpPrivate))
{}



PlayerMode::~PlayerMode() {

}

void PlayerMode::setPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pPokemonBoVec) {
    mpPrivate->mpPokemonBoVec = pPokemonBoVec;
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[0]);
}



void PlayerMode::setOppositingPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pOppositingPokemonBoVec) {
    mpPrivate->mpOppositingPokemonBoVec = pOppositingPokemonBoVec;
    mpPrivate->mpPokemonMode->setOppositingPokemon(mpPrivate->mpOppositingPokemonBoVec[0]);
}

bool PlayerMode::faintingSwapPokemon(const int& kPokemonIndex) {
    if (mpPrivate->mpPokemonBoVec[kPokemonIndex]->isFainting()) {
        return false;
    }

    mpPrivate->swapBeforeLog();
    mpPrivate->mPokemonIndex = kPokemonIndex;
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]);
    mpPrivate->swapAfterLog();

    return true;
}

bool PlayerMode::swapPokemon(const int& kPokemonIndex) {
    if (mpPrivate->mpPokemonBoVec[kPokemonIndex]->isFainting()) {
        return false;
    }

    mpPrivate->swapBeforeLog();
    mpPrivate->mPokemonIndex = kPokemonIndex;
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]);
    mpPrivate->swapAfterLog();


    mpPrivate->mpPokemonMode->nextRoundWithoutAttack();
}

bool PlayerMode::swapOppositingPokemon(const int& kPokemonIndex) {
    if (kPokemonIndex >= mpPrivate->mpOppositingPokemonBoVec.size()) {
        return false;
    }

    if (mpPrivate->mpOppositingPokemonBoVec[kPokemonIndex]->isFainting()) {
        return false;
    }

    mpPrivate->mOppositingPokemonIndex = kPokemonIndex;
    mpPrivate->mpPokemonMode->setOppositingPokemon(mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]);
    if (kPokemonIndex == 2) {
        mpPrivate->mpPokemonMode->setLastOppositePokemon();
    }
}





std::vector<std::string> PlayerMode::getPokemonsName() const {
    std::vector<std::string> data;
    auto pokemons = mpPrivate->mpPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        data.push_back(pokemons[i]->getName());
    }
    return data;
}

std::vector<std::string> PlayerMode::getOppositingPokemonsName() const {
    std::vector<std::string> data;
    auto pokemons = mpPrivate->mpOppositingPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        data.push_back(pokemons[i]->getName());
    }
    return data;
}



std::vector<std::pair<int, int>> PlayerMode::getPokemonsHp() const {
    std::vector<std::pair<int, int>> data;
    auto pokemons = mpPrivate->mpPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        auto currentHp = pokemons[i]->getPokemonStats().hp;
        auto maxHp = pokemons[i]->getMaxHp();
        std::pair<int, int> hpPair{ currentHp, maxHp };

        data.push_back(hpPair);

    }
    return data;
}

std::vector<std::pair<int, int>> PlayerMode::getOppositingPokemonsHp() const {
    std::vector<std::pair<int, int>> data;
    auto pokemons = mpPrivate->mpOppositingPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        auto currentHp = pokemons[i]->getPokemonStats().hp;
        auto maxHp = pokemons[i]->getMaxHp();
        std::pair<int, int> hpPair{ currentHp, maxHp };

        data.push_back(hpPair);

    }
    return data;
}

std::set<std::string> PlayerMode::getOppositingPokemonAdditionalEffect() const {
    std::set<std::string> data;
    auto currentPokemon = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex];
    for (auto additionalEffect : currentPokemon->getPokemonAdditionalEffectType()) {
        data.insert(effectTypeToString(additionalEffect));
    }
    return data;
}

std::set<std::string> PlayerMode::getCurrentPokemonAdditionalEffect() const {
    std::set<std::string> data;
    auto currentPokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
    for (auto additionalEffect : currentPokemon->getPokemonAdditionalEffectType()) {
        data.insert(effectTypeToString(additionalEffect));
    }
    return data;
}

void PlayerMode::battle(const int& kMoveIndex, const int& kOppositeIndex) {
    if (!mpPrivate->mIsTest) {
        mpPrivate->mpPokemonMode->nextRound(kMoveIndex);
    }
    else {
        mpPrivate->mpPokemonMode->nextRound(kMoveIndex, kOppositeIndex);
    }
    if (mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->isFainting()) {
        swapOppositingPokemon(mpPrivate->mOppositingPokemonIndex + 1);
    }
    if (isWinOrLose() == 1) {
        mpPrivate->mLogger.log("You win");
    }
    else if (isWinOrLose() == 2) {
        mpPrivate->mLogger.log("You lose");
    }

}


int PlayerMode::getCurrentPokemonIndex() const {
    return mpPrivate->mPokemonIndex;
}

int PlayerMode::getOppositingPokemonIndex() const {
    return mpPrivate->mOppositingPokemonIndex;
}


std::vector<std::string> PlayerMode::getCurrentPokemonMoves() const {
    std::vector<std::string > moves;
    auto moveBo = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]->getMoveBos();
    for (int i = 0; i < moveBo.size(); i++) {
        moves.push_back(moveBo[i].name);
    }
    return moves;
}


void PlayerMode::usePotion(const int& kPokemonIndex, const int& kPotionIndex) {
    mpPrivate->mpPokemonMode->usePotion(mpPrivate->mpPokemonBoVec[kPokemonIndex], kPotionIndex);
    mpPrivate->mpPokemonMode->nextRoundWithoutAttack();
}

std::vector<std::string> PlayerMode::getPotionsName() const {
    return mpPrivate->mpPokemonMode->getPotionsName();
}


std::vector<bool> PlayerMode::getPokemonsFaintStatus() const {
    std::vector<bool> paintVec;

    auto pokemons = mpPrivate->mpPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        if (pokemons[i]->isFainting()) {
            paintVec.push_back(true);
        }
        else {
            paintVec.push_back(false);
        }
    }
    return paintVec;
}


// 0 is not yet, 1 is win, 2 is lose
int PlayerMode::isWinOrLose() const {
    int oppositingFaintCnt = 0;
    for (int i = 0; i < mpPrivate->mpOppositingPokemonBoVec.size(); i++) {
        oppositingFaintCnt += mpPrivate->mpOppositingPokemonBoVec[i]->isFainting();
    }

    if (oppositingFaintCnt == mpPrivate->mpOppositingPokemonBoVec.size()) {
        return 1;
    }

    int myFaintCnt = 0;
    for (int i = 0; i < mpPrivate->mpPokemonBoVec.size(); i++) {
        myFaintCnt += mpPrivate->mpPokemonBoVec[i]->isFainting();
    }
    if (myFaintCnt == mpPrivate->mpOppositingPokemonBoVec.size()) {
        return 2;
    }

    return 0;

}

int PlayerMode::getOppositingPokemonHp() const {
    return mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->getHp();
}


std::vector<std::string> PlayerMode::getCurrentPokemonMoveTypes() const {
    std::vector<std::string> data;
    auto pokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
    auto moveBo = pokemon->getMoveBos();
    for (auto move : moveBo) {
        data.push_back(reverseTypeMap[move.type]);
    }
    return data;
}


std::vector<int> PlayerMode::getCurrentPokemonPowerPoints() const {
    std::vector<int> data;
    auto pokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
    auto moveBos = pokemon->getMoveBos();
    for (auto move : moveBos) {
        data.push_back(move.stats.powerPoint);
    }
    return data;
}

std::vector<int> PlayerMode::getCurrentPokemonMaxPowerPoints() const {
    return mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]->getMaxPowerPoint();
}


void PlayerMode::setTest() {
    mpPrivate->mpPokemonMode->setTest();
    mpPrivate->mIsTest = true;
}

void PlayerMode::runTest(const std::vector<std::string>& kTestData) {
    for (int i = 0; i < kTestData.size(); i++) {
        if (mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->isFainting()) {
            swapOppositingPokemon(mpPrivate->mOppositingPokemonIndex + 1);
        }

        if (kTestData[i] == "Battle") {
            i++;
            auto myMoveIndex = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]->findMoveIndexByName(kTestData[i]);
            i++;
            auto oppositeMoveIndex = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->findMoveIndexByName(kTestData[i]);
            mpPrivate->mpPokemonMode->nextRound(myMoveIndex, oppositeMoveIndex);
        }
        else if (kTestData[i] == "Bag") {
            i++;
            auto potionIndex = convertPotionToIndexMap[kTestData[i]];
            i++;
            auto pokemonBo = mpPrivate->findPokemonBoByName(kTestData[i]);
            mpPrivate->mpPokemonMode->usePotion(pokemonBo, potionIndex);
            i++;
            auto oppositeMoveIndex = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->findMoveIndexByName(kTestData[i]);
            mpPrivate->mpPokemonMode->nextRoundWithoutAttack(oppositeMoveIndex);
        }
        else if (kTestData[i] == "Pokemon") {
            i++;
            auto pokemonIndex = mpPrivate->findPokemonIndexByName(kTestData[i]);

            if (mpPrivate->mpPokemonBoVec[pokemonIndex]->isFainting()) {
                continue;
            }

            mpPrivate->swapBeforeLog();
            mpPrivate->mPokemonIndex = pokemonIndex;
            mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]);
            mpPrivate->swapAfterLog();

            i++;
            auto oppositeMoveIndex = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->findMoveIndexByName(kTestData[i]);
            mpPrivate->mpPokemonMode->nextRoundWithoutAttack(oppositeMoveIndex);

        }
        else if (kTestData[i] == "Status") {
            auto myPokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
            auto name = myPokemon->getName();
            auto myHp = myPokemon->getHp();
            auto effect = myPokemon->getPokemonAdditionalEffectType();
            std::string effectStr = "";
            for (auto& e : effect) {
                effectStr += effectTypeToString(e);
            }

            auto oppositePokemon = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex];
            auto oppositeName = oppositePokemon->getName();
            auto oppositeHp = oppositePokemon->getHp();
            auto oppositeEffect = oppositePokemon->getPokemonAdditionalEffectType();
            std::string oppositeEffectStr = "";
            for (auto& e : oppositeEffect) {
                oppositeEffectStr += effectTypeToString(e);
            }
            std::string mes = name + " " + std::to_string(myHp) + " " + effectStr + " " + oppositeName + " " + std::to_string(oppositeHp) + " " + oppositeEffectStr;
            mpPrivate->mLogger.log(mes);


        }
        else if (kTestData[i] == "Check") {
            auto myPokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
            auto moveBos = myPokemon->getMoveBos();
            std::string meg = "";
            for (int i = 0; i < moveBos.size(); i++) {
                meg += moveBos[i].name + " " + std::to_string(moveBos[i].stats.powerPoint) + " ";
            }
            mpPrivate->mLogger.log(meg);
        }

    }

    if (isWinOrLose() == 1) {
        mpPrivate->mLogger.log("You win");
    }
    else if (isWinOrLose() == 2) {
        mpPrivate->mLogger.log("You lose");
    }
}
