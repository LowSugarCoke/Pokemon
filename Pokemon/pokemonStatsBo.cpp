#include "pokemonStatsBo.h"

#include <vector>

#include "moveEntity.h"
#include "pokemonEntity.h"

class PokemonStatsBoPrivate {
public:
    std::vector<MoveEntity> mMoveEntityVec;
    PokemonEntity mPokemonEntity;
};

PokemonStatsBo::PokemonStatsBo()
    :mpPrivate(std::make_unique<PokemonStatsBoPrivate>())
{

}

PokemonStatsBo::PokemonStatsBo(const PokemonStatsBo& kPokemonStatsBo)
    : mpPrivate(std::make_unique<PokemonStatsBoPrivate>(*kPokemonStatsBo.mpPrivate))
{

}

PokemonStatsBo::~PokemonStatsBo() {}



void PokemonStatsBo::setPokemonEntity(const PokemonEntity& kPokemonEntity) {
    mpPrivate->mPokemonEntity = kPokemonEntity;
}
void PokemonStatsBo::addMoveEntity(const MoveEntity& kMoveEntity) {
    mpPrivate->mMoveEntityVec.push_back(kMoveEntity);
}
