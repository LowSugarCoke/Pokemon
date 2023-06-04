#pragma once
#include <iostream>
#include <string>

#include "DAMAGE_TYPE.h"
#include "STATUS.h"
#include "TYPE.h"

#include "MoveStat.h"

using namespace std;

class Move {
private:
	string name;
	TYPE type;
	DAMAGE_TYPE	damageType;
	// int power, accuracy, PP;
	MoveStat stat;
	STATUS status;

public:
	Move() {}
	Move(string);

	string getName() const;
	TYPE getType() const { return this->type; }
	DAMAGE_TYPE getDamageType() const { return this->damageType; }
	vector<STATUS> getStatus() const;

	//int getPower() { return this->power; }
	//int getAccuracy() { return this->accuracy; }

	friend ostream& operator<<(ostream& out, Move& rhs);
	friend istream& operator>>(istream& in, Move& rhs);
};