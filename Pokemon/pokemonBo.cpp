#include "pokemonBo.h"

#include <vector>
#include <set>

#include "moveEntity.h"
#include "pokemonEntity.h"



class PokemonBoPrivate {
public:
    std::vector<MoveBo> mMoveBoVec;

    std::string mPokemonName;
    std::vector<TYPE> mPokemonTypeVec;
    PokemonStats mPokemonStats;
    std::set<ADDITIONAL_EFFECT_TYPE> mPokemonAdditionEffectTypeSet;
    int mMaxHp;
    bool mIsMyPokemon;
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
    moveBo.name = kName;
    moveBo.stats = kMoveStats;
    moveBo.type = kType;
    moveBo.damageType = kDamageType;
    moveBo.additionalEffectType = kAdditionalEffectType;

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


MoveBo PokemonBo::findMoveBoByName(const std::string kMoveName) {

    for (int i = 0; i < mpPrivate->mMoveBoVec.size(); i++) {
        if (mpPrivate->mMoveBoVec[i].name == kMoveName) {
            return mpPrivate->mMoveBoVec[i];
        }
    }
    return {};
}

MoveBo PokemonBo::findMoveBoByIndex(const int& kMonitorIndex) {
    return mpPrivate->mMoveBoVec[kMonitorIndex];
}


std::vector<TYPE> PokemonBo::getPokemonTypes() const {
    return mpPrivate->mPokemonTypeVec;
}


std::vector<MoveBo> PokemonBo::getMoveBos() const {
    return mpPrivate->mMoveBoVec;
}


int PokemonBo::getMaxHp() const {
    return mpPrivate->mMaxHp;
}

int PokemonBo::getHp() const {
    return mpPrivate->mPokemonStats.hp;
}

void PokemonBo::setPokemonAdditionalEffectType(const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType) {
    mpPrivate->mPokemonAdditionEffectTypeSet.insert(kAdditionalEffectType);
}
std::set<ADDITIONAL_EFFECT_TYPE> PokemonBo::getPokemonAdditionalEffectType() const {
    return mpPrivate->mPokemonAdditionEffectTypeSet;
}

std::string PokemonBo::getName() const {
    return mpPrivate->mPokemonName;
}

void PokemonBo::reduceHalfSpeed() {
    mpPrivate->mPokemonStats.speed /= 2;
}

void PokemonBo::checkToMyPokemon(const bool& kMyPokemon) {
    mpPrivate->mIsMyPokemon = kMyPokemon;
}
bool PokemonBo::isMyPokemon() const {
    return mpPrivate->mIsMyPokemon;
}
