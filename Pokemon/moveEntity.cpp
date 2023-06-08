#include "moveEntity.h"


class MoveEntityPrivate {
public:
    std::string mName;   // Name of the Move
    TYPE mType;          // Type of the Move
    DAMAGE_TYPE mDamageType; // Damage type of the Move
    MoveStats mMoveStats; // Statistical attributes of the Move
    ADDITIONAL_EFFECT_TYPE mAdditionalEffectType; // Additional effect of the Move
};

// Default constructor
MoveEntity::MoveEntity()
    :mpPrivate(std::make_unique<MoveEntityPrivate>())
{
    // Initialize the name, move stats, and other attributes to default values
    mpPrivate->mName = "";
    mpPrivate->mMoveStats.accuracy = 0;
    mpPrivate->mMoveStats.power = 0;
    mpPrivate->mMoveStats.powerPoint = 0;
}

// Parameterized constructor
MoveEntity::MoveEntity(const std::string& kName, const TYPE& kType,
    const DAMAGE_TYPE& kDamageType, const MoveStats& kMoveStats,
    const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType)
    : mpPrivate(std::make_unique<MoveEntityPrivate>())
{
    // Set the name, type, damage type, move stats, and additional effect type using the provided parameters
    setName(kName);
    setType(kType);
    setDamageType(kDamageType);
    setMoveStats(kMoveStats);
    setAdditionalEffectType(kAdditionalEffectType);
}

// Copy constructor
MoveEntity::MoveEntity(const MoveEntity& kMoveEntity)
    : mpPrivate(std::make_unique<MoveEntityPrivate>(*kMoveEntity.mpPrivate))
{
    // Perform a deep copy of the private member using the unique pointer
}

// Destructor
MoveEntity::~MoveEntity() {
    // Destructor is automatically generated for the unique pointer
}

// Set the name of the move
void MoveEntity::setName(const std::string& kName) {
    mpPrivate->mName = kName;
}

// Get the name of the move
std::string MoveEntity::getName() const {
    return mpPrivate->mName;
}

// Set the type of the move
void MoveEntity::setType(const TYPE& kType) {
    mpPrivate->mType = kType;
}

// Get the type of the move
TYPE MoveEntity::getType() const {
    return mpPrivate->mType;
}

// Set the damage type of the move
void MoveEntity::setDamageType(const DAMAGE_TYPE& kDamageType) {
    mpPrivate->mDamageType = kDamageType;
}

// Get the damage type of the move
DAMAGE_TYPE MoveEntity::getDamageType() const {
    return mpPrivate->mDamageType;
}

// Set the move stats of the move
void MoveEntity::setMoveStats(const MoveStats& kMoveStats) {
    mpPrivate->mMoveStats = kMoveStats;
}

// Get the move stats of the move
MoveStats MoveEntity::getMoveStats() const {
    return mpPrivate->mMoveStats;
}

// Set the additional effect type of the move
void MoveEntity::setAdditionalEffectType(const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType) {
    mpPrivate->mAdditionalEffectType = kAdditionalEffectType;
}

// Get the additional effect type of the move
ADDITIONAL_EFFECT_TYPE MoveEntity::getAdditionalEffectType() const {
    return mpPrivate->mAdditionalEffectType;
}
