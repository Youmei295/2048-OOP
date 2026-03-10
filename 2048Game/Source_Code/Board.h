#pragma once
#include <iostream>
#include "Tile.h"
using namespace std;

class Board
{
private:
	static const int SIZE = 4;
	Tile* table[SIZE][SIZE];

public:
	Board()
	{
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				table[i][j] = nullptr;
	}

	~Board()
	{
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				delete table[i][j];
	}

	Tile* getTile(int row, int col) 
	{
		return table[row][col];
	}

	void setTile(int row, int col, Tile* tile) {
		table[row][col] = tile;
	}

	void resetMergeFlag()
	{
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (table[i][j])
					table[i][j]->resetMergeFlag();
	}

	void spamTile()
	{
		vector<pair<int, int>> randomPool;
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (!table[i][j]) randomPool.push_back({ i,j });
		if (randomPool.empty()) return;
		int rnd = rand() % randomPool.size();
		int x = randomPool[rnd].first, y = randomPool[rnd].second;
		int val = rand() % 10;
		if (val == 4) table[x][y] = new Tile(4);
		else table[x][y] = new Tile(2);
	}

	bool move(char dir)
	{
		bool moved = false;
		if (dir == 'w' || dir == 'W')
		{
			for (int col = 0; col < SIZE; col++)
			{
				for (int row = 1; row < SIZE; row++)
				{
					if (!table[row][col]) continue;
					int target = row;
					while (target > 0 && !table[target - 1][col])
						target--;
					if (target > 0 && table[row][col]->canMergeWith(table[target - 1][col]))
					{
						table[target - 1][col]->mergeWith(table[row][col]);
						delete table[row][col];
						table[row][col] = nullptr;
						moved = true;
					}

					else if (!table[target][col] && target != row)
					{
						table[target][col] = table[row][col];
						table[row][col] = nullptr;
						moved = true;
					}
				}
			}
		}

		else if (dir == 's' || dir == 'S')
		{
			for (int col = 0; col < SIZE; col++)
			{
				for (int row = SIZE - 2; row >= 0; row--)
				{
					if (!table[row][col]) continue;
					int target = row;
					while (target < SIZE - 1 && !table[target + 1][col])
						target++;
					if (target < SIZE - 1 && table[row][col]->canMergeWith(table[target + 1][col]))
					{
						table[target + 1][col]->mergeWith(table[row][col]);
						delete table[row][col];
						table[row][col] = nullptr;
						moved = true;
					}

					else if (target != row)
					{
						table[target][col] = table[row][col];
						table[row][col] = nullptr;
						moved = true;
					}
				}
			}
		}

		else if (dir == 'a' || dir == 'A')
		{
			for (int row = 0; row < SIZE; row++)
			{
				for (int col = 1; col < SIZE; col++)
				{
					if (!table[row][col]) continue;
					int target = col;
					while (target > 0 && !table[row][target - 1])
						target--;
					if (target > 0 && table[row][col]->canMergeWith(table[row][target - 1]))
					{
						table[row][target - 1]->mergeWith(table[row][col]);
						delete table[row][col];
						table[row][col] = nullptr;
						moved = true;
					}

					else if (target != col)
					{
						table[row][target] = table[row][col];
						table[row][col] = nullptr;
						moved = true;
					}
				}
			}
		}

		else if (dir == 'd' || dir == 'D')
		{
			for (int row = 0; row < SIZE; row++)
			{
				for (int col = SIZE - 2; col >= 0; col--)
				{
					if (!table[row][col]) continue;
					int target = col;
					while (target < SIZE - 1 && !table[row][target + 1])
						target++;
					if (target < SIZE - 1 && table[row][col]->canMergeWith(table[row][target + 1]))
					{
						table[row][target + 1]->mergeWith(table[row][col]);
						delete table[row][col];
						table[row][col] = nullptr;
						moved = true;
					}

					else if (target != col)
					{
						table[row][target] = table[row][col];
						table[row][col] = nullptr;
						moved = true;
					}
				}
			}
		}
		return moved;
	}

	bool isFull()
	{
		for (int row = 0; row < SIZE; row++)
			for (int col = 0; col < SIZE; col++)
				if (!table[row][col]) return false;
		return true;
	}

	bool checkLose()
	{
		if (isFull())
		{
			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					if ((col < 3 && table[row][col]->getValue() == table[row][col + 1]->getValue()) ||
						(row < 3 && table[row][col]->getValue() == table[row + 1][col]->getValue()))
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}

	bool checkWin()
	{
		for (int row = 0; row < SIZE; row++)
			for (int col = 0; col < SIZE; col++)
				if (table[row][col] && table[row][col]->getValue() == 2048)
					return true;
		return false;
	}

	void simpleDisplay()
	{
		for (int row = 0; row < SIZE; row++)
		{
			for (int col = 0; col < SIZE; col++)
			{
				if (table[row][col]) cout << table[row][col]->getValue();
				else  cout << " ";
				cout << "    ";
			}
			cout << endl << endl;
		}
	}

};
