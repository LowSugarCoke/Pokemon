#include "pokemonBo.h"

#include <vector>
#include <set>

#include "moveEntity.h"
#include "pokemonEntity.h"

// Define a private class to hold the member variables of PokemonBo
class PokemonBoPrivate {
public:
    std::vector<MoveBo> mMoveBoVec; // Vector to store MoveBo objects
    std::vector<int> mMaxPowerPoints; // Vector to store the maximum power points of moves
    std::string mPokemonName; // Name of the Pokemon
    std::vector<TYPE> mPokemonTypeVec; // Vector to store the types of the Pokemon
    PokemonStats mPokemonStats; // Object to store the stats of the Pokemon

    std::set<ADDITIONAL_EFFECT_TYPE> mPokemonAdditionEffectTypeSet; // Set to store additional effect types
    int mMaxHp; // Maximum HP of the Pokemon
    bool mIsMyPokemon; // Flag indicating whether the Pokemon is owned by the player
};

// Default constructor for PokemonBo
PokemonBo::PokemonBo()
    : mpPrivate(std::make_unique<PokemonBoPrivate>()) // Initialize the private member using std::make_unique
{
    mpPrivate->mMaxHp = 0; // Initialize maximum HP to 0
}

// Copy constructor for PokemonBo
PokemonBo::PokemonBo(const PokemonBo& kPokemonBo)
    : mpPrivate(std::make_unique<PokemonBoPrivate>(*kPokemonBo.mpPrivate)) // Initialize the private member with a copy of the input object's private member
{
    mpPrivate->mMaxHp = 0; // Initialize maximum HP to 0
}

// Destructor for PokemonBo
PokemonBo::~PokemonBo() {}

// Set the Pokemon elements, such as name, stats, and types
void PokemonBo::setPokemonElements(const std::string& kName, const PokemonStats& kPokemonStats, const std::vector<TYPE>& kType) {
    mpPrivate->mPokemonName = kName; // Set the Pokemon name
    mpPrivate->mMaxHp = kPokemonStats.hp; // Set the maximum HP
    mpPrivate->mPokemonStats = kPokemonStats; // Set the Pokemon stats
    mpPrivate->mPokemonTypeVec = kType; // Set the Pokemon types
}

// Add move elements to the Pokemon, such as move name, stats, type, damage type, and additional effect type
void PokemonBo::addMoveElements(const std::string& kName, const MoveStats& kMoveStats, const TYPE& kType, const DAMAGE_TYPE& kDamageType,
    const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType) {
    MoveBo moveBo; // Create a MoveBo object
    moveBo.name = kName; // Set the move name
    moveBo.stats = kMoveStats; // Set the move stats
    moveBo.type = kType; // Set the move type
    moveBo.damageType = kDamageType; // Set the move damage type
    moveBo.additionalEffectType = kAdditionalEffectType; // Set the move additional effect type

    mpPrivate->mMoveBoVec.push_back(moveBo); // Add the MoveBo object to the vector
    mpPrivate->mMaxPowerPoints.push_back(moveBo.stats.powerPoint); // Add the maximum power points of the move to the vector
}

// Add HP to the Pokemon
void PokemonBo::addHp(const int& kHp) {
    mpPrivate->mPokemonStats.hp += kHp; // Increase the Pokemon's HP
    if (mpPrivate->mPokemonStats.hp > mpPrivate->mMaxHp) {
        mpPrivate->mPokemonStats.hp = mpPrivate->mMaxHp; // If the HP exceeds the maximum HP, set it to the maximum HP
    }
}

// Subtract HP from the Pokemon
void PokemonBo::minusHp(const int& kHp) {
    mpPrivate->mPokemonStats.hp -= kHp; // Decrease the Pokemon's HP
    if (mpPrivate->mPokemonStats.hp < 0) {
        mpPrivate->mPokemonStats.hp = 0; // If the HP goes below 0, set it to 0 (Pokemon fainted)
    }
}

// Check if the Pokemon has fainted (HP is 0)
bool PokemonBo::isFainting() {
    return mpPrivate->mPokemonStats.hp == 0 ? true : false; // Return true if HP is 0, false otherwise
}

// Get the Pokemon's stats
PokemonStats PokemonBo::getPokemonStats() const {
    return mpPrivate->mPokemonStats; // Return the Pokemon's stats
}

// Find a MoveBo object by move name
MoveBo PokemonBo::findMoveBoByName(const std::string kMoveName) {
    for (int i = 0; i < mpPrivate->mMoveBoVec.size(); i++) {
        if (mpPrivate->mMoveBoVec[i].name == kMoveName) {
            return mpPrivate->mMoveBoVec[i]; // Return the MoveBo object if the move name matches
        }
    }
    return {}; // Return an empty MoveBo object if no match is found
}

// Find a MoveBo object by index
MoveBo PokemonBo::findMoveBoByIndex(const int& kMonitorIndex) {
    return mpPrivate->mMoveBoVec[kMonitorIndex]; // Return the MoveBo object at the given index
}

// Get the Pokemon's types
std::vector<TYPE> PokemonBo::getPokemonTypes() const {
    return mpPrivate->mPokemonTypeVec; // Return the Pokemon's types
}

// Get the Pokemon's MoveBo objects
std::vector<MoveBo> PokemonBo::getMoveBos() const {
    return mpPrivate->mMoveBoVec; // Return the Pokemon's MoveBo objects
}

// Get the maximum HP of the Pokemon
int PokemonBo::getMaxHp() const {
    return mpPrivate->mMaxHp; // Return the maximum HP
}

// Get the current HP of the Pokemon
int PokemonBo::getHp() const {
    return mpPrivate->mPokemonStats.hp; // Return the current HP
}

// Set the Pokemon's additional effect type
void PokemonBo::setPokemonAdditionalEffectType(const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType) {
    mpPrivate->mPokemonAdditionEffectTypeSet.insert(kAdditionalEffectType); // Add the additional effect type to the set
}

// Get the Pokemon's additional effect types
std::set<ADDITIONAL_EFFECT_TYPE> PokemonBo::getPokemonAdditionalEffectType() const {
    return mpPrivate->mPokemonAdditionEffectTypeSet; // Return the Pokemon's additional effect types
}

// Get the Pokemon's name
std::string PokemonBo::getName() const {
    return mpPrivate->mPokemonName; // Return the Pokemon's name
}

// Reduce the Pokemon's speed by half
void PokemonBo::reduceHalfSpeed() {
    mpPrivate->mPokemonStats.speed /= 2; // Divide the Pokemon's speed by 2
}

// Set the flag indicating whether the Pokemon is owned by the player
void PokemonBo::checkToMyPokemon(const bool& kMyPokemon) {
    mpPrivate->mIsMyPokemon = kMyPokemon; // Set the flag value
}

// Check if the Pokemon is owned by the player
bool PokemonBo::isMyPokemon() const {
    return mpPrivate->mIsMyPokemon; // Return the flag value
}

// Subtract power points from a move
void PokemonBo::minusMovePowerPoint(const MoveBo& kMoveBo) {
    for (int i = 0; i < mpPrivate->mMoveBoVec.size(); i++) {
        if (mpPrivate->mMoveBoVec[i].name == kMoveBo.name) {
            mpPrivate->mMoveBoVec[i].stats.powerPoint--; // Decrease the power points of the move
        }
    }
}

// Get the maximum power points of the moves
std::vector<int> PokemonBo::getMaxPowerPoint() const {
    return mpPrivate->mMaxPowerPoints; // Return the maximum power points
}

// Find the index of a move by move name
int PokemonBo::findMoveIndexByName(const std::string& kMoveName) const {
    auto moveBos = mpPrivate->mMoveBoVec;
    for (int i = 0; i < moveBos.size(); i++) {
        if (moveBos[i].name == kMoveName) {
            return i; // Return the index if the move name matches
        }
    }
    // If no match is found, the function should return an int value, but it currently doesn't. Consider adding a default return statement.
    return -1; // Return -1 if no match is found (error condition)
}
