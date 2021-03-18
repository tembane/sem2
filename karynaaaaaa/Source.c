#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <string.h>
union Rules
{
	int maxPlayers;
	char gameGenre[20];
};
struct TheGame
{
	float price;
	char name[20];
	union Rules rules;
	int flag;
};
int menu()
{
	int choice;
	printf("Choose an operation:\n");
	printf("1) Add game\n2) Show games\n3) Change games\n4) Search games\n5) Partical search\n6) Delete games\n7) Sort games\n8) Exit\n");
	while (!scanf_s("%d", &choice) || (choice <1) || (choice > 8))
	{
		printf("Incorrect value! Try again...\n");
		rewind(stdin);
	}
	return choice;
}
struct TheGame* add(struct TheGame* games, int numberOfGames, int newNumberOfGames)
{
	if (numberOfGames - newNumberOfGames == 0) games = (struct TheGame*)calloc(numberOfGames, sizeof(struct TheGame));
	else games = (struct TheGame*)realloc(games, numberOfGames* sizeof(struct TheGame));
	for (int i = numberOfGames - newNumberOfGames; i < numberOfGames; i++)
	{
		printf("Number of game: %d\n", i + 1);
		printf("Enter price: ");
		while (!scanf_s("%f", &games[i].price) || (games[i].price < 0))
		{
			rewind(stdin);
			printf("Incorrect value!\n");
		}
		printf("Enter name: ");
		rewind(stdin);
		fgets(games[i].name, 20, stdin);
		rewind(stdin);
		games[i].name[strlen(games[i].name) - 1] = '\0';
		printf("Enter '1' to enter game genre or '2' to enter max number of players: ");
		while (!scanf_s("%d", &games[i].flag) || (games[i].flag < 1) || (games[i].flag > 2))
		{
			rewind(stdin);
			printf("Incorrect value! try again...\n");
		}
		if (games[i].flag == 1)
		{
			printf("Enter game genre: ");
			rewind(stdin);
			fgets(games[i].rules.gameGenre, 20, stdin);
			rewind(stdin);
			games[i].rules.gameGenre[strlen(games[i].rules.gameGenre) - 1] = '\0';
		}
		else
		{
			printf("Enter max number of players: ");
			while (!scanf_s("%d", &games[i].rules.maxPlayers) || (games[i].rules.maxPlayers < 1))
			{
				rewind(stdin);
				printf("Incorrect value! try again...\n");
			}
		}
	}
	return games;
}
void show(struct TheGame* games, int numberOfGames) {
	hat();
	for (int i = 0; i < numberOfGames; i++) {
		printWorker(games, i);
		line();
	}
}
void hat() {
	char title[] = "G A M E S";
	line();
	printf("|%-40s%-79s|\n", " ", title);
	line();
	printf("|\t%-2s\t|\t%-15s\t|\t%-8s\t|\t%-9s\t|\t%-s\t\t\t|\n", "#", "Name", "Price", "Genre", "Max Players");
	line();
}
void printWorker(struct TheGame* games, int i) {
	if (games[i].flag == 1)
		printf("|\t%-2d\t|\t%-20s\t|\t%-.2f\t|\t%-20s\t|\t%-s\t\t|\n", i + 1,
			games[i].name, games[i].price, games[i].rules.gameGenre, "-");
	else printf("|\t%-2d\t|\t%-20s\t|\t%-.2f\t|\t%-s\t|\t%-5d\t\t\t|\n", i + 1,
		games[i].name, games[i].price, "-", games[i].rules.maxPlayers);
		line();
}
void line()
{
	for (int i = 0; i < 115; i++)
	{
		printf("%c", '-');
	}
	printf("\n");
}