#pragma once
#include <string>

#include "Player.h"
#include "Pokemon.h"

using namespace std;

class Item {
protected:
	string name;
	int amount;

public:
	Item() {}
	Item(string name, int amount);

	virtual void use(Pokemon& target) = 0;
};