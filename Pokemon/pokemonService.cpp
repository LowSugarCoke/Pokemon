#include "pokemonService.h"

#include "moveEntity.h"
#include "gameEntity.h"
#include "pokemonEntity.h"
#include "moveDao.h"
#include "gameDao.h"
#include "pokemonDao.h"
#include "pokemonBo.h"
#include "playerMode.h"
#include "pokemonMode.h"

class PokemonServicePrivate {
public:
    PokemonServicePrivate(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
        , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<PlayerMode>& kPlayerMode);

    std::shared_ptr<MoveDao> mpMoveDao;
    std::shared_ptr<GameDao> mpGameDao;
    std::shared_ptr<PokemonDao> mpPokemonDao;
    std::shared_ptr<PlayerMode> mpPlayerMode;
};

PokemonServicePrivate::PokemonServicePrivate(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
    , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<PlayerMode>& kPlayerMode)
    :mpMoveDao(kMoveDao)
    , mpGameDao(kGameDao)
    , mpPokemonDao(kPokemonDao)
    , mpPlayerMode(kPlayerMode)
{}


PokemonService::PokemonService(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
    , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<PlayerMode>& kPlayerMode)
    : mpPrivate(std::make_unique<PokemonServicePrivate>(kMoveDao, kGameDao, kPokemonDao, kPlayerMode))
{}

PokemonService::~PokemonService() {}


bool PokemonService::loadData(const std::string& kMoveFilePath, const std::string& kPokemonFilePath, const std::string& kGameFilePath) {
    std::vector<std::shared_ptr<PokemonBo>> pokemonBoVec;

    auto moveEntityVec = mpPrivate->mpMoveDao->getData(kMoveFilePath);
    auto pokemonEntityVec = mpPrivate->mpPokemonDao->getData(kPokemonFilePath);
    auto gameEntityVec = mpPrivate->mpGameDao->getData(kGameFilePath);

    if (moveEntityVec.empty() || pokemonEntityVec.empty() || gameEntityVec.empty()) {
        return false;
    }

    for (int i = 0; i < gameEntityVec.size(); i++) {
        std::shared_ptr<PokemonBo> pPokemonBo = std::make_shared<PokemonBo>();
        for (int j = 0; j < pokemonEntityVec.size(); j++) {
            if (gameEntityVec[i].getName() == pokemonEntityVec[j].getName()) {
                auto pokemonEntity = pokemonEntityVec[j];
                pPokemonBo->setPokemonElements(pokemonEntity.getName(), pokemonEntity.getStats(), pokemonEntity.getTypes());
                break;
            }
        }

        auto gameMoves = gameEntityVec[i].getMoves();
        for (int j = 0; j < gameMoves.size(); j++) {
            for (int k = 0; k < moveEntityVec.size(); k++) {
                if (gameMoves[j] == moveEntityVec[k].getName()) {
                    auto moveEntity = moveEntityVec[k];
                    pPokemonBo->addMoveElements(moveEntity.getName(), moveEntity.getMoveStats(), moveEntity.getType(),
                        moveEntity.getDamageType(), moveEntity.getAdditionalEffectType());
                }
            }
        }
        pokemonBoVec.push_back(pPokemonBo);
    }

    mpPrivate->mpPlayerMode->setPokemonBo(pokemonBoVec);
    return true;
}

std::vector<std::string> PokemonService::getPokemonsName() const {
    return mpPrivate->mpPlayerMode->getPokemonsName();
}

std::vector<std::pair<int, int>> PokemonService::getPokemonsHp() const {
    return mpPrivate->mpPlayerMode->getPokemonsHp();
}

std::set<std::string> PokemonService::getCurrentPokemonAdditionalEffect() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonAdditionalEffect();
}

std::string PokemonService::getBattleDailog() const {
    return "";
}
