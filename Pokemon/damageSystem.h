#pragma once

#include <memory>
#include <string>

class PokemonBo;
class DamageSystemPrivate;
class DamageSystem {
public:
    DamageSystem();
    DamageSystem(const DamageSystem& kDamageSystem);
    ~DamageSystem();

    bool isMiss(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const std::string& kMoveName);
    int damageCalculate(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const std::string& kMoveName);
    int statusDamageCalculate(std::shared_ptr<PokemonBo> pTargetPokemonBo);
private:
    std::unique_ptr<DamageSystemPrivate> mpPrivate;
};
