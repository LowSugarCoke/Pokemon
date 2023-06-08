#include "potionMode.h"

#include <vector>
#include <string>
#include <unordered_map>

#include "pokemonBo.h"
#include "pokemonLogger.h"

static const std::string kPotion = "Potion";
static const std::string kSuperPotion = "Super Potion";
static const std::string kHyperPotion = "Hyper Potion";
static const std::string kMaxPotion = "Max Potion";

static const std::vector<std::string> kPotionVec{ kPotion, kSuperPotion, kHyperPotion, kMaxPotion };

static std::unordered_map<int, int> potionMap{
    {0, 20},
    {1, 60},
    {2, 120},
    {3, 100000},
};

class PotionModePrivate {
public:
    PotionModePrivate();
    PokemonLogger& mLogger;

};

PotionModePrivate::PotionModePrivate()
    : mLogger(PokemonLogger::getInstance())
{

}

PotionMode::PotionMode()
    : mpPrivate(std::make_unique<PotionModePrivate>())

{

}
PotionMode::PotionMode(const PotionMode& kPotionMode)
    : mpPrivate(std::make_unique<PotionModePrivate>())
{

}

PotionMode::~PotionMode() {
}



std::vector<std::string> PotionMode::getPotionsName() const {
    return kPotionVec;
}


void PotionMode::addHp(std::shared_ptr<PokemonBo> pPokemonBo, const int& kPotionIndex) {
    mpPrivate->mLogger.log("You used a " + kPotionVec[kPotionIndex] + "!");
    pPokemonBo->addHp(potionMap[kPotionIndex]);
    mpPrivate->mLogger.log(pPokemonBo->getName() + " had its HP restored.");
}
