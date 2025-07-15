#pragma once
#include <iostream>
#include "Tile.h"
using namespace std;

struct Board
{
	static const int SIZE = 4;
	Tile* table[SIZE][SIZE];

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

	void resetMergeFlag()
	{
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if(table[i][j]) 
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
		table[x][y] = new Tile(2);
	}

	void move(char dir)
	{
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
					}

					else if (target != row)
					{
						table[target][col] = table[row][col];
						table[row][col] = nullptr;
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
					}

					else if (target != row)
					{
						table[target][col] = table[row][col];
						table[row][col] = nullptr;
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
					}

					else if (target != col)
					{
						table[row][target] = table[row][col];
						table[row][col] = nullptr;
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
					}

					else if (target != col)
					{
						table[row][target] = table[row][col];
						table[row][col] = nullptr;
					}
				}
			}
		}
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
					if ((col < 3 && table[row][col]->value == table[row][col + 1]->value) ||
						(row < 3 && table[row][col]->value == table[row + 1][col]->value))
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
				if (table[row][col]&&table[row][col]->value == 2048)
					return true;
		return false;
	}

	void simpleDisplay()
	{
		for (int row = 0; row < SIZE; row++)
		{
			for (int col = 0; col < SIZE; col++)
			{   
				if (table[row][col]) cout << table[row][col]->value;
				else  cout << " ";
				 cout<< "    ";
			}
			cout << endl << endl;
		}
	}

};
