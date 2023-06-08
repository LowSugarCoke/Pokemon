#pragma once

#include <memory>

class MoveBo;
class PokemonBo;
class AdditionalEffectModePrivate;
class AdditionalEffectMode {
public:


    AdditionalEffectMode();

    ~AdditionalEffectMode();

    bool unableToMove(std::shared_ptr<PokemonBo> pPokemonBo)const;
    void addIfMoveHasAdditionalEffect(std::shared_ptr<PokemonBo> pPokemonBo, MoveBo moveBo);

    void additionalDamageAfterBattle(std::shared_ptr<PokemonBo> pPokemonBo);

    void setTest();
private:
    std::unique_ptr<AdditionalEffectModePrivate> mpPrivate;
};
