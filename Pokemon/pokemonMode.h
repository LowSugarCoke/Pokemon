#pragma once

#include <memory>
#include <string>

class PokemonBo;
class AdditionalEffectMode;
class DamageSystem;
class PokemonModePrivate;
class PokemonMode {
public:
    PokemonMode(std::shared_ptr<DamageSystem> pDamageSystem, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode);
    PokemonMode(const PokemonMode& kPokemonMode);
    ~PokemonMode();

    void setMyPokemon(std::shared_ptr<PokemonBo> pMyPokemon);
    void setOppositingPokemon(std::shared_ptr<PokemonBo> pOppositingPokemon);

    void nextRound(const std::string& kMoveName);

    void nextRoundWithoutAttack();

private:
    std::unique_ptr<PokemonModePrivate> mpPrivate;
};
