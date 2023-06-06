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

    bool isMissing(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const std::string& kMoveName);
    int damageCalculate(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const std::string& kMoveName);

private:
    std::unique_ptr<DamageSystemPrivate> mpPrivate;
};
