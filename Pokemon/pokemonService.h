#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>

class MoveDao;
class PokemonDao;
class GameDao;
class PokemonBo;
class PlayerMode;
class PokemonMode;
class PokemonServicePrivate;
class PokemonService {
public:

    PokemonService(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao,
        const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<PlayerMode>& kPlayerMode);

    ~PokemonService();

    bool loadData(const std::string& kMoveFilePath, const std::string& kPokemonFilePath, const std::string& kGameFilePath);
    std::vector<std::string> getPokemonsName() const;
    int getCurrentPokemonIndex() const;
    std::vector<std::string> getOppositingPokemonsName() const;
    int getCurrentOppositingPokemonIndex() const;
    bool swapOppositingPokemon();
    std::vector<std::pair<int, int>> getPokemonsHp() const;
    std::vector<std::pair<int, int>> getOppositingPokemonsHp() const;
    int getOppositingPokemonHp() const;
    std::set<std::string> getCurrentPokemonAdditionalEffect() const;
    std::string getBattleDailog() const;
    void swapPokemon(const int& kIndex);
    bool faintingSwapPokemon(const int& kPokemonIndex);
    void battle(const int& kMoveIndex);

    std::vector<std::string> getCurrentPokemonMoves()const;
    void usePotion(const int& kPokemonIndex, const int& kPotionIndex);
    std::vector<std::string> getPotionsName() const;

    std::vector<bool> getPokemonsFaintStatus() const;
    int isWinOrLose() const; // 0 is not yet, 1 is win, 2 is lose


private:
    std::unique_ptr<PokemonServicePrivate> mpPrivate;
};
