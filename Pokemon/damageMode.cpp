#include "damageMode.h"

#include <random>
#include <algorithm> 

#include "pokemonBo.h"
#include "pokemonTypeChart.h"
#include "pokemonLogger.h"

const int kLevel = 50;

class DamageModePrivate {
public:
    DamageModePrivate();
    float getCriticalRandom();
    float getSameTypeAttackBonus(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);
    float getType(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pTargetPokemonBo);
    float getAttack(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);
    float getDefense(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);
    void typeLog(const float& kType);
    PokemonLogger& mLogger;

};
DamageModePrivate::DamageModePrivate()
    : mLogger(PokemonLogger::getInstance())
{}

void DamageModePrivate::typeLog(const float& kType) {
    static const float epsilon = 0.001; // Set this to a suitable value
    if (std::abs(kType - 2.0) < epsilon || kType > 2.0) {
        mLogger.log("It's super effective!");
    }
    else if (std::abs(kType - 0.5) < epsilon) {
        mLogger.log("It's not very effective...");
    }
    else if (std::abs(kType - 0.0) < epsilon) {
        mLogger.log("It's not effective!");
    }
}

float DamageModePrivate::getCriticalRandom() {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 10);

    int randomNumber = distrib(gen);

    if (randomNumber == 1) {
        return 1.5;
    }
    else {
        return 1;
    }
}

float DamageModePrivate::getSameTypeAttackBonus(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
    auto types = pPokemonBo->getPokemonTypes();
    for (int i = 0; i < types.size(); i++) {
        if (kMoveBo.type == types[i]) {
            return 1.5;
        }
    }
    return 1;
}

float DamageModePrivate::getType(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pTargetPokemonBo) {
    float cnt = 1.0;
    auto types = pTargetPokemonBo->getPokemonTypes();
    for (int i = 0; i < types.size(); i++) {
        auto r = static_cast<int>(kMoveBo.type);
        auto c = static_cast<int>(types[i]);
        cnt *= kEffectivenessRate[static_cast<int>(kMoveBo.type)][static_cast<int>(types[i])];
    }
    return cnt;
}

float DamageModePrivate::getAttack(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
    if (kMoveBo.damageType == DAMAGE_TYPE::PHYSICAL) {
        return pPokemonBo->getPokemonStats().attack;
    }
    else if (kMoveBo.damageType == DAMAGE_TYPE::SPECIAL) {
        return pPokemonBo->getPokemonStats().specialAttack;
    }
    else {
        return 0;
    }
}

float DamageModePrivate::getDefense(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
    if (kMoveBo.damageType == DAMAGE_TYPE::PHYSICAL) {
        return pPokemonBo->getPokemonStats().defense;
    }
    else if (kMoveBo.damageType == DAMAGE_TYPE::SPECIAL) {
        return pPokemonBo->getPokemonStats().specialDefence;
    }
    else {
        return 0;
    }
}



DamageMode::DamageMode()
    :mpPrivate(std::make_unique<DamageModePrivate>())
{

}
DamageMode::DamageMode(const DamageMode& kDamageMode)
    : mpPrivate(std::make_unique<DamageModePrivate>(*kDamageMode.mpPrivate))
{

}
DamageMode::~DamageMode() {

}

int DamageMode::damageCalculate(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const MoveBo& kMoveBo) {

    // Ref: https://bulbapedia.bulbagarden.net/wiki/Damage

    float damage = 0.0;

    if (kMoveBo.damageType == DAMAGE_TYPE::STATUS) {
        return 0.0;
    }

    float power = kMoveBo.stats.power;
    float atack = mpPrivate->getAttack(kMoveBo, pMyPokemonBo);
    float defence = mpPrivate->getDefense(kMoveBo, pTargetPokemonBo);
    float critical = mpPrivate->getCriticalRandom();
    float STAB = mpPrivate->getSameTypeAttackBonus(kMoveBo, pMyPokemonBo);
    float type = mpPrivate->getType(kMoveBo, pTargetPokemonBo);

    damage = (((2 * kLevel + 10) / 250) * power * (atack / defence) + 2) * critical * STAB * type * 10;

    mpPrivate->typeLog(type);

    return static_cast<int>(damage);
}


bool DamageMode::isMissing(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const MoveBo& kMoveBo) {
    auto accuracy = kMoveBo.stats.accuracy;
    auto targetSpeed = pTargetPokemonBo->getPokemonStats().speed;

    static const double totalStatPoints = 500.0; // Please adjust this constant based on your game setting.
    double dodgeChance = static_cast<double>(targetSpeed - accuracy) / totalStatPoints;
    dodgeChance = std::max(0.0, std::min(1.0, dodgeChance)); // Ensure dodgeChance falls in range [0,1]

    // Create a random number generator
    static std::default_random_engine rng(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Generate a random number and check if it is less than dodgeChance
    return dist(rng) < dodgeChance;
}
