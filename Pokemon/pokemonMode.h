#pragma once

#include <memory>
#include <string>

class PokemonBo;
class DamageSystem;
class PokemonModePrivate;
class PokemonMode {
public:
    PokemonMode(std::shared_ptr<DamageSystem> pDamageSystem);
    PokemonMode(const PokemonMode& kPokemonMode);
    ~PokemonMode();

    void setMyPokemon(std::shared_ptr<PokemonBo> pMyPokemon);
    void setOppositingPokemon(std::shared_ptr<PokemonBo> pOppositingPokemon);

    void nextRound(const std::string& kMoveName);



private:
    std::unique_ptr<PokemonModePrivate> mpPrivate;
};
