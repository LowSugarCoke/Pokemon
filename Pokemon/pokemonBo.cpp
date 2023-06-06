#include "pokemonBo.h"

#include <vector>

#include "moveEntity.h"
#include "pokemonEntity.h"

struct MoveBo {
    std::string mName;   // Name of the Move
    TYPE mType;          // Type of the Move
    DAMAGE_TYPE mDamageType; // Damage type of the Move
    MoveStats mStats; // Statistical attributes of the Move
    ADDITIONAL_EFFECT_TYPE mAdditionalEffectType; // Additional effect of the Move
};

class PokemonBoPrivate {
public:
    std::vector<MoveBo> mMoveBoVec;

    std::string mPokemonName;
    std::vector<TYPE> mPokemonTypeVec;
    PokemonStats mPokemonStats;

    int mMaxHp;
};

PokemonBo::PokemonBo()
    :mpPrivate(std::make_unique<PokemonBoPrivate>())
{
    mpPrivate->mMaxHp = 0;
}

PokemonBo::PokemonBo(const PokemonBo& kPokemonBo)
    : mpPrivate(std::make_unique<PokemonBoPrivate>(*kPokemonBo.mpPrivate))
{
    mpPrivate->mMaxHp = 0;
}

PokemonBo::~PokemonBo() {}



void PokemonBo::setPokemonElements(const std::string& kName, const PokemonStats& kPokemonStats, const std::vector<TYPE>& kType) {
    mpPrivate->mPokemonName = kName;
    mpPrivate->mMaxHp = kPokemonStats.hp;
    mpPrivate->mPokemonStats = kPokemonStats;
    mpPrivate->mPokemonTypeVec = kType;
}
void PokemonBo::addMoveElements(const std::string& kName, const MoveStats& kMoveStats, const TYPE& kType, const DAMAGE_TYPE& kDamageType
    , const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType) {
    MoveBo moveBo;
    moveBo.mName = kName;
    moveBo.mStats = kMoveStats;
    moveBo.mType = kType;
    moveBo.mDamageType = kDamageType;
    moveBo.mAdditionalEffectType = kAdditionalEffectType;

    mpPrivate->mMoveBoVec.push_back(moveBo);
}

void PokemonBo::addHp(const int& kHp) {
    mpPrivate->mPokemonStats.hp += kHp;
    if (mpPrivate->mPokemonStats.hp > mpPrivate->mMaxHp) {
        mpPrivate->mPokemonStats.hp = mpPrivate->mMaxHp;
    }
}
void PokemonBo::minusHp(const int& kHp) {
    mpPrivate->mPokemonStats.hp -= kHp;
    if (mpPrivate->mPokemonStats.hp < 0) {
        mpPrivate->mPokemonStats.hp = 0;
    }
}

bool PokemonBo::isFainting() {
    return mpPrivate->mPokemonStats.hp == 0 ? true : false;
}


PokemonStats PokemonBo::getPokemonStats() const {
    return mpPrivate->mPokemonStats;
}
