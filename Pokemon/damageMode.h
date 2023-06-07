#pragma once

#include <memory>
#include <string>

class PokemonBo;
class DamageModePrivate;
class DamageMode {
public:
    DamageMode();
    DamageMode(const DamageMode& kDamageMode);
    ~DamageMode();

    bool isMissing(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const std::string& kMoveName);
    int damageCalculate(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const std::string& kMoveName);

private:
    std::unique_ptr<DamageModePrivate> mpPrivate;
};
