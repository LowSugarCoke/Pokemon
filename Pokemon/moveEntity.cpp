#include "moveEntity.h"


class MoveEntityPrivate {
public:
    std::string mName;   // Name of the Move
    TYPE mType;          // Type of the Move
    DAMAGE_TYPE mDamageType; // Damage type of the Move
    MoveStats mMoveStats; // Statistical attributes of the Move
    ADDITIONAL_EFFECT_TYPE mAdditionalEffectType; // Additional effect of the Move
};

MoveEntity::MoveEntity()
    :mpPrivate(std::make_unique<MoveEntityPrivate>())
{
    mpPrivate->mName = "";
    mpPrivate->mMoveStats.accuracy = 0;
    mpPrivate->mMoveStats.power = 0;
    mpPrivate->mMoveStats.powerPoint = 0;
}

MoveEntity::MoveEntity(const std::string& kName, const TYPE& kType,
    const DAMAGE_TYPE& kDamageType, const MoveStats& kMoveStats,
    const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType)
    : mpPrivate(std::make_unique<MoveEntityPrivate>())
{
    setName(kName); // Set name of the Move
    setType(kType); // Set type of the Move
    setDamageType(kDamageType); // Set damage type of the Move
    setMoveStats(kMoveStats); // Set statistical attributes of the Move
    setAdditionalEffectType(kAdditionalEffectType); // Set additional effect of the Move
}

MoveEntity::MoveEntity(const MoveEntity& kMoveEntity)
    : mpPrivate(std::make_unique<MoveEntityPrivate>(*kMoveEntity.mpPrivate))
{
}


MoveEntity::~MoveEntity() {

}

void MoveEntity::setName(const std::string& kName) {
    mpPrivate->mName = kName;
}


std::string MoveEntity::getName() const {
    return mpPrivate->mName;
}


void MoveEntity::setType(const TYPE& kType) {
    mpPrivate->mType = kType;
}


TYPE MoveEntity::getType() const {
    return mpPrivate->mType;
}


void MoveEntity::setDamageType(const DAMAGE_TYPE& kDamageType) {
    mpPrivate->mDamageType = kDamageType;
}


DAMAGE_TYPE MoveEntity::getDamageType() const {
    return mpPrivate->mDamageType;
}


void MoveEntity::setMoveStats(const MoveStats& kMoveStats) {
    mpPrivate->mMoveStats = kMoveStats;
}


MoveStats MoveEntity::getMoveStats() const {
    return mpPrivate->mMoveStats;
}

void MoveEntity::setAdditionalEffectType(const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType) {
    mpPrivate->mAdditionalEffectType = kAdditionalEffectType;
}

ADDITIONAL_EFFECT_TYPE MoveEntity::getAdditionalEffectType() const {
    return mpPrivate->mAdditionalEffectType;
}
