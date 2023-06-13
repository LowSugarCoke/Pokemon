#include "playerMode.h"

#include <unordered_map>
#include <QString>

#include "pokemonBo.h"
#include "pokemonMode.h"
#include "pokemonLogger.h"
#include "additionalEffectType.h"

// Map to convert potion names to their corresponding index
static  std::unordered_map<std::string, int> convertPotionToIndexMap{
    {"Potion", 0},
    {"SuperPotion", 1},
    {"HyperPotion", 2},
    {"MaxPotion", 3},
};

class PlayerModePrivate {
public:
    /**
     * Intent: Initializes the PlayerModePrivate object.
     * Pre: The parameter pPokemonMode must be a valid shared pointer to a PokemonMode object.
     * Post: A new PlayerModePrivate object is created with the provided pPokemonMode.
     * \param pPokemonMode - A shared pointer to a PokemonMode object.
     */
    PlayerModePrivate(std::shared_ptr<PokemonMode> pPokemonMode);

    /**
     * Intent: Swaps the state of the player before logging.
     * Pre: None.
     * Post: The player's state is swapped.
     */
    void swapBeforeLog();

    /**
     * Intent: Swaps the state of the player after logging.
     * Pre: None.
     * Post: The player's state is swapped.
     */
    void swapAfterLog();

    /**
     * Intent: Finds the index of a Pokemon in the player's Pokemon vector by its name.
     * Pre: The parameter kPokemonName must be a valid string representing a Pokemon's name.
     * Post: Returns the index of the Pokemon in the player's Pokemon vector. If the Pokemon is not found, returns -1.
     * \param kPokemonName - The name of the Pokemon to find.
     * \return The index of the Pokemon in the player's Pokemon vector, or -1 if not found.
     */
    int findPokemonIndexByName(const std::string& kPokemonName) const;

    /**
     * Intent: Finds a PokemonBo object in the player's Pokemon vector by its name.
     * Pre: The parameter kPokemonName must be a valid string representing a Pokemon's name.
     * Post: Returns a shared pointer to the found PokemonBo object. If the Pokemon is not found, returns a null shared pointer.
     * \param kPokemonName - The name of the Pokemon to find.
     * \return A shared pointer to the found PokemonBo object, or a null shared pointer if not found.
     */
    std::shared_ptr<PokemonBo> findPokemonBoByName(const std::string& kPokemonName) const;

    std::vector<std::shared_ptr<PokemonBo>> mpPokemonBoVec; // Vector containing shared pointers to PokemonBo objects representing the player's Pokemon.
    std::vector<std::shared_ptr<PokemonBo>> mpOppositingPokemonBoVec; // Vector containing shared pointers to PokemonBo objects representing the opponent's Pokemon.
    std::shared_ptr<PokemonMode> mpPokemonMode; // Shared pointer to a PokemonMode object.
    PokemonLogger& mLogger; // Reference to a PokemonLogger object.
    int mPokemonIndex; // Index of the current player's Pokemon.
    int mOppositingPokemonIndex; // Index of the current opponent's Pokemon.
    bool mIsTest; // Flag indicating whether the PlayerModePrivate object is used for testing purposes.
};


int PlayerModePrivate::findPokemonIndexByName(const std::string& kPokemonName) const {
    // Iterate through the player's Pokemon vector
    for (int i = 0; i < mpPokemonBoVec.size(); i++) {
        // Check if the current Pokemon's name matches the given name
        if (mpPokemonBoVec[i]->getName() == kPokemonName) {
            // Return the index of the Pokemon if found
            return i;
        }
    }

    // Return -1 if the Pokemon is not found
}

PlayerModePrivate::PlayerModePrivate(std::shared_ptr<PokemonMode> pPokemonMode)
    : mpPokemonMode(pPokemonMode)
    , mLogger(PokemonLogger::getInstance())
{
    mPokemonIndex = 0;
    mOppositingPokemonIndex = 0;
}

void PlayerModePrivate::swapBeforeLog() {
    auto name = mpPokemonBoVec[mPokemonIndex]->getName();
    mLogger.log(name + ", switch out!");
}

void PlayerModePrivate::swapAfterLog() {
    auto name = mpPokemonBoVec[mPokemonIndex]->getName();
    mLogger.log("Come back!");
    mLogger.log("Go! " + name + "!");
}

std::shared_ptr<PokemonBo> PlayerModePrivate::findPokemonBoByName(const std::string& kPokemonName) const {
    // Iterate through the player's Pokemon vector
    for (int i = 0; i < mpPokemonBoVec.size(); i++) {
        // Check if the current Pokemon's name matches the given name
        if (mpPokemonBoVec[i]->getName() == kPokemonName) {
            // Return the found PokemonBo object
            return mpPokemonBoVec[i];
        }
    }

    // Return a null shared pointer if the Pokemon is not found
}

PlayerMode::PlayerMode(std::shared_ptr<PokemonMode> pPokemonMode)
    : mpPrivate(std::make_unique<PlayerModePrivate>(pPokemonMode))
{
    // Create a new PlayerModePrivate object with the provided PokemonMode shared pointer
}

PlayerMode::PlayerMode(const PlayerMode& kPlayerMode)
    : mpPrivate(std::make_unique<PlayerModePrivate>(*kPlayerMode.mpPrivate))
{
    // Create a new PlayerModePrivate object by copying the PlayerModePrivate object from the given PlayerMode
}

PlayerMode::~PlayerMode() {
    // Destructor
}

void PlayerMode::setPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pPokemonBoVec) {
    // Set the player's Pokemon vector with the provided vector
    mpPrivate->mpPokemonBoVec = pPokemonBoVec;
    // Set the player's Pokemon in the PokemonMode object to the first Pokemon in the vector
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[0]);
}

void PlayerMode::setOppositingPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pOppositingPokemonBoVec) {
    // Set the opponent's Pokemon vector with the provided vector
    mpPrivate->mpOppositingPokemonBoVec = pOppositingPokemonBoVec;
    // Set the opponent's Pokemon in the PokemonMode object to the first Pokemon in the vector
    mpPrivate->mpPokemonMode->setOppositingPokemon(mpPrivate->mpOppositingPokemonBoVec[0]);
}

bool PlayerMode::faintingSwapPokemon(const int& kPokemonIndex) {
    // Check if the Pokemon at the given index is fainting
    if (mpPrivate->mpPokemonBoVec[kPokemonIndex]->isFainting()) {
        return false;
    }

    // Perform the swap before logging
    mpPrivate->swapBeforeLog();

    // Set the current Pokemon index to the given index
    mpPrivate->mPokemonIndex = kPokemonIndex;

    // Set the player's Pokemon in the PokemonMode object to the new Pokemon
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]);

    // Perform the swap after logging
    mpPrivate->swapAfterLog();

    return true;
}

bool PlayerMode::swapPokemon(const int& kPokemonIndex) {
    // Check if the Pokemon at the given index is fainting
    if (mpPrivate->mpPokemonBoVec[kPokemonIndex]->isFainting()) {
        return false;
    }

    // Perform the swap before logging
    mpPrivate->swapBeforeLog();

    // Set the current Pokemon index to the given index
    mpPrivate->mPokemonIndex = kPokemonIndex;

    // Set the player's Pokemon in the PokemonMode object to the new Pokemon
    mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]);

    // Perform the swap after logging
    mpPrivate->swapAfterLog();

    // Proceed to the next round without attacking
    mpPrivate->mpPokemonMode->nextRoundWithoutAttack();
    return true;
}

bool PlayerMode::swapOppositingPokemon(const int& kPokemonIndex) {
    // Check if the given Pokemon index is valid
    if (kPokemonIndex >= mpPrivate->mpOppositingPokemonBoVec.size()) {
        return false;
    }

    // Check if the Pokemon at the given index is fainting
    if (mpPrivate->mpOppositingPokemonBoVec[kPokemonIndex]->isFainting()) {
        return false;
    }

    // Set the current opponent's Pokemon index to the given index
    mpPrivate->mOppositingPokemonIndex = kPokemonIndex;

    // Set the opponent's Pokemon in the PokemonMode object to the new Pokemon
    mpPrivate->mpPokemonMode->setOppositingPokemon(mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]);

    // Set the last opposite Pokemon if the given index is 2
    if (kPokemonIndex == 2) {
        mpPrivate->mpPokemonMode->setLastOppositePokemon();
    }
    return true;
}

std::vector<std::string> PlayerMode::getPokemonsName() const {
    std::vector<std::string> data;
    auto pokemons = mpPrivate->mpPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        data.push_back(pokemons[i]->getName());
    }
    return data;
}

// Retrieve the names of the opposing player's Pokémon
std::vector<std::string> PlayerMode::getOppositingPokemonsName() const {
    std::vector<std::string> data;
    auto pokemons = mpPrivate->mpOppositingPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        data.push_back(pokemons[i]->getName());
    }
    return data;
}

// Retrieve the current and maximum HP values of the player's Pokémon
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

// Retrieve the current and maximum HP values of the opposing player's Pokémon
std::vector<std::pair<int, int>> PlayerMode::getOppositingPokemonsHp() const {
    std::vector<std::pair<int, int>> data;
    auto pokemons = mpPrivate->mpOppositingPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        auto currentHp = pokemons[i]->getPokemonStats().hp;
        auto maxHp = pokemons[i]->getMaxHp();
        std::pair<int, int> hpPair{ currentHp, maxHp };

        data.push_back(hpPair);
    }
    return data;
}

// Retrieve the additional effects of the opposing player's current Pokémon
std::set<std::string> PlayerMode::getOppositingPokemonAdditionalEffect() const {
    std::set<std::string> data;
    auto currentPokemon = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex];
    for (auto additionalEffect : currentPokemon->getPokemonAdditionalEffectType()) {
        data.insert(effectTypeToString(additionalEffect));
    }
    return data;
}

// Retrieve the additional effects of the current player's Pokémon
std::set<std::string> PlayerMode::getCurrentPokemonAdditionalEffect() const {
    std::set<std::string> data;
    auto currentPokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
    for (auto additionalEffect : currentPokemon->getPokemonAdditionalEffectType()) {
        data.insert(effectTypeToString(additionalEffect));
    }
    return data;
}

// Perform a battle between the player's Pokémon and the opposing Pokémon
void PlayerMode::battle(const int& kMoveIndex, const int& kOppositeIndex) {
    if (!mpPrivate->mIsTest) {
        mpPrivate->mpPokemonMode->nextRound(kMoveIndex);
    }
    else {
        mpPrivate->mpPokemonMode->nextRound(kMoveIndex, kOppositeIndex);
    }
    if (mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->isFainting()) {
        swapOppositingPokemon(mpPrivate->mOppositingPokemonIndex + 1);
    }
    if (isWinOrLose() == 1) {
        mpPrivate->mLogger.log("You win");
    }
    else if (isWinOrLose() == 2) {
        mpPrivate->mLogger.log("You lose");
    }
}

// Retrieve the index of the current player's Pokémon
int PlayerMode::getCurrentPokemonIndex() const {
    return mpPrivate->mPokemonIndex;
}

// Retrieve the index of the opposing player's Pokémon
int PlayerMode::getOppositingPokemonIndex() const {
    return mpPrivate->mOppositingPokemonIndex;
}

// Retrieve the names of the moves available for the current player's Pokémon
std::vector<std::string> PlayerMode::getCurrentPokemonMoves() const {
    std::vector<std::string> moves;
    auto moveBo = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]->getMoveBos();
    for (int i = 0; i < moveBo.size(); i++) {
        moves.push_back(moveBo[i].name);
    }
    return moves;
}

// Use a potion on the specified Pokémon
void PlayerMode::usePotion(const int& kPokemonIndex, const int& kPotionIndex) {
    mpPrivate->mpPokemonMode->usePotion(mpPrivate->mpPokemonBoVec[kPokemonIndex], kPotionIndex);
    mpPrivate->mpPokemonMode->nextRoundWithoutAttack();
}

// Retrieve the names of the available potions
std::vector<std::string> PlayerMode::getPotionsName() const {
    return mpPrivate->mpPokemonMode->getPotionsName();
}

// Retrieve the fainting status of the player's Pokémon
std::vector<bool> PlayerMode::getPokemonsFaintStatus() const {
    std::vector<bool> faintVec;

    auto pokemons = mpPrivate->mpPokemonBoVec;
    for (int i = 0; i < pokemons.size(); i++) {
        if (pokemons[i]->isFainting()) {
            faintVec.push_back(true);
        }
        else {
            faintVec.push_back(false);
        }
    }
    return faintVec;
}

// Determine the win or lose status of the battle
// 0: not yet, 1: win, 2: lose
int PlayerMode::isWinOrLose() const {
    int opposingFaintCount = 0;
    for (int i = 0; i < mpPrivate->mpOppositingPokemonBoVec.size(); i++) {
        opposingFaintCount += mpPrivate->mpOppositingPokemonBoVec[i]->isFainting();
    }

    if (opposingFaintCount == mpPrivate->mpOppositingPokemonBoVec.size()) {
        return 1; // win
    }

    int myFaintCount = 0;
    for (int i = 0; i < mpPrivate->mpPokemonBoVec.size(); i++) {
        myFaintCount += mpPrivate->mpPokemonBoVec[i]->isFainting();
    }
    if (myFaintCount == mpPrivate->mpOppositingPokemonBoVec.size()) {
        return 2; // lose
    }

    return 0; // not yet
}

// Retrieve the current HP of the opposing player's Pokémon
int PlayerMode::getOppositingPokemonHp() const {
    return mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->getHp();
}

// Retrieve the types of moves available for the current player's Pokémon
std::vector<std::string> PlayerMode::getCurrentPokemonMoveTypes() const {
    std::vector<std::string> data;
    auto pokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
    auto moveBos = pokemon->getMoveBos();
    for (auto move : moveBos) {
        data.push_back(reverseTypeMap[move.type]);
    }
    return data;
}

// Retrieve the power points of moves available for the current player's Pokémon
std::vector<int> PlayerMode::getCurrentPokemonPowerPoints() const {
    std::vector<int> data;
    auto pokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
    auto moveBos = pokemon->getMoveBos();
    for (auto move : moveBos) {
        data.push_back(move.stats.powerPoint);
    }
    return data;
}

// Retrieve the maximum power points of moves available for the current player's Pokémon
std::vector<int> PlayerMode::getCurrentPokemonMaxPowerPoints() const {
    return mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]->getMaxPowerPoint();
}

// Set the test mode for the player
void PlayerMode::setTest() {
    mpPrivate->mpPokemonMode->setTest();
    mpPrivate->mIsTest = true;
}

void PlayerMode::runTest(const std::vector<std::string>& kTestData) {
    mpPrivate->mOppositingPokemonIndex = 0;
    mpPrivate->mPokemonIndex = 0;
    for (int i = 0; i < kTestData.size(); i++) {
        // Check if the opposing Pokémon is fainting and swap if necessary
        if (mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->isFainting()) {
            swapOppositingPokemon(mpPrivate->mOppositingPokemonIndex + 1);
        }

        // Process the test data based on the commands
        if (kTestData[i] == "Battle") {
            i++;
            auto myMoveIndex = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]->findMoveIndexByName(kTestData[i]);
            i++;
            auto oppositeMoveIndex = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->findMoveIndexByName(kTestData[i]);
            mpPrivate->mpPokemonMode->nextRound(myMoveIndex, oppositeMoveIndex);
        }
        else if (kTestData[i] == "Bag") {
            i++;
            auto potionIndex = convertPotionToIndexMap[kTestData[i]];
            i++;
            auto pokemonBo = mpPrivate->findPokemonBoByName(kTestData[i]);
            mpPrivate->mpPokemonMode->usePotion(pokemonBo, potionIndex);
            i++;
            auto oppositeMoveIndex = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->findMoveIndexByName(kTestData[i]);
            mpPrivate->mpPokemonMode->nextRoundWithoutAttack(oppositeMoveIndex);
        }
        else if (kTestData[i] == "Pokemon") {
            i++;
            auto pokemonIndex = mpPrivate->findPokemonIndexByName(kTestData[i]);

            // Skip the action if the selected Pokémon is already fainting
            if (mpPrivate->mpPokemonBoVec[pokemonIndex]->isFainting()) {
                continue;
            }

            // Swap the player's active Pokémon
            mpPrivate->swapBeforeLog();
            mpPrivate->mPokemonIndex = pokemonIndex;
            mpPrivate->mpPokemonMode->setMyPokemon(mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex]);
            mpPrivate->swapAfterLog();

            i++;
            auto oppositeMoveIndex = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex]->findMoveIndexByName(kTestData[i]);
            mpPrivate->mpPokemonMode->nextRoundWithoutAttack(oppositeMoveIndex);
        }
        else if (kTestData[i] == "Status") {
            // Retrieve status information of both player's Pokémon
            auto myPokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
            auto name = myPokemon->getName();
            auto myHp = myPokemon->getHp();
            auto effect = myPokemon->getPokemonAdditionalEffectType();
            std::string effectStr = "";
            for (auto& e : effect) {
                effectStr += effectTypeToString(e);
            }

            auto oppositePokemon = mpPrivate->mpOppositingPokemonBoVec[mpPrivate->mOppositingPokemonIndex];
            auto oppositeName = oppositePokemon->getName();
            auto oppositeHp = oppositePokemon->getHp();
            auto oppositeEffect = oppositePokemon->getPokemonAdditionalEffectType();
            std::string oppositeEffectStr = "";
            for (auto& e : oppositeEffect) {
                oppositeEffectStr += effectTypeToString(e);
            }

            // Log the status information
            std::string mes = name + " " + std::to_string(myHp) + " " + effectStr + " " + oppositeName + " " + std::to_string(oppositeHp) + " " + oppositeEffectStr;
            mpPrivate->mLogger.log(mes);
        }
        else if (kTestData[i] == "Check") {
            // Check the moves and their power points of the current player's Pokémon
            auto myPokemon = mpPrivate->mpPokemonBoVec[mpPrivate->mPokemonIndex];
            auto moveBos = myPokemon->getMoveBos();
            std::string meg = "";
            for (int i = 0; i < moveBos.size(); i++) {
                meg += moveBos[i].name + " " + std::to_string(moveBos[i].stats.powerPoint) + " ";
            }

            // Log the move information
            mpPrivate->mLogger.log(meg);
        }
    }

    // Check the win or lose status and log the result
    if (isWinOrLose() == 1) {
        mpPrivate->mLogger.log("You win");
    }
    else if (isWinOrLose() == 2) {
        mpPrivate->mLogger.log("You lose");
    }
}
