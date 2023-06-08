#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>

class PokemonBo;
class PokemonMode;
class PlayerModePrivate;
class PlayerMode
{
public:
    PlayerMode(std::shared_ptr<PokemonMode> pPokemonMode);
    PlayerMode(const PlayerMode& kPlayerMode);
    ~PlayerMode();

    void setPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pPokemonBoVec);
    void setOppositingPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pOppositingPokemonBoVec);

    bool faintingSwapPokemon(const int& kPokemonIndex);

    bool swapOppositingPokemon(const int& kPokemonIndex);
    bool swapPokemon(const int& kPokemonIndex);

    bool isWin();

    void battle(const int& kMoveIndex);


    std::vector<std::string> getPokemonsName() const;

    std::vector<std::pair<int, int>> getPokemonsHp() const;


    std::vector<std::pair<int, int>> getOppositingPokemonsHp() const;


    std::set<std::string> getCurrentPokemonAdditionalEffect() const;
    std::set<std::string> getOppositingPokemonAdditionalEffect() const;

    int getCurrentPokemonIndex() const;
    int getOppositingPokemonIndex() const;

    std::vector<std::string> getOppositingPokemonsName() const;

    std::vector<std::string> getCurrentPokemonMoves() const;

    void usePotion(const int& kPokemonIndex, const int& kPotionIndex);

    std::vector<std::string> getPotionsName() const;

    std::vector<bool> getPokemonsFaintStatus() const;

    int isWinOrLose() const;

    int getOppositingPokemonHp() const;

    std::vector<std::string> getCurrentPokemonMoveTypes() const;
private:
    std::unique_ptr<PlayerModePrivate> mpPrivate;
};
