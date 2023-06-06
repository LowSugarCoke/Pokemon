#include "damageSystem.h"


class DamageSystemPrivate {
public:

};

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
