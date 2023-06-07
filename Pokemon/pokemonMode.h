#pragma once

#include <memory>
#include <string>

class PokemonBo;
class AdditionalEffectMode;
class DamageMode;
class PotionMode;
class PokemonModePrivate;
class PokemonMode {
public:
    PokemonMode(std::shared_ptr<DamageMode> pDamageMode, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode, std::shared_ptr<PotionMode> pPotionMode);
    PokemonMode(const PokemonMode& kPokemonMode);
    ~PokemonMode();

    void setMyPokemon(std::shared_ptr<PokemonBo> pMyPokemon);
    void setOppositingPokemon(std::shared_ptr<PokemonBo> pOppositingPokemon);

    void nextRound(const int& kMoveIndex);

    void nextRoundWithoutAttack();

private:
    std::unique_ptr<PokemonModePrivate> mpPrivate;
};
