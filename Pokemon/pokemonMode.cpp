#include "pokemonMode.h"

#include "pokemonStatsBo.h"

class PokemonModePrivate {
public:
    PokemonModePrivate(std::shared_ptr<PokemonBo> pPokemonBo);
    std::shared_ptr<PokemonBo> mpStats;

};

PokemonModePrivate::PokemonModePrivate(std::shared_ptr<PokemonBo> pPokemonBo)
    :mpStats(pPokemonBo)
{

}


PokemonMode::PokemonMode(std::shared_ptr<PokemonBo> pPokemonBo)
    :mpPrivate(std::make_unique<PokemonModePrivate>(pPokemonBo))
{

}

PokemonMode::PokemonMode(const PokemonMode& kPokemonMode)
    : mpPrivate(std::make_unique<PokemonModePrivate>(*kPokemonMode.mpPrivate))
{

}

PokemonMode::~PokemonMode() {
}

void PokemonMode::Damage(std::shared_ptr<PokemonMode> pOpposingPokemonMode) {

}

bool PokemonMode::isFaster(std::shared_ptr<PokemonMode> pOpposingPokemonMode) {
    return mpPrivate->mpStats->getPokemonStats().speed > pOpposingPokemonMode->mpPrivate->mpStats->getPokemonStats().speed;
}
