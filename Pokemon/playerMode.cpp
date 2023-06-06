#include "playerMode.h"

#include "pokemonBo.h"
#include "pokemonMode.h"

class PlayerModePrivate {
public:

    PlayerModePrivate(std::shared_ptr<PokemonMode> pPokemonMode);

    std::vector<std::shared_ptr<PokemonBo>> mpPokemonBoVec;
    std::shared_ptr<PokemonMode> mpPokemonMode;
    int mPokemonIndex;
};

PlayerModePrivate::PlayerModePrivate(std::shared_ptr<PokemonMode> pPokemonMode)
    :mpPokemonMode(pPokemonMode)
{

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

void PlayerMode::setPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pokemonBoVec) {
    mpPrivate->mpPokemonBoVec = pokemonBoVec;
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[0]);
}

bool PlayerMode::swapPokemon(const int& kPokemonIndex) {
    if (mpPrivate->mpPokemonBoVec[kPokemonIndex]->isFainting()) {
        return false;
    }

    mpPrivate->mPokemonIndex = kPokemonIndex;
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]);
    mpPrivate->mpPokemonMode->nextRoundWithoutAttack();
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


std::set<std::string> PlayerMode::getCurrentPokemonAdditionalEffect() const {
    std::set<std::string> data;
    auto currentPokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
    for (auto additionalEffect : currentPokemon->getPokemonAdditionalEffectType()) {
        data.insert(effectTypeToString(additionalEffect));
    }
    return data;
}
