#pragma once
#include "IPotion.h"

class Potion : public IPotion {
	void heal(Pokemon& target) final override;
};