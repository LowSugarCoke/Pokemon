#pragma once

#include <memory>
#include <functional>

class PotionModePrivate;
class PotionMode {
public:

    PotionMode();
    ~PotionMode();
    PotionMode(const PotionMode& kPotionMode);

    void setAddHPCallBack(const std::function<void(const int&)>& kpFunction);

private:
    std::unique_ptr<PotionModePrivate> mpPrivate;
};
