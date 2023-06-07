#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <string>

class PotionModePrivate;
class PotionMode {
public:

    PotionMode();
    ~PotionMode();
    PotionMode(const PotionMode& kPotionMode);

    void setAddHPCallBack(const std::function<void(const int&)>& kpFunction);
    std::vector<std::string> getPotionsName() const;

    void usePotion(const int& kMotionIndex);

private:
    std::unique_ptr<PotionModePrivate> mpPrivate;
};
