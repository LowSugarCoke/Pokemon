#include "potionMode.h"

#include <vector>
#include <string>
#include <unordered_map>

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

    std::function<void(const int&)> mAddHP;

};

PotionMode::PotionMode()
    :mpPrivate(std::make_unique<PotionModePrivate>())
{

}
PotionMode::PotionMode(const PotionMode& kPotionMode)
    : mpPrivate(std::make_unique<PotionModePrivate>())
{

}

PotionMode::~PotionMode() {
}

void PotionMode::setAddHPCallBack(const std::function<void(const int&)>& kpFunction) {
    mpPrivate->mAddHP = kpFunction;
}


std::vector<std::string> PotionMode::getPotionsName() const {
    return kPotionVec;
}

void PotionMode::usePotion(const int& kMotionIndex) {

    mpPrivate->mAddHP(potionMap[kMotionIndex]);
}
