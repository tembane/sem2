#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include <windows.h>
union Info
{
	char date[8];
	int seasons;
};
struct Series
{
	char title[20];
	int episodes;
	Info info;
	int isType;
	int size;
};
int check(int numberOfSeries)
{
	if (numberOfSeries == 0)
	{
		printf("Ooops...No notes found.\n");
		return -1;
	}
	else return 1;
}
int menu()
{
	int choice;
	printf("Choose an operation:\n");
	printf("1) Add series\n2) Show series\n3) Delete series\n4) Search series\n5) Exit\n");
	while (!scanf_s("%d", &choice))
	{
		printf("Incorrect value! Try again...\n");
		rewind(stdin);
	}
	system("CLS");
	return choice;
}
struct Series* add(struct Series* serial, int numberOfSeries)
{
	system("CLS");
	printf("Enter number of seriess you want to add: ");
	int numberToAdd = 0;
	while (!scanf_s("%d", &numberToAdd) || (numberToAdd < 1))
	{
		rewind(stdin);
		system("CLS");
		printf("Incorrect value! try again...\n");
	}
	int startToAdd = numberOfSeries;
	numberOfSeries += numberToAdd;
	if(startToAdd!=0)	serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
	else serial = (Series*)calloc(numberOfSeries, sizeof(Series));
	system("CLS");
	for (int i = 0; i < numberOfSeries; i++)
	{
		serial[i].size = numberOfSeries;

	}
	for (int i = startToAdd; i < numberOfSeries; i++)
	{
		printf("Series number: %d\n", i + 1);
		printf("Enter series title: "); 
		rewind(stdin);
		fgets(serial[i].title, 20, stdin);
		rewind(stdin);
		deleteEnter(serial, numberOfSeries, i, 1);
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &serial[i].episodes) || (serial[i].episodes < 1))
		{
			rewind(stdin);
			system("CLS");
			printf("Incorrect value! try again...\n");
		}
		printf("Enter '1' to enter releae date or '2' to enter number of seasons: ");
		while (!scanf_s("%d", &serial[i].isType) || (serial[i].isType < 1) || (serial[i].isType > 2))
		{
			rewind(stdin);
			system("CLS");
			printf("Incorrect value! try again...\n");
		}
		if (serial[i].isType == 1)
		{
			printf("Enter release date(YYYYMMDD): ");
			rewind(stdin);
			fgets(serial[i].info.date, 8, stdin);
			rewind(stdin);
			deleteEnter(serial, numberOfSeries, i, 2);
		}
		else
		{
			printf("Enter number of seasons: ");
			while (!scanf_s("%d", &serial[i].info.seasons) || (serial[i].info.seasons < 1))
			{
				rewind(stdin);
				system("CLS");
				printf("Incorrect value! try again...\n");
			}
		}
		system("CLS");
	}
	return serial;
}
void show(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return;
	int choice;
	system("CLS");
	printf("1)Show all notes\n2)Show 1 note\n3)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choice)
	{
	case 1:
		system("CLS");
		print(serial, numberOfSeries, -1);
		break;
	case 2:
		printf("Enter number of series you want to see: ");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > numberOfSeries))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		choice--;
		system("CLS");
		print(serial, numberOfSeries, choice);
		break;
	case 3:
		return;
		break;
	}
}
void print(struct Series* serial, int numberOfSeries, int serialToPrint)
{
	char table[] = "S E R I E S";
	printLine();
	printf("|\t\t\t\t\t %-58s|\n", table);
	printLine();
	printf("|\t%-5s|\t%-19s|\t%-5s|\t%-5s|\t%-8s|\n", "Note", "Title", "Episodes", "Seasons", "Release Date");
	printLine();
	if (serialToPrint != -1)
	{
		if (serial[serialToPrint].isType == 1)
		{
			printf("|\t%-5d|\t%-19s|\t%-5d|\t%-5s|\t%-8s|\n",
				serialToPrint + 1, (serial + serialToPrint)->title,
				serial[serialToPrint].episodes, "-",
				(serial + serialToPrint)->info.date);
			printLine();
		}
		else
		{
			printf("|\t%-5d|\t%-19s|\t%-5d|\t%-5d|\t%-8s|\n",
				serialToPrint + 1, (serial + serialToPrint)->title,
				serial[serialToPrint].episodes, serial[serialToPrint].info.seasons,
				"-");
			printLine();
		}
	}
	else
	{
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].isType == 1)
			{
				printf("|\t%-5d|\t%-19s|\t%-5d|\t%-5s|\t%-8s|\n",
					i + 1, (serial + i)->title,
					serial[i].episodes, "-",
					(serial + i)->info.date);
				printLine();
			}
			else
			{
				printf("|\t%-5d|\t%-19s|\t%-5d|\t%-5d|\t%-8s|\n",
					i + 1, (serial + i)->title,
					serial[i].episodes, serial[i].info.seasons,
					"-");
				printLine();
			}
		}
	}
}
void printLine()
{
	for (int i = 0; i < 100; i++)
	{
		printf("%c", '_');
	}
	printf("\n");
}
int size(struct Series* serial, int numberOfSeries)
{
	numberOfSeries = serial[0].size;
	return numberOfSeries;
}
void deleteEnter(struct Series* serial, int numberOfSeries, int numberOfStructure, int choice)
{
	if (choice == 1)
	{
		for (int i = 0; i < 20; i++)
		{
			if (serial[numberOfStructure].title[i] == '\n')
				for (i; i < 20; i++)
					serial[numberOfStructure].title[i] = serial[numberOfStructure].title[i + 1];
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (serial[numberOfStructure].info.date[i] == '\n')
				for (i; i < 8; i++)
					serial[numberOfStructure].info.date[i] = serial[numberOfStructure].info.date[i + 1];
		}
	}
}
void search(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return;
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Title\n");
	printf("2)Number of episodes\n");
	printf("3)Date of release\n");
	printf("4)Number of seasons\n");
	printf("5)Exit\n");
	int choice, intToSearch = 0, flag = 0;
	char str[20];
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
	{
		system("CLS");
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		printf("Enter title: ");
		rewind(stdin);
		fgets(str, 20, stdin);
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')		str[i] ='\0';
		}
		for (int i = 0; i < numberOfSeries; ++i)
		{
			int temp = 0;
			if (strlen(serial[i].title) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial[i].title[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(serial, numberOfSeries, i);
					flag = 1;
				}
			}
		}
		break;
	case 2:
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].episodes == intToSearch)
			{
				print(serial, numberOfSeries, i);
				flag = 1;
				break;
			}
		}
		break;
	case 3:
		printf("Enter date of release(YYYYMMDD): ");
		rewind(stdin);
		fgets(str, 20, stdin);
		rewind(stdin);
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')		str[i] = '\0';
		}
		for (int i = 0; i < numberOfSeries; ++i)
		{
			if (serial[i].isType != 1) continue;
			int temp = 0;
			if (strlen(serial[i].info.date) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial[i].info.date[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(serial, numberOfSeries, i);
					flag = 1;
				}
			}
		}
		break;
	case 4:
		printf("Enter number of seasons: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].isType != 2) continue;
			if (serial[i].info.seasons == intToSearch)
			{
				print(serial, numberOfSeries, i);
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		system("CLS");
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
}
struct Series* del(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return serial;
	int choice = 0;
	system("CLS");
	printf("1)Delete all notes\n2)Delete 1 note\n3)Delete by option\n4)Exit\n");
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choice)
	{
	case 1:
		system("CLS");
		printf("All notes were successfully deleted!\n");
		numberOfSeries = 1;
		serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
		serial[0].size = 0;
		break;
	case 2:
		printf("Enter number of note you want to delete: ");
		while (!scanf_s("%d", &choice) || (choice < 1) || (choice > numberOfSeries))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		choice--;
		serial=delExact(serial, numberOfSeries, choice);
		return serial;
		break;
	case 3:
		serial=deleteByTheOption(serial, numberOfSeries);
		return serial;
		break;
	case 4:
		return serial;
		break;
	}
	return serial;
}
struct Series* delExact(struct Series* serial, int numberOfSeries, int serialNumber)
{
	for (int i = serialNumber; i < numberOfSeries; i++)
	{
		serial[i] = serial[i + 1];
	}
	numberOfSeries--;
	for (int i = 0; i < numberOfSeries; i++)
	{
		serial[i].size = numberOfSeries;
	}
	serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
	system("CLS");
	printf("Note was successfully deleted!\n");
	return serial;
}
struct Series* deleteByTheOption(struct Series* serial, int numberOfSeries)
{
	if (check(numberOfSeries) == -1) return serial;
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Title\n");
	printf("2)Number of episodes\n");
	printf("3)Date of release\n");
	printf("4)Number of seasons\n");
	printf("5)Exit\n");
	int choice, intToSearch = 0, flag = 0;
	char str[20];
	while (!scanf_s("%d", &choice) || (choice < 1) || (choice > 5))
	{
		system("CLS");
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choice)
	{
	case 1:
		printf("Enter title: ");
		rewind(stdin);
		fgets(str, 20, stdin);
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')		str[i] = '\0';
		}
		for (int i = 0; i < numberOfSeries; ++i)
		{
			int temp = 0;
			if (strlen(serial[i].title) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial[i].title[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
					{
						serial = delExact(serial, numberOfSeries, i);
						numberOfSeries--;
						for (int i = 0; i < numberOfSeries; i++)
						{
							serial[i].size = numberOfSeries;
						}
						serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
					}
					flag = 1;
				}
			}
		}
		break;
	case 2:
		printf("Enter number of episodes: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].episodes == intToSearch)
			{
				serial = delExact(serial, numberOfSeries, i);
				numberOfSeries--;
				for (int i = 0; i < numberOfSeries; i++)
				{
					serial[i].size = numberOfSeries;
				}
				serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
				flag = 1;
				break;
			}
		}
		break;
	case 3:
		printf("Enter date of release(YYYYMMDD): ");
		rewind(stdin);
		fgets(str, 20, stdin);
		rewind(stdin);
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')		str[i] = '\0';
		}
		for (int i = 0; i < numberOfSeries; ++i)
		{
			if (serial[i].isType != 1) continue;
			int temp = 0;
			if (strlen(serial[i].info.date) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (serial[i].info.date[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
					{
						serial = delExact(serial, numberOfSeries, i);
						numberOfSeries--;
						for (int i = 0; i < numberOfSeries; i++)
						{
							serial[i].size = numberOfSeries;
						}
						serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
					}
					flag = 1;
				}
			}
		}
		break;
	case 4:
		printf("Enter number of seasons: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfSeries; i++)
		{
			if (serial[i].isType != 2) continue;
			if (serial[i].info.seasons == intToSearch)
			{
				serial = delExact(serial, numberOfSeries, i);
				numberOfSeries--;
				for (int i = 0; i < numberOfSeries; i++)
				{
					serial[i].size = numberOfSeries;
				}
				serial = (Series*)realloc(serial, numberOfSeries * sizeof(Series));
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		system("CLS");
		return serial;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
	return serial;
}