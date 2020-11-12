#include <stdio.h>
#include <locale.h>
int main()
{
	int n;
	char *s;
	setlocale(LC_ALL, "RUS");
	printf("Введите кол-во элементов строки: ");
	while(!scanf_s("%d", &n))
	{
		printf("Ошибка ввода. Введите число:");
		rewind(stdin);
	}
	n++;
	// Выделение памяти
	s = (char*)malloc(n * sizeof(char));
	printf("Введите элементы строки: ");
	// Ввод строки
	for (int i = 0; i < n; i++)
	{
		s[i]=getchar();
	}
	printf("Элементы между двоеточиями:\n");
	// Отбор элементов между двумя двоеточиями
	for (int i = 0; i < n; i++)
	{
		if (s[i] == 58) 
		{
			i++;
			for (i; i < n; i++)
				if (s[i] != 58)
				{
					printf("%c", s[i]);
				}
				else
				{
					i = n;
				}
		}
	}
	// Очищение памяти
	free(s);
	return 0;
}