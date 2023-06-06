#include "damageSystem.h"

#include <random>
#include <algorithm> 

#include "pokemonBo.h"
#include "pokemonTypeChart.h"

const int kLevel = 50;

class DamageSystemPrivate {
public:
    float getCriticalRandom();
    float getSameTypeAttackBonus(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);
    float getType(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pTargetPokemonBo);
    float getAttack(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);
    float getDefense(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo);
    float getStatusHurt(std::shared_ptr<PokemonBo> pTargetPokemonBo);
};

float DamageSystemPrivate::getCriticalRandom() {
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

float DamageSystemPrivate::getSameTypeAttackBonus(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
    auto types = pPokemonBo->getPokemonTypes();
    for (int i = 0; i < types.size(); i++) {
        if (kMoveBo.type == types[i]) {
            return 1.5;
        }
    }
    return 1;
}

float DamageSystemPrivate::getType(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pTargetPokemonBo) {
    float cnt = 0.0;
    auto types = pTargetPokemonBo->getPokemonTypes();
    for (int i = 0; i < types.size(); i++) {
        cnt *= kEffectivenessRate[static_cast<int>(kMoveBo.type)][static_cast<int>(types[i])];
    }
    return cnt;
}

float DamageSystemPrivate::getAttack(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
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

float DamageSystemPrivate::getDefense(const MoveBo& kMoveBo, std::shared_ptr<PokemonBo> pPokemonBo) {
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

float DamageSystemPrivate::getStatusHurt(std::shared_ptr<PokemonBo> pTargetPokemonBo) {
    return pTargetPokemonBo->getMaxHp() / 16;
}

DamageSystem::DamageSystem()
    :mpPrivate(std::make_unique<DamageSystemPrivate>())
{

}
DamageSystem::DamageSystem(const DamageSystem& kDamageSystem)
    : mpPrivate(std::make_unique<DamageSystemPrivate>(*kDamageSystem.mpPrivate))
{

}
DamageSystem::~DamageSystem() {

}

int DamageSystem::damageCalculate(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const std::string& kMoveName) {

    // Ref: https://bulbapedia.bulbagarden.net/wiki/Damage

    float damage = 0.0;

    auto moveBo = pMyPokemonBo->findMoveBoByName(kMoveName);
    if (moveBo.damageType == DAMAGE_TYPE::STATUS) {
        if (pTargetPokemonBo->getPokemonAdditionalEffectType() == ADDITIONAL_EFFECT_TYPE::NRML) {
            pTargetPokemonBo->setPokemonAdditionalEffectType(moveBo.additionalEffectType);
        }

        return 0.0;
    }

    float power = moveBo.stats.power;
    float atack = mpPrivate->getAttack(moveBo, pMyPokemonBo);
    float defence = mpPrivate->getDefense(moveBo, pTargetPokemonBo);
    float critical = mpPrivate->getCriticalRandom();
    float STAB = mpPrivate->getSameTypeAttackBonus(moveBo, pMyPokemonBo);
    float type = mpPrivate->getType(moveBo, pTargetPokemonBo);

    damage = (((2 * kLevel + 10) / 250) * power * (atack / defence) + 2) * critical * STAB * type;



    return static_cast<int>(damage);
}

int DamageSystem::statusDamageCalculate(std::shared_ptr<PokemonBo> pTargetPokemonBo) {
    float damage = 0.0;
    if (pTargetPokemonBo->getPokemonAdditionalEffectType() != ADDITIONAL_EFFECT_TYPE::NRML) {
        damage = mpPrivate->getStatusHurt(pTargetPokemonBo);
    }
    return static_cast<int>(damage);
}

bool DamageSystem::isMiss(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const std::string& kMoveName) {
    auto accuracy = pMyPokemonBo->findMoveBoByName(kMoveName).stats.accuracy;
    auto targetSpeed = pTargetPokemonBo->getPokemonStats().speed;

    const double totalStatPoints = 100.0; // Please adjust this constant based on your game setting.
    double dodgeChance = static_cast<double>(targetSpeed - accuracy) / totalStatPoints;
    dodgeChance = std::max(0.0, std::min(1.0, dodgeChance)); // Ensure dodgeChance falls in range [0,1]

    // Create a random number generator
    static std::default_random_engine rng(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Generate a random number and check if it is less than dodgeChance
    return dist(rng) < dodgeChance;
}
