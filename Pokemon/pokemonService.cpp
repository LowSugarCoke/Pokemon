#include "pokemonService.h"

#include "moveEntity.h"
#include "gameEntity.h"
#include "pokemonEntity.h"
#include "moveDao.h"
#include "gameDao.h"
#include "pokemonDao.h"
#include "pokemonStatsBo.h"

class PokemonServicePrivate {
public:
    PokemonServicePrivate(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao, const std::shared_ptr<PokemonDao>& kPokemonDao);

    std::shared_ptr<MoveDao> mpMoveDao;
    std::shared_ptr<GameDao> mpGameDao;
    std::shared_ptr<PokemonDao> mpPokemonDao;
};

PokemonServicePrivate::PokemonServicePrivate(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao, const std::shared_ptr<PokemonDao>& kPokemonDao)
    :mpMoveDao(kMoveDao)
    , mpGameDao(kGameDao)
    , mpPokemonDao(kPokemonDao)
{}


PokemonService::PokemonService(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao, const std::shared_ptr<PokemonDao>& kPokemonDao)
    : mpPrivate(std::make_unique<PokemonServicePrivate>(kMoveDao, kGameDao, kPokemonDao))
{}

std::vector<PokemonStatsBo> PokemonService::getPokemonBos(const std::string& kMoveFilePath, const std::string& kPokemonFilePath, const std::string& kGameFilePath) {
    std::vector<PokemonStatsBo> pokemonBo;

    auto moveEntityVec = mpPrivate->mpMoveDao->getData(kMoveFilePath);
    auto pokemonEntityVec = mpPrivate->mpPokemonDao->getData(kPokemonFilePath);
    auto gameEntityVec = mpPrivate->mpGameDao->getData(kGameFilePath);


    for (int i = 0; i < gameEntityVec.size(); i++) {
        PokemonStatsBo pokemonBoTmp;
        for (int j = 0; j < pokemonEntityVec.size(); j++) {
            if (gameEntityVec[i].getName() == pokemonEntityVec[j].getName()) {
                pokemonBoTmp.setPokemonEntity(pokemonEntityVec[j]);
                break;
            }
        }

        auto gameMoves = gameEntityVec[i].getMoves();
        for (int j = 0; j < gameMoves.size(); j++) {
            for (int k = 0; k < moveEntityVec.size(); k++) {
                if (gameMoves[j] == moveEntityVec[k].getName()) {
                    pokemonBoTmp.addMoveEntity(moveEntityVec[k]);
                }
            }
        }

        pokemonBo.push_back(pokemonBoTmp);
    }


    return pokemonBo;
}
