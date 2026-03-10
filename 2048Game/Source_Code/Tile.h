#pragma once
#include <vector>
using namespace std;

class Tile
{
private:
	int value;
	bool mergedThisTurn;

public:

	int getValue()
	{
		return value;
	}

	Tile(int val = 2) :value(val), mergedThisTurn(false) {}

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
