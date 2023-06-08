#include "potionMode.h"

#include <vector>
#include <string>
#include <unordered_map>

#include "pokemonBo.h"
#include "pokemonLogger.h"

// Define the names of different potions
static const std::string kPotion = "Potion";
static const std::string kSuperPotion = "Super Potion";
static const std::string kHyperPotion = "Hyper Potion";
static const std::string kMaxPotion = "Max Potion";

// Create a vector to store the names of potions
static const std::vector<std::string> kPotionVec{ kPotion, kSuperPotion, kHyperPotion, kMaxPotion };

// Define the HP restoration values for each potion
static std::unordered_map<int, int> potionMap{
    {0, 20},
    {1, 60},
    {2, 120},
    {3, 100000},
};

class PotionModePrivate {
public:
    PotionModePrivate();
    PokemonLogger& mLogger; // Reference to the PokemonLogger instance for logging purposes
};

PotionModePrivate::PotionModePrivate()
    : mLogger(PokemonLogger::getInstance()) // Initialize the logger with the PokemonLogger instance
{
}

PotionMode::PotionMode()
    : mpPrivate(std::make_unique<PotionModePrivate>()) // Create a unique pointer to PotionModePrivate
{
}

PotionMode::PotionMode(const PotionMode& kPotionMode)
    : mpPrivate(std::make_unique<PotionModePrivate>()) // Create a deep copy of the PotionModePrivate object
{
}

PotionMode::~PotionMode() {
}

std::vector<std::string> PotionMode::getPotionsName() const {
    return kPotionVec; // Return the names of available potions
}

void PotionMode::addHp(std::shared_ptr<PokemonBo> pPokemonBo, const int& kPotionIndex) {
    mpPrivate->mLogger.log("You used a " + kPotionVec[kPotionIndex] + "!"); // Log the potion usage
    pPokemonBo->addHp(potionMap[kPotionIndex]); // Restore HP of the Pokemon using the corresponding potion
    mpPrivate->mLogger.log(pPokemonBo->getName() + " had its HP restored."); // Log the HP restoration
}
