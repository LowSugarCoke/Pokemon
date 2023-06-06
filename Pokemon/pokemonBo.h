#pragma once

#include <memory>

#include "pokemonStats.h"
#include "type.h"
#include "moveStats.h"
#include "damageType.h"
#include "additionalEffectType.h"

class MoveEntity;
class PokemonEntity;
class PokemonBoPrivate;
class PokemonBo {
public:
    PokemonBo();
    PokemonBo(const PokemonBo& kPokemonBo);

    ~PokemonBo();

    void setPokemonElements(const std::string& kName, const PokemonStats& kPokemonStats, const std::vector<TYPE>& kType);
    void addMoveElements(const std::string& kName, const MoveStats& kMoveStats, const TYPE& kType, const DAMAGE_TYPE& kDamageType
        , const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType);


    void addHp(const int& kHp);
    void minusHp(const int& kHp);

    PokemonStats getPokemonStats() const;

    bool isFainting();

private:
    std::unique_ptr<PokemonBoPrivate> mpPrivate;
};
