#pragma once
#include "Pokemon.h"
#include "Item.h"
#include "Move.h"

#include <vector>

using namespace std;

class Player {
private:
	// string name;
	vector<Pokemon> pokemons;
	vector<Item*> bag;

public:
	Player() {}
	Player(vector<Pokemon> pokemons, vector<Item*> bag);

	bool isLose();
	bool useMove(Move move);
	bool swapPokemon(Pokemon newPokemon);
	bool useItem(Item* item, Pokemon target);
	void escape();
};