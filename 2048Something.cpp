#include "Board.h"
#include <conio.h>
int main()
{
	srand(time(nullptr));
	Board playTable;
	char direction;
	playTable.spamTile();
	playTable.spamTile();
	playTable.simpleDisplay();
	while (!playTable.checkLose())
	{
		direction=_getch();
		playTable.move(direction);
		if (playTable.checkWin())
			return 0;
		playTable.resetMergeFlag();
		playTable.spamTile();
		playTable.simpleDisplay();
		cout << endl;
	}
	cout << "you lost";
	return 0;
}

