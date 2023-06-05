#include "pokemonEntity.h"

class PokemonEntityPrivate {
public:
    std::string mName;
    std::vector<TYPE> mTypeVec;
    PokemonStats mStats;
};

PokemonEntity::PokemonEntity()
    :mpPrivate(std::make_unique<PokemonEntityPrivate>())
{
    mpPrivate->mName = "";
    mpPrivate->mStats.attack = 0;
    mpPrivate->mStats.defense = 0;
    mpPrivate->mStats.hp = 0;
    mpPrivate->mStats.specialAttack = 0;
    mpPrivate->mStats.specialDefence = 0;
    mpPrivate->mStats.speed = 0;
}
PokemonEntity::PokemonEntity(const std::string& kName, const std::vector<TYPE>& kTypeVec, const PokemonStats& kStats)
    : mpPrivate(std::make_unique<PokemonEntityPrivate>())
{
    setName(kName);
    mpPrivate->mTypeVec = kTypeVec;
    setStats(kStats);
}

void PokemonEntity::setName(const std::string& kName) {
    mpPrivate->mName = kName;
}

std::string PokemonEntity::getName() const {
    return mpPrivate->mName;
}

void PokemonEntity::addType(const TYPE& kType) {
    mpPrivate->mTypeVec.push_back(kType);
}
std::vector<TYPE> PokemonEntity::getTypes() const {
    return mpPrivate->mTypeVec;
}

void PokemonEntity::setStats(const PokemonStats& kStats) {
    mpPrivate->mStats = kStats;
}
PokemonStats PokemonEntity::getStats() const {
    return mpPrivate->mStats;
}
