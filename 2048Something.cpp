#include "Board.h"
#include <conio.h>
int main()
{
	srand(time(nullptr));
	Board playTable;
	char direction;
	int firstX = rand() % 4, firstY = rand() % 4;
	playTable.table[firstX][firstY]=new Tile(2);
	int secondX = rand() % 4, secondY = rand() % 4;
	while (secondX == firstX && secondY == firstY)
	{
		secondX = rand() % 4;
		secondY = rand() % 4;
	}
	playTable.table[secondX][secondY] = new Tile(2);
	playTable.simpleDisplay();
	while (!playTable.checkLose())
	{
		direction=_getch();
		if (playTable.move(direction))
		{
			playTable.spamTile();
		}
		if (playTable.checkWin())
			return 0;
		playTable.resetMergeFlag();
		playTable.simpleDisplay();
		cout << endl;
	}
	cout << "you lost";
	return 0;
}

