#pragma once

#include <memory>
#include <set>

#include "pokemonStats.h"
#include "type.h"
#include "moveStats.h"
#include "damageType.h"
#include "additionalEffectType.h"

struct MoveBo {
    std::string name;   // Name of the Move
    TYPE type;          // Type of the Move
    DAMAGE_TYPE damageType; // Damage type of the Move
    MoveStats stats; // Statistical attributes of the Move
    ADDITIONAL_EFFECT_TYPE additionalEffectType; // Additional effect of the Move
};

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

    MoveBo findMoveBoByName(const std::string kMoveName);
    MoveBo findMoveBoByIndex(const int& kMonitorIndex);
    std::vector<MoveBo> getMoveBos() const;

    std::vector<TYPE> getPokemonTypes() const;

    bool isFainting();

    int getMaxHp() const;
    int getHp() const;

    void setPokemonAdditionalEffectType(const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType);
    std::set<ADDITIONAL_EFFECT_TYPE> getPokemonAdditionalEffectType() const;

    std::string getName() const;

    void reduceHalfSpeed();
    void checkToMyPokemon(const bool& kMyPokemon);
    bool isMyPokemon() const;
    void minusMovePowerPoint(const MoveBo& kMoveBo);
    std::vector<int> getMaxPowerPoint() const;
private:
    std::unique_ptr<PokemonBoPrivate> mpPrivate;
};
