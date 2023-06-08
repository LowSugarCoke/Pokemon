#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <string>

class PokemonBo;
class PotionModePrivate;
class PotionMode {
public:

    PotionMode();
    ~PotionMode();
    PotionMode(const PotionMode& kPotionMode);


    std::vector<std::string> getPotionsName() const;
    void addHp(std::shared_ptr<PokemonBo> pPokemonBo, const int& kPotionIndex);

private:
    std::unique_ptr<PotionModePrivate> mpPrivate;
};
