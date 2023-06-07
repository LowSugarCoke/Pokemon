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
#include "pokemonLogger.h"

class PokemonServicePrivate {
public:
    PokemonServicePrivate(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
        , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<PlayerMode>& kPlayerMode);

    std::shared_ptr<MoveDao> mpMoveDao;
    std::shared_ptr<GameDao> mpGameDao;
    std::shared_ptr<PokemonDao> mpPokemonDao;
    std::shared_ptr<PlayerMode> mpPlayerMode;
    PokemonLogger& mLogger;
};

PokemonServicePrivate::PokemonServicePrivate(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
    , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<PlayerMode>& kPlayerMode)
    :mpMoveDao(kMoveDao)
    , mpGameDao(kGameDao)
    , mpPokemonDao(kPokemonDao)
    , mpPlayerMode(kPlayerMode)
    , mLogger(PokemonLogger::getInstance())
{}


PokemonService::PokemonService(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
    , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<PlayerMode>& kPlayerMode)
    : mpPrivate(std::make_unique<PokemonServicePrivate>(kMoveDao, kGameDao, kPokemonDao, kPlayerMode))
{}

PokemonService::~PokemonService() {}


bool PokemonService::loadData(const std::string& kMoveFilePath, const std::string& kPokemonFilePath, const std::string& kGameFilePath) {
    std::vector<std::shared_ptr<PokemonBo>> pPokemonBoVec;
    std::vector<std::shared_ptr<PokemonBo>> pOppositingPokemonBoVec;

    auto moveEntityVec = mpPrivate->mpMoveDao->getData(kMoveFilePath);
    auto pokemonEntityVec = mpPrivate->mpPokemonDao->getData(kPokemonFilePath);
    auto gameEntityVec = mpPrivate->mpGameDao->getData(kGameFilePath);

    auto myGameEntityVec = gameEntityVec.first;
    auto oppositingGameEntityVec = gameEntityVec.second;

    if (moveEntityVec.empty() || pokemonEntityVec.empty() || myGameEntityVec.empty() || oppositingGameEntityVec.empty()) {
        return false;
    }

    for (int i = 0; i < myGameEntityVec.size(); i++) {
        std::shared_ptr<PokemonBo> pPokemonBo = std::make_shared<PokemonBo>();
        for (int j = 0; j < pokemonEntityVec.size(); j++) {
            if (myGameEntityVec[i].getName() == pokemonEntityVec[j].getName()) {
                auto pokemonEntity = pokemonEntityVec[j];
                pPokemonBo->setPokemonElements(pokemonEntity.getName(), pokemonEntity.getStats(), pokemonEntity.getTypes());
                break;
            }
        }

        auto gameMoves = myGameEntityVec[i].getMoves();
        for (int j = 0; j < gameMoves.size(); j++) {
            for (int k = 0; k < moveEntityVec.size(); k++) {
                if (gameMoves[j] == moveEntityVec[k].getName()) {
                    auto moveEntity = moveEntityVec[k];
                    pPokemonBo->addMoveElements(moveEntity.getName(), moveEntity.getMoveStats(), moveEntity.getType(),
                        moveEntity.getDamageType(), moveEntity.getAdditionalEffectType());
                }
            }
        }
        pPokemonBo->checkToMyPokemon(true);
        pPokemonBoVec.push_back(pPokemonBo);
    }

    for (int i = 0; i < oppositingGameEntityVec.size(); i++) {
        std::shared_ptr<PokemonBo> pPokemonBo = std::make_shared<PokemonBo>();
        for (int j = 0; j < pokemonEntityVec.size(); j++) {
            if (oppositingGameEntityVec[i].getName() == pokemonEntityVec[j].getName()) {
                auto pokemonEntity = pokemonEntityVec[j];
                pPokemonBo->setPokemonElements(pokemonEntity.getName(), pokemonEntity.getStats(), pokemonEntity.getTypes());
                break;
            }
        }

        auto gameMoves = oppositingGameEntityVec[i].getMoves();
        for (int j = 0; j < gameMoves.size(); j++) {
            for (int k = 0; k < moveEntityVec.size(); k++) {
                if (gameMoves[j] == moveEntityVec[k].getName()) {
                    auto moveEntity = moveEntityVec[k];
                    pPokemonBo->addMoveElements(moveEntity.getName(), moveEntity.getMoveStats(), moveEntity.getType(),
                        moveEntity.getDamageType(), moveEntity.getAdditionalEffectType());
                }
            }
        }
        pPokemonBo->checkToMyPokemon(false);
        pOppositingPokemonBoVec.push_back(pPokemonBo);
    }


    mpPrivate->mpPlayerMode->setPokemonBo(pPokemonBoVec);
    mpPrivate->mpPlayerMode->setOppositingPokemonBo(pOppositingPokemonBoVec);
    return true;
}

std::vector<std::string> PokemonService::getPokemonsName() const {
    return mpPrivate->mpPlayerMode->getPokemonsName();
}

std::vector<std::pair<int, int>> PokemonService::getOppositingPokemonsHp() const {
    return mpPrivate->mpPlayerMode->getOppositingPokemonsHp();
}

std::vector<std::pair<int, int>> PokemonService::getPokemonsHp() const {
    return mpPrivate->mpPlayerMode->getPokemonsHp();
}

std::set<std::string> PokemonService::getCurrentPokemonAdditionalEffect() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonAdditionalEffect();
}

std::string PokemonService::getBattleDailog() const {
    return mpPrivate->mLogger.getLog();
}

void PokemonService::swapPokemon(const int& kIndex) {
    mpPrivate->mpPlayerMode->swapPokemon(kIndex);
}

void PokemonService::battle(const int& kMoveIndex) {
    mpPrivate->mpPlayerMode->battle(kMoveIndex);
    mpPrivate->mLogger.addTurn();
}

int PokemonService::getCurrentPokemonIndex() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonIndex();
}
std::vector<std::string>  PokemonService::getOppositingPokemonsName() const {
    return mpPrivate->mpPlayerMode->getOppositingPokemonsName();
}
int  PokemonService::getCurrentOppositingPokemonIndex() const {
    return mpPrivate->mpPlayerMode->getOppositingPokemonIndex();
}

std::vector<std::string> PokemonService::getCurrentPokemonMoves()const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonMoves();
}
