#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
int main()
{
	int numberOfGames = 0;
	int newNumberOfGames = 0;
	struct TheGame* games = NULL;
	while (1)
	{
		switch (menu())
		{
		case 1:
			printf("Number of games you want to add: ");
			while (!scanf_s("%d", &newNumberOfGames) || (newNumberOfGames <= 0))
			{
				rewind(stdin);
				printf("Incorrect value.");
			}
			numberOfGames += newNumberOfGames;
			games = add(games, numberOfGames, newNumberOfGames);
			break;
		case 2: show(games, numberOfGames); break;
		case 3:
			//games = del(games, numberOfGames);
			break;
		case 4:	//search(games, numberOfGames); break;
		case 5: //sort(games, numberOfGames); break;
		case 6: //games = change(games, numberOfGames); break;
		case 7: //partSearch(games, numberOfGames); break;
		case 8:
			free(games);
			return 0;
		default:
			printf("Error. Incorrect value!\n");
		}
	}
}