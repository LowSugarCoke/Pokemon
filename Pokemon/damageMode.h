#pragma once

#include <memory>
#include <string>
#include "pokemonBo.h"


class DamageModePrivate;
class DamageMode {
public:
    DamageMode();
    DamageMode(const DamageMode& kDamageMode);
    ~DamageMode();

    bool isMissing(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const MoveBo& kMoveBo);
    int damageCalculate(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const MoveBo& kMoveBo);
    void setTest();

private:
    std::unique_ptr<DamageModePrivate> mpPrivate;
};
