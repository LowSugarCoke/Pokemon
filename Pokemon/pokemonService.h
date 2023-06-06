#pragma once

#include <memory>
#include <vector>
#include <string>

class MoveDao;
class PokemonDao;
class GameDao;
class PokemonBo;
class PokemonServicePrivate;
class PokemonService {
public:

    PokemonService(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao, const std::shared_ptr<PokemonDao>& kPokemonDao);

    std::vector<std::shared_ptr<PokemonBo>> getPokemonBos(const std::string& kMoveFilePath, const std::string& kPokemonFilePath, const std::string& kGameFilePath);

private:
    std::unique_ptr<PokemonServicePrivate> mpPrivate;
};
