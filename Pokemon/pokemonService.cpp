#include "pokemonService.h"

#include "moveEntity.h"
#include "gameEntity.h"
#include "pokemonEntity.h"
#include "moveDao.h"
#include "gameDao.h"
#include "pokemonDao.h"
#include "testDataDao.h"
#include "pokemonBo.h"
#include "playerMode.h"
#include "pokemonMode.h"
#include "pokemonLogger.h"

class PokemonServicePrivate {
public:
    PokemonServicePrivate(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
        , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<TestDataDao>& kTestDataDao, const std::shared_ptr<PlayerMode>& kPlayerMode);

    std::shared_ptr<MoveDao> mpMoveDao;
    std::shared_ptr<GameDao> mpGameDao;
    std::shared_ptr<PokemonDao> mpPokemonDao;
    std::shared_ptr<TestDataDao> mpTestDataDao;
    std::shared_ptr<PlayerMode> mpPlayerMode;
    PokemonLogger& mLogger;

};

// Private class that holds the dependencies and private members of PokemonService
PokemonServicePrivate::PokemonServicePrivate(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
    , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<TestDataDao>& kTestDataDao, const std::shared_ptr<PlayerMode>& kPlayerMode)
    : mpMoveDao(kMoveDao)
    , mpGameDao(kGameDao)
    , mpPokemonDao(kPokemonDao)
    , mpTestDataDao(kTestDataDao)
    , mpPlayerMode(kPlayerMode)
    , mLogger(PokemonLogger::getInstance())
{
    // Constructor initializes the member variables
}


// Public constructor of PokemonService that initializes the private implementation class
PokemonService::PokemonService(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao
    , const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr<TestDataDao>& kTestDataDao, const std::shared_ptr<PlayerMode>& kPlayerMode)
    : mpPrivate(std::make_unique<PokemonServicePrivate>(kMoveDao, kGameDao, kPokemonDao, kTestDataDao, kPlayerMode))
{
    // Constructor implementation
}

// Destructor of PokemonService
PokemonService::~PokemonService() {
    // Destructor implementation
}


// Loads data from various files and initializes the player's and opponent's Pokemon
bool PokemonService::loadData(const std::string& kMoveFilePath, const std::string& kPokemonFilePath, const std::string& kGameFilePath) {
    std::vector<std::shared_ptr<PokemonBo>> pPokemonBoVec;
    std::vector<std::shared_ptr<PokemonBo>> pOppositingPokemonBoVec;

    // Retrieve move, Pokemon, and game data from respective data access objects (DAOs)
    auto moveEntityVec = mpPrivate->mpMoveDao->getData(kMoveFilePath);
    auto pokemonEntityVec = mpPrivate->mpPokemonDao->getData(kPokemonFilePath);
    auto gameEntityVec = mpPrivate->mpGameDao->getData(kGameFilePath);

    auto myGameEntityVec = gameEntityVec.first;
    auto opposingGameEntityVec = gameEntityVec.second;

    // Check if any of the required data is missing
    if (moveEntityVec.empty() || pokemonEntityVec.empty() || myGameEntityVec.empty() || opposingGameEntityVec.empty()) {
        return false;
    }

    // Load player's Pokemon data
    for (int i = 0; i < myGameEntityVec.size(); i++) {
        std::shared_ptr<PokemonBo> pPokemonBo = std::make_shared<PokemonBo>();
        for (int j = 0; j < pokemonEntityVec.size(); j++) {
            if (myGameEntityVec[i].getName() == pokemonEntityVec[j].getName()) {
                // Match the game entity with the corresponding Pokemon entity
                auto pokemonEntity = pokemonEntityVec[j];
                pPokemonBo->setPokemonElements(pokemonEntity.getName(), pokemonEntity.getStats(), pokemonEntity.getTypes());
                break;
            }
        }

        // Add the moves to the player's Pokemon
        auto gameMoves = myGameEntityVec[i].getMoves();
        for (int j = 0; j < gameMoves.size(); j++) {
            for (int k = 0; k < moveEntityVec.size(); k++) {
                if (gameMoves[j] == moveEntityVec[k].getName()) {
                    // Match the game move with the corresponding move entity
                    auto moveEntity = moveEntityVec[k];
                    pPokemonBo->addMoveElements(moveEntity.getName(), moveEntity.getMoveStats(), moveEntity.getType(),
                        moveEntity.getDamageType(), moveEntity.getAdditionalEffectType());
                }
            }
        }
        pPokemonBo->checkToMyPokemon(true);
        pPokemonBoVec.push_back(pPokemonBo);
    }

    // Load opponent's Pokemon data
    for (int i = 0; i < opposingGameEntityVec.size(); i++) {
        std::shared_ptr<PokemonBo> pPokemonBo = std::make_shared<PokemonBo>();
        for (int j = 0; j < pokemonEntityVec.size(); j++) {
            if (opposingGameEntityVec[i].getName() == pokemonEntityVec[j].getName()) {
                // Match the opposing game entity with the corresponding Pokemon entity
                auto pokemonEntity = pokemonEntityVec[j];
                pPokemonBo->setPokemonElements(pokemonEntity.getName(), pokemonEntity.getStats(), pokemonEntity.getTypes());
                break;
            }
        }

        // Add the moves to the opposing Pokemon
        auto gameMoves = opposingGameEntityVec[i].getMoves();
        for (int j = 0; j < gameMoves.size(); j++) {
            for (int k = 0; k < moveEntityVec.size(); k++) {
                if (gameMoves[j] == moveEntityVec[k].getName()) {
                    // Match the game move with the corresponding move entity
                    auto moveEntity = moveEntityVec[k];
                    pPokemonBo->addMoveElements(moveEntity.getName(), moveEntity.getMoveStats(), moveEntity.getType(),
                        moveEntity.getDamageType(), moveEntity.getAdditionalEffectType());
                }
            }
        }
        pPokemonBo->checkToMyPokemon(false);
        pOppositingPokemonBoVec.push_back(pPokemonBo);
    }

    // Set the loaded Pokemon data in the player mode
    mpPrivate->mpPlayerMode->setPokemonBo(pPokemonBoVec);
    mpPrivate->mpPlayerMode->setOppositingPokemonBo(pOppositingPokemonBoVec);
    return true;
}

// Get the names of the player's Pokemon
std::vector<std::string> PokemonService::getPokemonsName() const {
    return mpPrivate->mpPlayerMode->getPokemonsName();
}

// Get the HP (health points) of the opponent's Pokemon
std::vector<std::pair<int, int>> PokemonService::getOppositingPokemonsHp() const {
    return mpPrivate->mpPlayerMode->getOppositingPokemonsHp();
}

// Get the HP (health points) of the player's Pokemon
std::vector<std::pair<int, int>> PokemonService::getPokemonsHp() const {
    return mpPrivate->mpPlayerMode->getPokemonsHp();
}

// Get the additional effects of the current player's Pokemon
std::set<std::string> PokemonService::getCurrentPokemonAdditionalEffect() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonAdditionalEffect();
}

// Get the additional effects of the opponent's Pokemon
std::set<std::string> PokemonService::getOppositingPokemonAdditionalEffect() const {
    return mpPrivate->mpPlayerMode->getOppositingPokemonAdditionalEffect();
}

// Get the battle dialogue
std::string PokemonService::getBattleDailog() const {
    return mpPrivate->mLogger.getLog();
}

// Swap the player's Pokemon with the one at the given index
void PokemonService::swapPokemon(const int& kIndex) {
    mpPrivate->mpPlayerMode->swapPokemon(kIndex);
}

// Perform a battle move with the specified move index and opponent index
void PokemonService::battle(const int& kMoveIndex, const int& kOppositeIndex) {
    mpPrivate->mpPlayerMode->battle(kMoveIndex);
}

// Get the index of the current player's Pokemon
int PokemonService::getCurrentPokemonIndex() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonIndex();
}

// Get the names of the opponent's Pokemon
std::vector<std::string> PokemonService::getOppositingPokemonsName() const {
    return mpPrivate->mpPlayerMode->getOppositingPokemonsName();
}

// Get the index of the current opponent's Pokemon
int PokemonService::getCurrentOppositingPokemonIndex() const {
    return mpPrivate->mpPlayerMode->getOppositingPokemonIndex();
}

// Get the moves of the current player's Pokemon
std::vector<std::string> PokemonService::getCurrentPokemonMoves() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonMoves();
}

// Use a potion on the specified player's Pokemon and potion index
void PokemonService::usePotion(const int& kPokemonIndex, const int& kPotionIndex) {
    mpPrivate->mpPlayerMode->usePotion(kPokemonIndex, kPotionIndex);
}

// Get the names of available potions
std::vector<std::string> PokemonService::getPotionsName() const {
    return mpPrivate->mpPlayerMode->getPotionsName();
}

// Get the faint status of the player's Pokemon
std::vector<bool> PokemonService::getPokemonsFaintStatus() const {
    return mpPrivate->mpPlayerMode->getPokemonsFaintStatus();
}

// Check if the player has won or lost the battle
int PokemonService::isWinOrLose() const {
    // 0 is not yet determined, 1 is win, 2 is lose
    return mpPrivate->mpPlayerMode->isWinOrLose();
}

// Swap the player's Pokemon with a fainted one at the specified index
bool PokemonService::faintingSwapPokemon(const int& kPokemonIndex) {
    return mpPrivate->mpPlayerMode->faintingSwapPokemon(kPokemonIndex);
}

// Swap the opponent's Pokemon to the next one in the list
bool PokemonService::swapOppositingPokemon() {
    auto opposingPokemonIndex = mpPrivate->mpPlayerMode->getOppositingPokemonIndex();
    return mpPrivate->mpPlayerMode->swapOppositingPokemon(opposingPokemonIndex + 1);
}

// Get the HP (health points) of the opponent's Pokemon
int PokemonService::getOppositingPokemonHp() const {
    return mpPrivate->mpPlayerMode->getOppositingPokemonHp();
}

// Get the move types of the current player's Pokemon
std::vector<std::string> PokemonService::getCurrentPokemonMoveTypes() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonMoveTypes();
}

// Get the power points (PP) of the current player's Pokemon moves
std::vector<int> PokemonService::getCurrentPokemonPowerPoints() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonPowerPoints();
}

// Get the maximum power points (PP) of the current player's Pokemon moves
std::vector<int> PokemonService::getCurrentPokemonMaxPowerPoints() const {
    return mpPrivate->mpPlayerMode->getCurrentPokemonMaxPowerPoints();
}

// Load test data from a file and run the test
bool PokemonService::loadTestData(const std::string& kTestFilePath) {
    auto data = mpPrivate->mpTestDataDao->getData(kTestFilePath);
    auto pokemonFilePath = data[0];
    auto moveFilePath = data[1];
    auto gameFilePath = data[2];

    // Load the necessary data for the test
    bool isLoad = loadData(moveFilePath, pokemonFilePath, gameFilePath);
    mpPrivate->mpPlayerMode->setTest();
    if (!isLoad) {
        return false;
    }

    std::vector<std::string> out;
    for (int i = 4; i < data.size(); i++) {
        out.push_back(data[i]);
    }

    // Run the test with the provided inputs
    mpPrivate->mpPlayerMode->runTest(out);
    return true;
}
