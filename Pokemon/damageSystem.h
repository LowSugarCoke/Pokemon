#pragma once

#include <memory>

class DamageSystemPrivate;
class DamageSystem {
public:
    DamageSystem();
    DamageSystem(const DamageSystem& kDamageSystem);
    ~DamageSystem();

    int damageCalculate();

private:
    std::unique_ptr<DamageSystemPrivate> mpPrivate;
};
