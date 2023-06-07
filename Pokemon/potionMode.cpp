#include "potionMode.h"

#include <vector>
#include <string>
#include <unordered_map>

static const std::string kPotion = "potion";
static const std::string kSuperPotion = "Super Potion";
static const std::string kHyperPotion = "Hyper Potion";
static const std::string kMaxPotion = "Max Potion";

static const std::unordered_map<std::string, int> potionMap{
    {kPotion, 20},
    {kSuperPotion, 60},
    {kHyperPotion, 120},
    {kMaxPotion, 100000},
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
