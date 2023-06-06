#pragma once

#include <memory>

class PokemonBo;
class PokemonModePrivate;
class PokemonMode {
public:
    PokemonMode(std::shared_ptr<PokemonBo> pPokemonBo);
    PokemonMode(const PokemonMode& kPokemonMode);
    ~PokemonMode();

    bool isFaster(std::shared_ptr<PokemonMode> pOpposingPokemonMode);
    void Damage(std::shared_ptr<PokemonMode> pOpposingPokemonMode);

private:
    std::unique_ptr<PokemonModePrivate> mpPrivate;
};
