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
    std::vector<std::pair<int, int>> getPokemonsHp() const;
    std::vector<std::pair<int, int>> getOppositingPokemonsHp() const;
    std::set<std::string> getCurrentPokemonAdditionalEffect() const;
    std::string getBattleDailog() const;
    void swapPokemon(const int& kIndex);
    void battle(const int& kMoveIndex);

    std::vector<std::string> getCurrentPokemonMoves()const;
private:
    std::unique_ptr<PokemonServicePrivate> mpPrivate;
};
