#pragma once
#include <vector>
using namespace std;

struct Tile
{
	int value;
	bool mergedThisTurn;

	Tile(int val = 2) :value(val), mergedThisTurn(false) {};

	void resetMergeFlag()
	{
		mergedThisTurn = false;
	}

	bool canMergeWith(Tile* otherTile) 
	{
		return otherTile && value == otherTile->value && !mergedThisTurn && !otherTile->mergedThisTurn;
	}

	void mergeWith(Tile* otherTile)
	{
		if (!canMergeWith(otherTile)) return;
		value *= 2;
		mergedThisTurn = true;
		/*otherTile->value = 0;*/
	}

};