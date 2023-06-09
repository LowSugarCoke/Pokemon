#include "damageMode.h"

#include <random>
#include <algorithm>

#include "pokemonBo.h"
#include "pokemonTypeChart.h"
#include "pokemonLogger.h"

const float kLevel = 50.0;  // The level used in damage calculation
class DamageModePrivate {
public:
    /**
     * Constructor for DamageModePrivate.
     *
     * Intent: Initialize a new instance of the DamageModePrivate class.
     * Pre: None.
     * Post: An instance of DamageModePrivate is created.
     */
    DamageModePrivate();

    /**
     * Generates a random value for determining critical hits.
     *
     * Intent: Generate a random value to determine if a move is a critical hit.
     * Pre: None.
     * Post: Return a random value for determining critical hits.
     * \return The generated random value for critical hits.
     */
    float getCriticalRandom();

    /**
     * Calculates the same type attack bonus for a move.
     *
     * Intent: Calculate the same type attack bonus for a move based on the attacker's type.
     * Pre: kMoveBo and pPokemonBo are valid objects.
     * Post: Return the same type attack bonus for the move.
     * \param kMoveBo The move for which to calculate the same type attack bonus.
     * \param pPokemonBo The attacking Pokémon.
     * \return The same type attack bonus for the move.
     */
    float getSameTypeAttackBonus(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);

    /**
     * Calculates the effectiveness multiplier based on move type and target Pokémon types.
     *
     * Intent: Calculate the effectiveness multiplier of a move based on its type and the target Pokémon's types.
     * Pre: kMoveBo and pTargetPokemonBo are valid objects.
     * Post: Return the effectiveness multiplier of the move.
     * \param kMoveBo The move for which to calculate the effectiveness multiplier.
     * \param pTargetPokemonBo The target Pokémon.
     * \return The effectiveness multiplier of the move.
     */
    float getType(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pTargetPokemonBo);

    /**
     * Retrieves the attack stat for the Pokémon based on the move's damage type.
     *
     * Intent: Retrieve the appropriate attack stat of the Pokémon based on the move's damage type.
     * Pre: kMoveBo and pPokemonBo are valid objects.
     * Post: Return the corresponding attack stat of the Pokémon.
     * \param kMoveBo The move for which to retrieve the attack stat.
     * \param pPokemonBo The attacking Pokémon.
     * \return The attack stat of the Pokémon.
     */
    float getAttack(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);

    /**
     * Retrieves the defense stat for the Pokémon based on the move's damage type.
     *
     * Intent: Retrieve the appropriate defense stat of the Pokémon based on the move's damage type.
     * Pre: kMoveBo and pPokemonBo are valid objects.
     * Post: Return the corresponding defense stat of the Pokémon.
     * \param kMoveBo The move for which to retrieve the defense stat.
     * \param pPokemonBo The defending Pokémon.
     * \return The defense stat of the Pokémon.
     */
    float getDefense(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);

    /**
     * Logs a message based on the type effectiveness.
     *
     * Intent: Log a message indicating the effectiveness of a move against the target Pokémon.
     * Pre: kType is a valid type effectiveness value.
     * Post: A log message is created based on the type effectiveness.
     * \param kType The type effectiveness value.
     */
    void typeLog(const float& kType);
    PokemonLogger& mLogger;
    bool mIsTest;
};


DamageModePrivate::DamageModePrivate()
    : mLogger(PokemonLogger::getInstance())
    , mIsTest(false)
{
}

void DamageModePrivate::typeLog(const float& kType) {
    static const float epsilon = 0.001; // A small value used for comparison
    if (std::abs(kType - 2.0) < epsilon || kType > 2.0) {
        mLogger.log("It's super effective!");  // Log if the move is super effective
    }
    else if (std::abs(kType - 0.5) < epsilon) {
        mLogger.log("It's not very effective...");  // Log if the move is not very effective
    }
    else if (std::abs(kType - 0.0) < epsilon) {
        mLogger.log("It's not effective!");  // Log if the move is not effective
    }
}

float DamageModePrivate::getCriticalRandom() {
    if (mIsTest) {
        return 1.0;  // In test mode, critical hits are disabled, so return 1.0
    }

    std::random_device rd;  // Generate a random seed
    std::mt19937 gen(rd()); // Create a random number engine using the seed
    std::uniform_int_distribution<> distrib(1, 10);  // Generate random numbers between 1 and 10 (inclusive)

    int randomNumber = distrib(gen);  // Generate a random number

    if (randomNumber == 1) {
        mLogger.log("A critical hit!");  // Log if it's a critical hit
        return 1.5;  // Return the critical hit multiplier
    }
    else {
        return 1;  // Return the normal multiplier
    }
}

float DamageModePrivate::getSameTypeAttackBonus(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
    auto types = pPokemonBo->getPokemonTypes();  // Get the types of the Pokemon
    for (int i = 0; i < types.size(); i++) {
        if (kMoveBo.type == types[i]) {
            return 1.5;  // If the move type matches the Pokemon's type, return the same type attack bonus
        }
    }
    return 1;  // If there is no match, return the normal multiplier
}

float DamageModePrivate::getType(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pTargetPokemonBo) {
    float cnt = 1.0;
    auto types = pTargetPokemonBo->getPokemonTypes();  // Get the types of the target Pokemon
    for (int i = 0; i < types.size(); i++) {
        auto r = static_cast<int>(kMoveBo.type);
        auto c = static_cast<int>(types[i]);
        cnt *= kEffectivenessRate[static_cast<int>(kMoveBo.type)][static_cast<int>(types[i])];  // Get the effectiveness rate from the type chart
    }
    return cnt;  // Return the combined type effectiveness multiplier
}

float DamageModePrivate::getAttack(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
    if (kMoveBo.damageType == DAMAGE_TYPE::PHYSICAL) {
        return pPokemonBo->getPokemonStats().attack;  // Return the physical attack stat of the Pokemon
    }
    else if (kMoveBo.damageType == DAMAGE_TYPE::SPECIAL) {
        return pPokemonBo->getPokemonStats().specialAttack;  // Return the special attack stat of the Pokemon
    }
    else {
        return 0;  // Return 0 if the move type is not physical or special
    }
}

float DamageModePrivate::getDefense(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
    if (kMoveBo.damageType == DAMAGE_TYPE::PHYSICAL) {
        return pPokemonBo->getPokemonStats().defense;  // Return the physical defense stat of the Pokemon
    }
    else if (kMoveBo.damageType == DAMAGE_TYPE::SPECIAL) {
        return pPokemonBo->getPokemonStats().specialDefence;  // Return the special defense stat of the Pokemon
    }
    else {
        return 0;  // Return 0 if the move type is not physical or special
    }
}

DamageMode::DamageMode()
    :mpPrivate(std::make_unique<DamageModePrivate>())
{
}

DamageMode::DamageMode(const DamageMode& kDamageMode)
    : mpPrivate(std::make_unique<DamageModePrivate>(*kDamageMode.mpPrivate))
{
}

DamageMode::~DamageMode() {
}

int DamageMode::damageCalculate(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const MoveBo& kMoveBo) {
    // Reference: https://bulbapedia.bulbagarden.net/wiki/Damage

    float damage = 0.0;

    if (kMoveBo.damageType == DAMAGE_TYPE::STATUS) {
        return 0.0;  // If the move is a status move, return 0 damage
    }

    float power = kMoveBo.stats.power;
    float atack = mpPrivate->getAttack(kMoveBo, pMyPokemonBo);
    float defence = mpPrivate->getDefense(kMoveBo, pTargetPokemonBo);
    float critical = mpPrivate->getCriticalRandom();
    float STAB = mpPrivate->getSameTypeAttackBonus(kMoveBo, pMyPokemonBo);
    float type = mpPrivate->getType(kMoveBo, pTargetPokemonBo);

    // Calculate the damage using the damage formula
    damage = (((2.0 * kLevel + 10.0) / 250.0) * power * (atack / defence) + 2.0) * critical * STAB * type;

    mpPrivate->typeLog(type);  // Log the type effectiveness

    return static_cast<int>(damage);
}

bool DamageMode::isMissing(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const MoveBo& kMoveBo) {
    if (mpPrivate->mIsTest) {
        return false;  // In test mode, missing is disabled, so return false
    }
    auto accuracy = kMoveBo.stats.accuracy;  // Get the accuracy of the move
    auto targetSpeed = pTargetPokemonBo->getPokemonStats().speed;  // Get the speed of the target Pokemon

    static const double totalStatPoints = 500.0;  // The total number of stat points used for calculation (adjust based on game settings)
    double dodgeChance = static_cast<double>(targetSpeed - accuracy) / totalStatPoints;  // Calculate the dodge chance
    dodgeChance = std::max(0.0, std::min(1.0, dodgeChance));  // Ensure the dodge chance is within the range [0, 1]

    // Create a random number generator
    static std::default_random_engine rng(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Generate a random number and check if it is less than dodgeChance
    return dist(rng) < dodgeChance;  // Return true if the move misses, false otherwise
}

void DamageMode::setTest() {
    mpPrivate->mIsTest = true;  // Enable test mode
}
