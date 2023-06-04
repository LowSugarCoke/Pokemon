#pragma once

#include "Pokemon.h"
#include "Move.h"
#include "Player.h"

#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

class Game {
private:
	int turn;

	Player player1;
	Player player2;

	vector<Pokemon> pokemonData;
	vector<Move> moveData;

public:
	Game() {};

	bool run();

private:
	void setup();
	void readMove(string filePath);
	void readPokemon(string filePath);
	void readGameData(string filePath);
	void switchTurn();
};