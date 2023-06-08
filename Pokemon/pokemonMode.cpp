#include "pokemonMode.h"

#include <random>

#include "pokemonBo.h"
#include "damageMode.h"
#include "additionalEffectMode.h"
#include "pokemonLogger.h"
#include "potionMode.h"

class PokemonModePrivate {
public:

    /**
     * Constructor
     *
     * Intent: Creates an instance of PokemonModePrivate.
     * Pre: -
     * Post: PokemonModePrivate instance is created with the given parameters.
     * \param pDamageMode Pointer to the DamageMode object.
     * \param pAdditionalEffectMode Pointer to the AdditionalEffectMode object.
     * \param pPotionMode Pointer to the PotionMode object.
     */
    PokemonModePrivate(std::shared_ptr<DamageMode> pDamageMode, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode, \
        std::shared_ptr<PotionMode> pPotionMode);

    /**
     * Intent: Calculates the damage inflicted by a move on two Pokemon.
     * Pre: Pointers pAPokemonBo and pBPokemonBo are valid and non-null. kMoveBo is a valid MoveBo object.
     * Post: Damage is calculated and the necessary effects are applied to the Pokemon.
     * \param pAPokemonBo
     * \param pBPokemonBo
     * \param kMoveBo
     */
    void damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const MoveBo& kMoveBo);

    /**
     * Intent: Retrieves a random move for the opposing Pokemon.
     * Pre: Pointer pOppositingPokemonBo is a valid and non-null PokemonBo object.
     * Post: A random move for the opposing Pokemon is retrieved.
     * \param pOppositingPokemonBo
     * \return MoveBo object representing the random move.
     */
    MoveBo getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo);

    /**
     * Intent: Logs the attack performed by the player's Pokemon.
     * Pre: kMoveBo is a valid MoveBo object.
     * Post: The attack is logged.
     * \param kMoveBo
     */
    void myAttackLog(const MoveBo& kMoveBo);

    /**
     * Intent: Logs the attack performed by the opposing Pokemon.
     * Pre: kMoveBo is a valid MoveBo object.
     * Post: The attack is logged.
     * \param kMoveBo
     */
    void oppositingAttackLog(const MoveBo& kMoveBo);

    /**
     * Intent: Logs the message when the opposing Pokemon misses its attack.
     * Pre: Pointer mpOppositingPokemonBo is a valid and non-null PokemonBo object.
     * Post: The message is logged.
     * \param mpOppositingPokemonBo
     */
    void missingLog(std::shared_ptr<PokemonBo> mpOppositingPokemonBo);

    /**
     * Intent: Logs the message when a Pokemon is paralyzed.
     * Pre: Pointer pPokemonBo is a valid and non-null PokemonBo object.
     * Post: The message is logged.
     * \param pPokemonBo
     */
    void paralyzedLog(std::shared_ptr<PokemonBo> pPokemonBo);

    std::shared_ptr<PokemonBo> mpPokemonBo;
    std::shared_ptr<PokemonBo> mpOppositingPokemonBo;
    std::shared_ptr<DamageMode> mpDamageMode;
    std::shared_ptr<AdditionalEffectMode> mpAdditionalEffectMode;
    std::shared_ptr<PotionMode> mpPotionMode;
    PokemonLogger& mLogger;

    bool mIsTest;
    bool mIsLastOppositePokemon;
};

PokemonModePrivate::PokemonModePrivate(std::shared_ptr<DamageMode> pDamageMode,
    std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode,
    std::shared_ptr<PotionMode> pPotionMode)
    : mpDamageMode(pDamageMode) // Set the DamageMode object
    , mpAdditionalEffectMode(pAdditionalEffectMode) // Set the AdditionalEffectMode object
    , mpPotionMode(pPotionMode) // Set the PotionMode object
    , mIsTest(false) // Set the test flag to false
    , mIsLastOppositePokemon(false) // Set the flag for the last opposing Pokemon to false
    , mLogger(PokemonLogger::getInstance()) // Get the instance of the PokemonLogger
{
}

void PokemonModePrivate::myAttackLog(const MoveBo& kMoveBo) {
    auto name = mpPokemonBo->getName(); // Get the name of the player's Pokemon
    mLogger.log(name + " used " + kMoveBo.name + "!"); // Log the attack of the player's Pokemon
}

void PokemonModePrivate::oppositingAttackLog(const MoveBo& kMoveBo) {
    auto name = mpOppositingPokemonBo->getName(); // Get the name of the opposing Pokemon
    mLogger.log("The opposing " + name + " used " + kMoveBo.name + "!"); // Log the attack of the opposing Pokemon
}

void PokemonModePrivate::missingLog(std::shared_ptr<PokemonBo> mpOppositingPokemonBo) {
    auto name = mpOppositingPokemonBo->getName(); // Get the name of the opposing Pokemon
    mLogger.log(name + " avoided the attack!"); // Log the message that the opposing Pokemon avoided the attack
}

void PokemonModePrivate::paralyzedLog(std::shared_ptr<PokemonBo> pPokemonBo) {
    auto name = pPokemonBo->getName(); // Get the name of the paralyzed Pokemon
    mLogger.log(name + " is paralyzed!"); // Log the message that the Pokemon is paralyzed
    mLogger.log("It can't move!"); // Log the message that the paralyzed Pokemon can't move
}

void PokemonModePrivate::damage(std::shared_ptr<PokemonBo> pAPokemonBo, std::shared_ptr<PokemonBo> pBPokemonBo, const MoveBo& kMoveBo) {
    if (mpDamageMode->isMissing(pAPokemonBo, pBPokemonBo, kMoveBo)) { // Check if the attack missed
        missingLog(pBPokemonBo); // Log the message that the opposing Pokemon avoided the attack
        return;
    }

    if (mpAdditionalEffectMode->unableToMove(pAPokemonBo)) { // Check if the attacking Pokemon is unable to move
        paralyzedLog(pAPokemonBo); // Log the message that the attacking Pokemon is paralyzed
        return;
    }

    if (pAPokemonBo->isMyPokemon()) {
        myAttackLog(kMoveBo); // Log the attack of the player's Pokemon
    }
    else {
        oppositingAttackLog(kMoveBo); // Log the attack of the opposing Pokemon
    }

    int damage = mpDamageMode->damageCalculate(pAPokemonBo, pBPokemonBo, kMoveBo); // Calculate the damage
    pBPokemonBo->minusHp(damage); // Reduce the HP of the opposing Pokemon

    mpAdditionalEffectMode->addIfMoveHasAdditionalEffect(pBPokemonBo, kMoveBo); // Apply additional effects if the move has any
}

MoveBo PokemonModePrivate::getRandomMoveBo(std::shared_ptr<PokemonBo> pOppositingPokemonBo) {
    auto moveBos = pOppositingPokemonBo->getMoveBos(); // Get the available moves of the opposing Pokemon

    std::random_device rd; // Obtain a random seed from the device
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, moveBos.size()); // Create a uniform distribution for random move selection

    int randomNumber = distrib(gen); // Generate a random number within the range of available moves

    return moveBos[randomNumber - 1]; // Return the randomly selected move
}

PokemonMode::PokemonMode(std::shared_ptr<DamageMode> pDamageMode,
    std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode,
    std::shared_ptr<PotionMode> pPotionMode)
    : mpPrivate(std::make_unique<PokemonModePrivate>(pDamageMode, pAdditionalEffectMode, pPotionMode)) // Create a unique pointer to PokemonModePrivate and initialize it with the provided objects
{
}

PokemonMode::PokemonMode(const PokemonMode& kPokemonMode)
    : mpPrivate(std::make_unique<PokemonModePrivate>(*kPokemonMode.mpPrivate)) // Create a deep copy of the PokemonModePrivate object
{
}

PokemonMode::~PokemonMode() {
}

void PokemonMode::setMyPokemon(std::shared_ptr<PokemonBo> pMyPokemon) {
    mpPrivate->mpPokemonBo = pMyPokemon; // Set the player's Pokemon
}

void PokemonMode::setOppositingPokemon(std::shared_ptr<PokemonBo> pOppositingPokemon) {
    mpPrivate->mpOppositingPokemonBo = pOppositingPokemon; // Set the opposing Pokemon
}

void PokemonMode::nextRound(const int& kMoveIndex, const int& kOppositeIndex) {
    MoveBo oppositingMove;
    if (!mpPrivate->mIsTest) {
        oppositingMove = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo); // Get a random move for the opposing Pokemon
    }
    else {
        oppositingMove = mpPrivate->mpOppositingPokemonBo->findMoveBoByIndex(kOppositeIndex); // Use the specified move for the opposing Pokemon in the test mode
    }

    auto moveBo = mpPrivate->mpPokemonBo->findMoveBoByIndex(kMoveIndex); // Get the move chosen by the player

    mpPrivate->mpPokemonBo->minusMovePowerPoint(moveBo); // Reduce the move's power points for the player's Pokemon

    if (mpPrivate->mpPokemonBo->getPokemonStats().speed >= mpPrivate->mpOppositingPokemonBo->getPokemonStats().speed) {
        mpPrivate->damage(mpPrivate->mpPokemonBo, mpPrivate->mpOppositingPokemonBo, moveBo); // Player's Pokemon attacks first
        if (mpPrivate->mpOppositingPokemonBo->isFainting()) {
            mpPrivate->mLogger.log("The opposing " + mpPrivate->mpOppositingPokemonBo->getName() + " fainted!"); // Log the message that the opposing Pokemon fainted
            if (!mpPrivate->mIsLastOppositePokemon) {
                mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo); // Apply additional damage after the battle for the player's Pokemon
                mpPrivate->mLogger.addTurn(); // Increment the turn count
            }
            return;
        }
        mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove); // Opposing Pokemon counterattacks
    }
    else {
        mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove); // Opposing Pokemon attacks first
        if (mpPrivate->mpPokemonBo->isFainting()) {
            mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo); // Apply additional damage after the battle for the opposing Pokemon
            mpPrivate->mLogger.addTurn(); // Increment the turn count
            return;
        }
        mpPrivate->damage(mpPrivate->mpPokemonBo, mpPrivate->mpOppositingPokemonBo, moveBo); // Player's Pokemon counterattacks
    }
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo); // Apply additional damage after the battle for the player's Pokemon
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo); // Apply additional damage after the battle for the opposing Pokemon

    mpPrivate->mLogger.addTurn(); // Increment the turn count
}

void PokemonMode::nextRoundWithoutAttack(const int& kOppositingIndex) {
    MoveBo oppositingMove;
    if (!mpPrivate->mIsTest) {
        oppositingMove = mpPrivate->getRandomMoveBo(mpPrivate->mpOppositingPokemonBo); // Get a random move for the opposing Pokemon
    }
    else {
        oppositingMove = mpPrivate->mpOppositingPokemonBo->findMoveBoByIndex(kOppositingIndex); // Use the specified move for the opposing Pokemon in the test mode
    }

    mpPrivate->damage(mpPrivate->mpOppositingPokemonBo, mpPrivate->mpPokemonBo, oppositingMove); // Opposing Pokemon attacks
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpPokemonBo); // Apply additional damage after the battle for the player's Pokemon
    mpPrivate->mpAdditionalEffectMode->additionalDamageAfterBattle(mpPrivate->mpOppositingPokemonBo); // Apply additional damage after the battle for the opposing Pokemon

    mpPrivate->mLogger.addTurn(); // Increment the turn count
}

void PokemonMode::usePotion(std::shared_ptr<PokemonBo> pPokemonBo, const int& kPotionIndex) {
    mpPrivate->mpPotionMode->addHp(pPokemonBo, kPotionIndex); // Increase the HP of the Pokemon using a potion
}

std::vector<std::string> PokemonMode::getPotionsName() const {
    return mpPrivate->mpPotionMode->getPotionsName(); // Get the names of available potions
}

void PokemonMode::setTest() {
    mpPrivate->mpDamageMode->setTest(); // Enable test mode for the DamageMode
    mpPrivate->mpAdditionalEffectMode->setTest(); // Enable test mode for the AdditionalEffectMode
    mpPrivate->mIsTest = true; // Set the test flag to true
}

void PokemonMode::setLastOppositePokemon() {
    mpPrivate->mIsLastOppositePokemon = true; // Set the flag for the last opposing Pokemon to true
}
