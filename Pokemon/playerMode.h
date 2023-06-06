#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>

class PokemonBo;
class PokemonMode;
class PlayerModePrivate;
class PlayerMode {
public:

    PlayerMode(std::shared_ptr<PokemonMode> pPokemonMode);
    PlayerMode(const PlayerMode& kPlayerMode);
    ~PlayerMode();

    void setPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pokemonBoVec);

    bool swapPokemon(const int& kPokemonIndex);

    bool isWin();

    std::vector<std::string> getPokemonsName() const;

    std::vector<std::pair<int, int>> getPokemonsHp() const;

    std::set<std::string> getCurrentPokemonAdditionalEffect() const;

private:
    std::unique_ptr<PlayerModePrivate> mpPrivate;
};
