#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
struct Flights
{
	int number;
	char destination[20];
	int time;
	int date;
	double price;
};
int menu(struct Flights* flight, int numberOfFlights)
{
	int choise;
	printf("Choose an operation (1-8):\n");
	printf("1) Add flight\n2) Show entered flights\n3) Change flight\n4) Search by the option\n5) Sort flights\n6) Delete flight\n7) Search by part of option\n8)Exit\n");
	while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 8))
	{
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choise)
	{
	case 1:
		add(flight, numberOfFlights);
		break;
	case 2:
		show(flight, numberOfFlights);
		break;
	case 3:
		change(flight, numberOfFlights);
		break;
	case 4:
		search(flight, numberOfFlights);
		break;
	case 5:
		sort(flight, numberOfFlights);
		break;
	case 6:
		del(flight, numberOfFlights);
		break;
	case 7:
		partSearch(flight, numberOfFlights);
		break;
	case 8:
		break;
	}
	return choise;
}
void add(struct Flights* flight, int numberOfFlights)
{
	int numberToAdd = 0, startToAdd=0;
	system("CLS");
	printf("Enter number of flights you want to add: ");
	if (numberOfFlights != 0)
	{
		startToAdd = numberOfFlights;
		while (!scanf_s("%d", &numberToAdd) || (numberToAdd < 1))
		{
			printf("Incorrect value. Try again...\n");
			rewind(stdin);
		}
		printf("\n");
		flight = (Flights*)realloc(flight, (numberToAdd+numberOfFlights)*sizeof(Flights));
	}
	else
	{
		while (!scanf_s("%d", &numberOfFlights) || (numberOfFlights < 1))
		{
			printf("Incorrect value. Try again...\n");
			rewind(stdin);
		}
		printf("\n");
		flight = (Flights*)calloc(numberOfFlights, sizeof(Flights));
	}
	numberOfFlights += numberToAdd;
	for (int i = startToAdd; i < numberOfFlights; i++)
	{
		printf("Note number: %d\n", i + 1);
		printf("Enter number of flight: ");
		while (!scanf_s("%d", &flight[i].number) || (flight[i].number < 1))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("Enter destination: ");
		rewind(stdin);
		fgets(flight[i].destination, 20, stdin);
		deleteEnter(flight, numberOfFlights, i);
		rightRegister(flight, numberOfFlights, i);
		rewind(stdin);
		printf("Enter date(YYYYMMDD): ");
		while (!scanf_s("%d", &flight[i].date) || (flight[i].date < 20000101) || (flight[i].date > 20301231))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("Enter time(HHMMSS): ");
		while (!scanf_s("%d", &flight[i].time) || (flight[i].time > 235959) || (flight[i].time < 1))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("Enter price: ");
		while (!scanf_s("%lf", &flight[i].price) || (flight[i].price <=0))
		{
			rewind(stdin);
			printf("Incorrect value\n");
		}
		printf("\n");
	}
	system("CLS");
	menu(flight, numberOfFlights);
}
void show(struct Flights* flight, int numberOfFlights)
{
	int choise=0;
	check(flight, numberOfFlights);
	system("CLS");
	printf("1)Show all notes\n2)Show 1 note\n");
	while (!scanf_s("%d", &choise) || (choise<1) ||(choise>2))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	if (choise == 1)
	{
		system("CLS");
		print(flight, numberOfFlights, -1);
		menu(flight, numberOfFlights);
		return;
	}
	else
	{
		printf("Enter number of note you want to see: ");
		while (!scanf_s("%d", &choise) || (choise < 1) || (choise > numberOfFlights))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		choise--;
		system("CLS");
		print(flight, numberOfFlights, choise);
		menu(flight, numberOfFlights);
		return;
	}
	menu(flight, numberOfFlights);
	return;
}
void change(struct Flights* flight, int numberOfFlights)
{
	int numberToChange = 0, choise;
	check(flight, numberOfFlights);
	system("CLS");
	print(flight, numberOfFlights, -1);
	printf("Enter number of note you want to change: ");
	while (!scanf_s("%d", &numberToChange) || (numberToChange < 1) || (numberToChange > numberOfFlights))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
	numberToChange--;
	int exit = 0;
	do
	{
		printf("1)Change number of flight\n");
		printf("2)Change destination\n");
		printf("3)Change date of flight\n");
		printf("4)Change time of flight\n");
		printf("5)Change price of flight\n");
		printf("6)Exit\n");
		while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 6))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		switch (choise)
		{
		case 1:
			printf("Enter new number of flight: ");
			while (!scanf_s("%d", &flight[numberToChange].number) || (flight[numberToChange].number < 1))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 2:
			printf("Enter new destination: ");
			rewind(stdin);
			fgets(flight[numberToChange].destination, 20, stdin);
			deleteEnter(flight, numberOfFlights, numberToChange);
			break;
		case 3:
			printf("\nEnter date(YYYYMMDD): ");
			while (!scanf_s("%d", &flight[numberToChange].date) || (flight[numberToChange].date < 20000101) || (flight[numberToChange].date > 20301231))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 4:
			printf("\nEnter time(HHMMSS): ");
			while (!scanf_s("%d", &flight[numberToChange].time) || (flight[numberToChange].time > 235959) || (flight[numberToChange].time < 1))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 5:
			printf("\nEnter price: ");
			while (!scanf_s("%lf", &flight[numberToChange].price) || (flight[numberToChange].price <= 0))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 6:
			exit = 1;
			break;
		}
	} while (exit!=1);
	system("CLS");
	menu(flight, numberOfFlights);
}
void del(struct Flights* flight, int numberOfFlights)
{
	int choise = 0;
	check(flight, numberOfFlights);
	system("CLS");
	printf("1)Delete all notes\n2)Delete 1 note\n3)Delete by option\n4)Exit\n");
	while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choise)
	{
	case 1:
		free(flight);
		system("CLS");
		printf("All notes were successfully deleted!\n");
		numberOfFlights = 0;
		break;
	case 2:
		printf("Enter number of note you want to delete: ");
		while (!scanf_s("%d", &choise) || (choise < 1) || (choise > numberOfFlights))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		choise--;
		delExact(flight, numberOfFlights, choise);
		break;
	case 3:
		deleteByTheOption(flight, numberOfFlights);
		return;
		break;
	case 4:
		menu(flight, numberOfFlights);
		return;
		break;
	}
	menu(flight, numberOfFlights);
}
void search(struct Flights* flight, int numberOfFlights)
{
	check(flight, numberOfFlights);
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Number of flight\n");
	printf("2)Destination\n");
	printf("3)Date\n");
	printf("4)Time\n");
	printf("5)Price\n");
	printf("6)Exit\n");
	int choise, intToSearch=0, flag=0;
	double doubleToSearch; 
	char str[20];
	while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 6))
	{
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choise)
	{
	case 1:
		printf("Enter number of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].number == intToSearch)
			{
				print(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 2:
		printf("Enter destination: ");
		rewind(stdin);
		fgets(str, 20, stdin);
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')
				for (i; i < 20; i++)
					str[i] = str[i + 1];
		}
		for (int i = 0; i < numberOfFlights; ++i)
		{
			int temp = 0;
			if (strlen(flight[i].destination) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (flight[i].destination[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(flight, numberOfFlights, i);
					flag = 1;
				}
			}
		}
		break;
	case 3:
		printf("Enter date of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].date == intToSearch)
			{
				print(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 4:
		printf("Enter time of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].time == intToSearch)
			{
				print(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		printf("Enter price of flight: ");
		while (!scanf_s("%lf", &doubleToSearch) || (doubleToSearch <=0))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].price == doubleToSearch)
			{
				print(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
	menu(flight, numberOfFlights);
}
void sort(struct Flights* flight, int numberOfFlights)
{
	check(flight, numberOfFlights);
	system("CLS");
	printf("How to sort:\n");
	printf("1)From Min to Max\n");
	printf("2)From Max to Min\n");
	printf("3)Exit\n");
	int choise;
	while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choise)
	{
	case 1:
		system("CLS");
		sortFromMin(flight, numberOfFlights);
		return;
		break;
	case 2:
		system("CLS");
		sortFromMax(flight, numberOfFlights);
		return;
		break;
	case 3:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
		break;
	}
	menu(flight, numberOfFlights);
}
void sortFromMin(struct Flights* flight, int numberOfFlights)
{
	check(flight, numberOfFlights);
	struct Flights temp;
	int choise;
	system("CLS");
	print(flight, numberOfFlights, -1);
	printf("1)Sort by number of flight\n");
	printf("2)Sort by destination\n");
	printf("3)Sort by date of flight\n");
	printf("4)Sort by time of flight\n");
	printf("5)Sort by price of flight\n");
	printf("6)Exit\n");
	while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 6))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (choise)
	{
	case 1:
		for (int i = 0; i < numberOfFlights ; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].number > flight[j + 1].number)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j+ 1] = temp;
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int z = numberOfFlights-2; z >= i; z--)
			{
				for (int j = 0; j < strlen(flight[z].destination); j++)
				{
					if (flight[z].destination[j] > flight[z + 1].destination[j])
					{
						temp = flight[z];
						flight[z] = flight[z + 1];
						flight[z + 1] = temp;
						j = strlen(flight[z].destination);
					}
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].date > flight[j + 1].date)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 4:
		for (int i = 0; i < numberOfFlights ; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].time > flight[j + 1].time)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 5:
		for (int i = 0; i < numberOfFlights ; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].price > flight[j + 1].price)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
	}
	system("CLS");
	menu(flight, numberOfFlights);
}
void sortFromMax(struct Flights* flight, int numberOfFlights)
{
	check(flight, numberOfFlights);
	struct Flights temp;
	int choise;
	system("CLS");
	print(flight, numberOfFlights, -1);
	printf("1)Sort by number of flight\n");
	printf("2)Sort by destination\n");
	printf("3)Sort by date of flight\n");
	printf("4)Sort by time of flight\n");
	printf("5)Sort by price of flight\n");
	printf("6)Exit\n");
	while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 6))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (choise)
	{
	case 1:
		for (int i = 0; i < numberOfFlights ; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].number < flight[j + 1].number)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < numberOfFlights; i++)
		{
			for (int z = 0; z < numberOfFlights - 1; z++)
			{
				for (int j = 0; j < strlen(flight[z].destination); j++)
				{
					if (flight[z].destination[j] < flight[z + 1].destination[j])
					{
						temp = flight[z];
						flight[z] = flight[z + 1];
						flight[z + 1] = temp;
						j = strlen(flight[z].destination);
					}
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < numberOfFlights ; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].date < flight[j + 1].date)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 4:
		for (int i = 0; i < numberOfFlights ; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].time < flight[j + 1].time)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 5:
		for (int i = 0; i < numberOfFlights ; i++)
		{
			for (int j = 0; j < numberOfFlights - 1; j++)
			{
				if (flight[j].price < flight[j + 1].price)
				{
					temp = flight[j];
					flight[j] = flight[j + 1];
					flight[j + 1] = temp;
				}
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
	}
	system("CLS");
	menu(flight, numberOfFlights);
}
void check(struct Flights* flight, int numberOfFlights)
{
	if (numberOfFlights == 0)
	{
		printf("Ooops...No notes found.\n");
		menu(flight, numberOfFlights);
		return;
	}
}
void print(struct Flights* flight, int numberOfFlights, int flightToPrint)
{
	char table[] = "F L I G H T S";
	printLine();
	printf("|\t\t\t\t\t %-58s|\n", table);	
	printLine();
	printf("|\t%-5s|\t%-10s|\t%-19s|\t%-10s|\t%-10s|\t%-11s|\n", "Note", "Number", "Destination", "Date", "Time", "Price");
	printLine();
	if (flightToPrint != -1)
	{
		printf("|\t%-5d|\t%-10d|\t%-19s|\t%-10d|\t%-10d|\t%-11.2lf|\n",
			flightToPrint+1,flight[flightToPrint].number, (flight + flightToPrint)->destination,
			flight[flightToPrint].date, flight[flightToPrint].time,
			flight[flightToPrint].price);
		printLine();
	}
	else
	{
		for (int i = 0; i < numberOfFlights; i++)
		{
			printf("|\t%-5d|\t%-10d|\t%-19s|\t%-10d|\t%-10d|\t%-11.2lf|\n",
				i+1,flight[i].number, (flight + i)->destination,
				flight[i].date, flight[i].time,
				flight[i].price);
			printLine();
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
void deleteEnter(struct Flights* flight, int numberOfFlights, int numberOfStructure)
{
	for (int i = 0; i < 20; i++)
	{
		if (flight[numberOfStructure].destination[i] == '\n')
			for (i; i < 20; i++)
				flight[numberOfStructure].destination[i] = flight[numberOfStructure].destination[i + 1];
	}
}
void partSearch(struct Flights* flight, int numberOfFlights)
{
	check(flight, numberOfFlights);
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Number of flight\n");
	printf("2)Destination\n");
	printf("3)Exit\n");
	int choise;
	while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (choise)
	{
	case 1:
		system("CLS");
		printf("Enter symbols of number (*a*b*): ");
		findCharNumber(flight, numberOfFlights);
		break;
	case 2:
		system("CLS");
		printf("Enter symbols of destination (*a*b*): ");
		findChar(flight, numberOfFlights);
		break;
	case 3:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
		break;
	}
	menu(flight, numberOfFlights);
}
void findChar(struct Flights* flight, int numberOfFlights)
{
	char str[20];
	char compareChar;
	int flag = 0, flag1 = 0;
	rewind(stdin);
	fgets(str, 20, stdin);
	rewind(stdin);
	for (int l = 0; l < numberOfFlights; l++) //по структурным переменным
	{
		int j = 0, i = 0, j1 = 0;
		for (i; i < strlen(str); i++) //по строке поиска
		{
			while ((str[i] != '*') && (str[i] != '\n') && (str[i] != '\0'))
			{
				compareChar = str[i];
				flag1++;
				for (j = j1; j < strlen(flight[l].destination); j++)
				{
					if (flight[l].destination[j] == compareChar)
					{
						flag++;
						j1 = j;
						j = strlen(flight[l].destination);
					}
				}
				break;
			}
		}
		if ((flag == flag1) && (flag1 != 0))	print(flight, numberOfFlights, l);
		flag = 0;
		flag1 = 0;
	}
}
void findCharNumber(struct Flights* flight, int numberOfFlights)
{
	char str[20], str2[20]; //str1 для искомого, str2 для структурного int
	char compareChar;
	int flag = 0, flag1 = 0;
	rewind(stdin);
	fgets(str, 20, stdin);
	rewind(stdin);
	for (int l = 0; l < numberOfFlights; l++) //по структурным переменным
	{
		sprintf_s(str2, "%d", flight[l].number); //переводим int в char
		int j = 0, i = 0, j1 = 0;
		for (i; i < strlen(str); i++) //по строке поиска
		{
			while ((str[i] != '*') && (str[i] != '\n') && (str[i] != '\0'))
			{
				compareChar = str[i];
				flag1++;
				for (j = j1; j < strlen(str2); j++)
				{
					if (str2[j] == compareChar)
					{
						flag++;
						j1 = j;
						j = strlen(str2);
					}
				}
				break;
			}
		}
		if ((flag == flag1) && (flag1 != 0))	print(flight, numberOfFlights, l);
		flag = 0;
		flag1 = 0;
	}
}
void deleteByTheOption(struct Flights* flight, int numberOfFlights)
{
	check(flight, numberOfFlights);
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Number of flight\n");
	printf("2)Destination\n");
	printf("3)Date\n");
	printf("4)Time\n");
	printf("5)Price\n");
	printf("6)Exit\n");
	int choise, intToSearch = 0, flag = 0;
	double doubleToSearch;
	char str[20];
	while (!scanf_s("%d", &choise) || (choise < 1) || (choise > 6))
	{
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (choise)
	{
	case 1:
		printf("Enter number of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].number == intToSearch)
			{
				delExact(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 2:
		printf("Enter destination: ");
		rewind(stdin);
		fgets(str, 20, stdin);
		for (int i = 0; i < 20; i++)
		{
			if (str[i] == '\n')
				for (i; i < 20; i++)
					str[i] = str[i + 1];
		}
		for (int i = 0; i < numberOfFlights; ++i)
		{
			int temp = 0;
			if (strlen(flight[i].destination) == strlen(str))
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (flight[i].destination[j] != str[j])
						break;
					else
						temp++;
					if (temp == strlen(str))
						print(flight, numberOfFlights, i);
					delExact(flight, numberOfFlights, i);
					flag = 1;
					break;
				}
			}
		}						
		break;
	case 3:
		printf("Enter date of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].date == intToSearch)
			{
				delExact(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 4:
		printf("Enter time of flight: ");
		while (!scanf_s("%d", &intToSearch) || (intToSearch < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].time == intToSearch)
			{
				delExact(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		printf("Enter price of flight: ");
		while (!scanf_s("%lf", &doubleToSearch) || (doubleToSearch <= 0))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < numberOfFlights; i++)
		{
			while (flight[i].price == doubleToSearch)
			{
				delExact(flight, numberOfFlights, i);
				flag = 1;
				break;
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, numberOfFlights);
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
	menu(flight, numberOfFlights);
}
void delExact(struct Flights* flight, int numberOfFlights, int flightNumber)
{
	for (int i = flightNumber; i < numberOfFlights; i++)
	{
		flight[i] = flight[i + 1];
	}
	numberOfFlights--;
	flight = (Flights*)realloc(flight, numberOfFlights * sizeof(Flights));
	system("CLS");
	printf("Note was successfully deleted!\n");
	menu(flight, numberOfFlights);
}
void rightRegister(struct Flights* flight, int numberOfFlights, int numberOfStructure)
{
	if ((flight[numberOfStructure].destination[0] >= 'a') && (flight[numberOfStructure].destination[0] <= 'z'))
		flight[numberOfStructure].destination[0] -= 32;
	for (int i = 1; i < 20; i++)
	{
		if ((flight[numberOfStructure].destination[i] >= 'A') && (flight[numberOfStructure].destination[i] <= 'Z'))
			flight[numberOfStructure].destination[i] += 32;
	}
	for (int i = 1; i < 20; i++)
	{
		if ((flight[numberOfStructure].destination[i] >= 'a') && (flight[numberOfStructure].destination[i] <= 'z') &&
			(((flight[numberOfStructure].destination[i-1])=='-') || ((flight[numberOfStructure].destination[i - 1]) == ' ')))
			flight[numberOfStructure].destination[i] -= 32;
	}
}