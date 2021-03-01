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
int menu(struct Flights* flight, int k)
{
	int n;
	printf("Choose an operation (1-8):\n");
	printf("1) Add flight\n2) Show entered flights\n3) Change flight\n4) Search by the option\n5) Sort flights\n6) Delete flight\n7) Search by part of option\n8)Exit\n");
	while (!scanf_s("%d", &n) || (n < 1) || (n > 8))
	{
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (n)
	{
	case 1:
		add(flight, k);
		break;
	case 2:
		show(flight, k);
		break;
	case 3:
		change(flight, k);
		break;
	case 4:
		search(flight, k);
		break;
	case 5:
		sort(flight, k);
		break;
	case 6:
		del(flight, k);
		break;
	case 7:
		partSearch(flight, k);
		break;
	case 8:
		break;
	}
	return n;
}
void add(struct Flights* flight, int k)
{
	int k1 = 0, k2=0;
	system("CLS");
	printf("Enter number of flights you want to add: ");
	if (k != 0)
	{
		k2 = k;
		while (!scanf_s("%d", &k1) || (k1 < 1))
		{
			printf("Incorrect value. Try again...\n");
			rewind(stdin);
		}
		printf("\n");
		flight = (Flights*)realloc(flight, (k1+k)*sizeof(Flights));
	}
	else
	{
		while (!scanf_s("%d", &k) || (k < 1))
		{
			printf("Incorrect value. Try again...\n");
			rewind(stdin);
		}
		printf("\n");
		flight = (Flights*)calloc(k, sizeof(Flights));
	}
	k += k1;
	for (int i = k2; i < k; i++)
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
		deleteEnter(flight, k, i);
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
	menu(flight, k);
}
void show(struct Flights* flight, int k)
{
	int n=0;
	check(flight, k);
	system("CLS");
	printf("1)Show all notes\n2)Show 1 note\n");
	while (!scanf_s("%d", &n) || (n<1) ||(n>2))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	if (n == 1)
	{
		system("CLS");
		print(flight, k, -1);
	}
	else
	{
		printf("Enter number of note you want to see: ");
		while (!scanf_s("%d", &n) || (n < 1) || (n > k))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		n--;
		system("CLS");
		print(flight, k, n);
	}
	menu(flight, k);
}
void change(struct Flights* flight, int k)
{
	int n = 0, s;
	check(flight, k);
	system("CLS");
	print(flight, k, -1);
	printf("Enter number of note you want to change: ");
	if (k != 0)
	{
		while (!scanf_s("%d", &n) || (n < 1) || (n > k))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		n--;
	}
	int f = 0;
	do
	{
		printf("1)Change number of flight\n");
		printf("2)Change destination\n");
		printf("3)Change date of flight\n");
		printf("4)Change time of flight\n");
		printf("5)Change price of flight\n");
		printf("6)Exit\n");
		while (!scanf_s("%d", &s) || (s < 1) || (s > 6))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		switch (s)
		{
		case 1:
			printf("Enter new number of flight: ");
			while (!scanf_s("%d", &flight[n].number) || (flight[n].number < 1))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 2:
			printf("Enter new destination: ");
			rewind(stdin);
			fgets(flight[n].destination, 20, stdin);
			deleteEnter(flight, k, n);
			break;
		case 3:
			printf("\nEnter date(YYYYMMDD): ");
			while (!scanf_s("%d", &flight[n].date) || (flight[n].date < 10000000) || (flight[n].date > 30000000))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 4:
			printf("\nEnter time(HHMM): ");
			while (!scanf_s("%d", &flight[n].time) || (flight[n].time > 235959) || (flight[n].time < 1))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 5:
			printf("\nEnter price: ");
			while (!scanf_s("%lf", &flight[n].price) || (flight[n].price <= 0))
			{
				rewind(stdin);
				printf("Incorrect value\n");
			}
			break;
		case 6:
			f = 1;
			break;
		}
	} while (f!=1);
	system("CLS");
	menu(flight, k);
}
void del(struct Flights* flight, int k)
{
	int n = 0;
	check(flight, k);
	system("CLS");
	printf("1)Delete all notes\n2)Delete 1 note\n");
	while (!scanf_s("%d", &n) || (n < 1) || (n > 2))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	if (n == 1)
	{
		free(flight);
		system("CLS");
		printf("All notes were successfully deleted!\n");
		k = 0;
	}
	else
	{
		printf("Enter number of note you want to delete: ");
		while (!scanf_s("%d", &n) || (n < 1) || (n > k))
		{
			printf("Incorrect value. Try again.\n");
			rewind(stdin);
		}
		n--;
		for (int i = n; i < k; i++)
		{
			flight[i] = flight[i + 1];
		}
		k--;
		system("CLS");
		printf("Note was successfully deleted!\n");
	}
	menu(flight, k);
}
void search(struct Flights* flight, int k)
{
	check(flight, k);
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Number of flight\n");
	printf("2)Destination\n");
	printf("3)Date\n");
	printf("4)Time\n");
	printf("5)Price\n");
	printf("6)Exit\n");
	int n, s=0, flag=0;
	double s1; 
	char str[20];
	while (!scanf_s("%d", &n) || (n < 1) || (n > 6))
	{
		printf("Incorrect value\n");
		rewind(stdin);
	}
	switch (n)
	{
	case 1:
		printf("Enter number of flight: ");
		while (!scanf_s("%d", &s) || (s < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < k; i++)
		{
			while (flight[i].number == s)
			{
				print(flight, k, i);
				flag = 1;
				break;
			}
		}
		break;
	case 2:
		printf("Enter destination: ");
		rewind(stdin);
		fgets(str, 20, stdin);
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; (j < strlen(str)) || (j < strlen(flight[i].destination)); j++)
			{
				if (flight[i].destination[j] != str[j]) break;
				else
				{
					if ((i == k - 1) && (j < strlen(str)) || (j < strlen(flight[i].destination)))
					{
						print(flight, k, i);
							flag = 1;
							break;
					}
				}
			}
		}
		break;
	case 3:
		printf("Enter date of flight: ");
		while (!scanf_s("%d", &s) || (s < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < k; i++)
		{
			while (flight[i].date == s)
			{
				print(flight, k, i);
				flag = 1;
				break;
			}
		}
		break;
	case 4:
		printf("Enter time of flight: ");
		while (!scanf_s("%d", &s) || (s < 1))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < k; i++)
		{
			while (flight[i].time == s)
			{
				print(flight, k, i);
				flag = 1;
				break;
			}
		}
		break;
	case 5:
		printf("Enter price of flight: ");
		while (!scanf_s("%lf", &s1) || (s1 <=0))
		{
			printf("Incorrect value\n");
			rewind(stdin);
		}
		for (int i = 0; i < k; i++)
		{
			while (flight[i].price == s1)
			{
				print(flight, k, i);
				flag = 1;
				break;
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, k);
		return;
		break;
	}
	if (flag == 0) printf("Nothing found...Try again.\n");
	menu(flight, k);
}
void sort(struct Flights* flight, int k)
{
	check(flight, k);
	system("CLS");
	printf("How to sort:\n");
	printf("1)From Min to Max\n");
	printf("2)From Max to Min\n");
	printf("3)Exit\n");
	int n;
	while (!scanf_s("%d", &n) || (n < 1) || (n > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (n)
	{
	case 1:
		system("CLS");
		sortFromMin(flight, k);
		return;
		break;
	case 2:
		system("CLS");
		sortFromMax(flight, k);
		return;
		break;
	case 3:
		system("CLS");
		menu(flight, k);
		return;
		break;
	}
	menu(flight, k);
}
void sortFromMin(struct Flights* flight, int k)
{
	check(flight, k);
	struct Flights temp;
	int s;
	int f = 0;
	system("CLS");
	print(flight, k, -1);
	printf("1)Sort by number of flight\n");
	printf("2)Sort by destination\n");
	printf("3)Sort by date of flight\n");
	printf("4)Sort by time of flight\n");
	printf("5)Sort by price of flight\n");
	printf("6)Exit\n");
	while (!scanf_s("%d", &s) || (s < 1) || (s > 6))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (s)
	{
	case 1:
		for (int i = 0; i < k - 1; i++)
		{
			if (flight[i].number > flight[i + 1].number)
			{
				temp = flight[i];
				flight[i] = flight[i + 1];
				flight[i + 1] = temp;
			}
		}
		break;
	case 2:
		for (int i = 0; i < k - 1; i++)
		{
			for (int j = 0; j < strlen(flight[i].destination); j++)
			{
				if (flight[i].destination[j] > flight[i + 1].destination[j])
				{
					temp = flight[i];
					flight[i] = flight[i + 1];
					flight[i + 1] = temp;
					j = strlen(flight[i].destination);
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < k - 1; i++)
		{
			if (flight[i].date > flight[i + 1].date)
			{
				temp = flight[i];
				flight[i] = flight[i + 1];
				flight[i + 1] = temp;
			}
		}
		break;
	case 4:
		for (int i = 0; i < k - 1; i++)
		{
			if (flight[i].time > flight[i + 1].time)
			{
				temp = flight[i];
				flight[i] = flight[i + 1];
				flight[i + 1] = temp;
			}
		}
		break;
	case 5:
		for (int i = 0; i < k - 1; i++)
		{
			if (flight[i].price > flight[i + 1].price)
			{
				temp = flight[i];
				flight[i] = flight[i + 1];
				flight[i + 1] = temp;
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, k);
		return;
	}
	system("CLS");
	menu(flight, k);
}
void sortFromMax(struct Flights* flight, int k)
{
	check(flight, k);
	struct Flights temp;
	int s;
	int f = 0;
	system("CLS");
	print(flight, k, -1);
	printf("1)Sort by number of flight\n");
	printf("2)Sort by destination\n");
	printf("3)Sort by date of flight\n");
	printf("4)Sort by time of flight\n");
	printf("5)Sort by price of flight\n");
	printf("6)Exit\n");
	while (!scanf_s("%d", &s) || (s < 1) || (s > 6))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	switch (s)
	{
	case 1:
		for (int i = 0; i < k - 1; i++)
		{
			if (flight[i].number < flight[i + 1].number)
			{
				temp = flight[i];
				flight[i] = flight[i + 1];
				flight[i + 1] = temp;
			}
		}
		break;
	case 2:
		for (int i = 0; i < k - 1; i++)
		{
			for (int j = 0; j < strlen(flight[i].destination); j++)
			{
				if (flight[i].destination[j] < flight[i + 1].destination[j])
				{
					temp = flight[i];
					flight[i] = flight[i + 1];
					flight[i + 1] = temp;
					j = strlen(flight[i].destination);
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < k - 1; i++)
		{
			if (flight[i].date < flight[i + 1].date)
			{
				temp = flight[i];
				flight[i] = flight[i + 1];
				flight[i + 1] = temp;
			}
		}
		break;
	case 4:
		for (int i = 0; i < k - 1; i++)
		{
			if (flight[i].time < flight[i + 1].time)
			{
				temp = flight[i];
				flight[i] = flight[i + 1];
				flight[i + 1] = temp;
			}
		}
		break;
	case 5:
		for (int i = 0; i < k - 1; i++)
		{
			if (flight[i].price < flight[i + 1].price)
			{
				temp = flight[i];
				flight[i] = flight[i + 1];
				flight[i + 1] = temp;
			}
		}
		break;
	case 6:
		system("CLS");
		menu(flight, k);
		return;
	}
	system("CLS");
	menu(flight, k);
}
void check(struct Flights* flight, int k)
{
	if (k == 0)
	{
		printf("Ooops...No notes found.\n");
		menu(flight, k);
		return;
	}
}
void print(struct Flights* flight, int k, int j)
{
	char table[] = "F L I G H T S";
	printLine();
	printf("|\t\t\t %-66s|\n", table);
	printLine();
	printf("|\t%-10s|\t%-19s|\t%-10s|\t%-10s|\t%-11s|\n", "Number", "Destination", "Date", "Time", "Price");
	printLine();
	if (j != -1)
	{
		printf("|\t%-10d|\t%-19s|\t%-10d|\t%-10d|\t%-11.2lf|\n",
			flight[j].number, (flight + j)->destination,
			flight[j].date, flight[j].time,
			flight[j].price);
		printLine();
	}
	else
	{
		for (int i = 0; i < k; i++)
		{
			printf("|\t%-10d|\t%-19s|\t%-10d|\t%-10d|\t%-11.2lf|\n",
				flight[i].number, (flight + i)->destination,
				flight[i].date, flight[i].time,
				flight[i].price);
			printLine();
		}
	}
}
void printLine()
{
	for (int i = 0; i < 92; i++)
	{
		printf("%c", '-');
	}
	printf("\n");
}
void deleteEnter(struct Flights* flight, int k, int n)
{
	for (int i = 0; i < 20; i++)
	{
		if (flight[n].destination[i] == '\n')
			for (i; i < 20; i++)
				flight[n].destination[i] = flight[n].destination[i + 1];
	}
}
void partSearch(struct Flights* flight, int k)
{
	check(flight, k);
	system("CLS");
	printf("Select option to search:\n");
	printf("1)Number of flight\n");
	printf("2)Destination\n");
	printf("3)Exit\n");
	int n;
	while (!scanf_s("%d", &n) || (n < 1) || (n > 3))
	{
		printf("Incorrect value. Try again.\n");
		rewind(stdin);
	}
	printf("\n");
	switch (n)
	{
	case 1:
		system("CLS");
		printf("Enter symbols of number (*a*b*): ");
		findCharNumber(flight, k);
		break;
	case 2:
		system("CLS");
		printf("Enter symbols of destination (*a*b*): ");
		findChar(flight, k);
		break;
	case 3:
		system("CLS");
		menu(flight, k);
		return;
		break;
	}
	menu(flight, k);
}
void findChar(struct Flights* flight, int k)
{
	char str[20];
	char s;
	int i = 0, j = 0, j1 = 0, flag = 0, flag1 = 0;
	rewind(stdin);
	fgets(str, 20, stdin);
	rewind(stdin);
	for (int l = 0; l < k; l++) //по структурным переменным
	{
		j = 0, i = 0, j1 = 0;
		for (i; i < strlen(str); i++) //по строке поиска
		{
			while ((str[i] != '*') && (str[i] != '\n') && (str[i] != '\0'))
			{
				s = str[i];
				flag1++;
				for (j = j1; j < strlen(flight[l].destination); j++)
				{
					if (flight[l].destination[j] == s)
					{
						flag++;
						j1 = j;
						j = strlen(flight[l].destination);
					}
				}
				break;
			}
		}
		if ((flag == flag1) && (flag1 != 0))	print(flight, k, l);
		flag = 0;
		flag1 = 0;
	}
}
void findCharNumber(struct Flights* flight, int k)
{
	char str[20], str2[20];
	char s;
	int i = 0, j = 0, j1 = 0, flag = 0, flag1 = 0;
	rewind(stdin);
	fgets(str, 20, stdin);
	rewind(stdin);
	for (int l = 0; l < k; l++) //по структурным переменным
	{
		sprintf_s(str2, "%d", flight[l].number);
		j = 0, i = 0, j1 = 0;
		for (i; i < strlen(str); i++) //по строке поиска
		{
			while ((str[i] != '*') && (str[i] != '\n') && (str[i] != '\0'))
			{
				s = str[i];
				flag1++;
				for (j = j1; j < strlen(str2); j++)
				{
					if (str2[j] == s)
					{
						flag++;
						j1 = j;
						j = strlen(str2);
					}
				}
				break;
			}
		}
		if ((flag == flag1) && (flag1 != 0))	print(flight, k, l);
		flag = 0;
		flag1 = 0;
	}
}