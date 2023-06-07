#include "playerMode.h"

#include "pokemonBo.h"
#include "pokemonMode.h"
#include "pokemonLogger.h"

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
};

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

bool PlayerMode::swapPokemon(const int& kPokemonIndex) {
    if (mpPrivate->mpPokemonBoVec[kPokemonIndex]->isFainting()) {
        return false;
    }

    mpPrivate->swapBeforeLog();
    mpPrivate->mPokemonIndex = kPokemonIndex;
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]);
    mpPrivate->swapAfterLog();


    // mpPrivate->mpPokemonMode->nextRoundWithoutAttack();
}


bool PlayerMode::isWin() {
    auto pokemonBoVec = mpPrivate->mpPokemonBoVec;
    int num = 0;
    for (int i = 0; i < pokemonBoVec.size(); i++) {
        if (pokemonBoVec[i]->isFainting()) {
            num++;
        }
    }

    return num == pokemonBoVec.size();
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



std::set<std::string> PlayerMode::getCurrentPokemonAdditionalEffect() const {
    std::set<std::string> data;
    auto currentPokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
    for (auto additionalEffect : currentPokemon->getPokemonAdditionalEffectType()) {
        data.insert(effectTypeToString(additionalEffect));
    }
    return data;
}

void PlayerMode::battle(const int& kMoveIndex) {
    mpPrivate->mpPokemonMode->nextRound(kMoveIndex);
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
