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
void printGames(struct TheGame* games, int i) {
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

void change(struct TheGame* games, int arraySize)
{
    printf("Choose an operation:\n");
    printf("1)  Edit the entire post\n");
    printf("2)  Edit part of note\n");
    printf("3)  Exit\n");
    int choice = correctChoice(3);
    switch (choice)
    {
        case 1:
            changeOneGame(games, arraySize);
            break;
        case 2:
            partChange(games, arraySize);
            break;
        case 3:
            break;
    }

}
void changeOneGame(struct TheGame* pointer, int arraySize)
{
    printf("Enter game number\n");
    int gameNumber = correctChoice(arraySize);
    gameNumber--;

    printf("Enter new game name\n");
    rewind(stdin);
    gets(pointer[gameNumber].name);

    printf("Enter new price size\n");
    pointer[gameNumber].price = inputValidationFloat();

    if (pointer[gameNumber].flag == 1)
    {
        printf("Make a choice\n");
        printf("1)  Change game genre\n");
        printf("2)  Change the field with the game genre to the maximum number of players\n");
        int choice = correctChoice(2);
        switch (choice)
        {
            case 1:
                printf("Enter a new genre\n");
                rewind(stdin);
                gets(pointer[gameNumber].rules.gameGenre);
                //break;
                return;
            case 2:
                printf("Enter the maximum number of players\n");
                pointer[gameNumber].rules.maxPlayers = inputValidationInt();
                pointer[gameNumber].flag = 2;
                //break;
                return;
        }
    }
    if (pointer[gameNumber].flag == 2)
    {
        printf("Make choice\n");
        printf("1)  Change the maximum number of players\n");
        printf("2)  Change the maximum number of players to the game genre\n");
        int choice = correctChoice(2);
        switch (choice)
        {
            case 1:
                printf("Enter the maximum number of players\n");
                pointer[gameNumber].rules.maxPlayers = inputValidationInt();
                //break;
                return;
            case 2:
                printf("Enter new genre\n");
                rewind(stdin);
                gets(pointer[gameNumber].rules.gameGenre);
                pointer[gameNumber].flag = 1;
                //break;
                return;
        }
    }
}
void partChange(struct TheGame* pointer, int arraySize)
{
    printf("Enter game number\n");
    int gameNumber = correctChoice(arraySize);
    gameNumber--;
    printf("Make a choice\n");
    printf("1)  Change game name\n");
    printf("2)  Change price size\n");
    printf("3)  Change game genre\n");
    printf("4)  Change the maximum number of players\n");
    int choice = correctChoice(4);
    switch (choice)
    {
        case 1:
            printf("Enter new game name\n");
            rewind(stdin);
            gets(pointer[gameNumber].name);
            break;
        case 2:
            printf("Enter new price size\n");
            pointer[gameNumber].price = inputValidationFloat();
            break;
        case 3:
            if (pointer[gameNumber].flag == 1)
            {
                printf("Enter the new genre\n");
                rewind(stdin);
                gets(pointer[gameNumber].rules.gameGenre);
            }
            if (pointer[gameNumber].flag == 2)
            {
                printf("If you change this field,"
                       "you will no longer be able to store information about the maximum number of players\n");
                printf("Do you want to make changes?\n");
                printf("1)No\n2)Yes\n");
                int editChoice = correctChoice(2);
                switch (editChoice)
                {
                    case 1:
                        break;
                    case 2:
                        printf("Enter the genre\n");
                        rewind(stdin);
                        gets(pointer[gameNumber].rules.gameGenre);
                        pointer[gameNumber].flag = 1;
                }
            }
            break;
        case 4:
            if (pointer[gameNumber].flag == 2)
            {
                printf("Enter the maximum number of players\n");
                pointer[gameNumber].rules.maxPlayers = inputValidationInt();
            }
            if (pointer[gameNumber].flag == 1)
            {
                printf("If you change this field,"
                       "you will no longer be able to store information about the genre of the game\n");
                printf("Do you want to make changes?\n");
                printf("1)No\n2)Yes\n");
                int editChoice = correctChoice(2);
                switch (editChoice)
                {
                    case 1:
                        break;
                    case 2:
                        printf("Enter the maximum number of players\n");
                        pointer[gameNumber].rules.maxPlayers = inputValidationInt();
                        pointer[gameNumber].flag = 2;
                }
            }
            break;
    }
}



//------------Проверки на ввод------------//
int inputValidationInt()
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}
float inputValidationFloat()
{
    float n;
    while (scanf("%f", &n) != 1 || n <= 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}
int correctChoice(int k)
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0 || n > k)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}
