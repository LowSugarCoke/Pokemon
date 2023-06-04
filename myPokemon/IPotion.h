#pragma once

#include "Item.h"

class IPotion : public Item {
public:
	virtual void use(Pokemon& target) final override;
	virtual void heal(Pokemon& target) = 0;
};