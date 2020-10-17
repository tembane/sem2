//num 4
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL, "RUS");
	int** ms;
	int s[3] = {0,0,0}, n = 0, i = 0, j = 0;
	printf_s("Введите кол-во строк и столбцов: ");
	scanf_s("%d", &n);
	ms = (int**)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		ms[i] = (int*)malloc(n * sizeof(int));
	printf_s("Введите элементы:\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (!scanf_s("%d", &ms[i][j])) {
				printf_s("Вы ввели не число. Введите элементы:\n");
				rewind(stdin);
			}
		}
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
		if ((ms[i][0] < 0) && (i < j)){
			s[0] += ms[i][j];
		}
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
		if ((ms[i][0] < 0) && (i == j)) {
			s[1] += ms[i][j];
		}
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
		if ((ms[i][0] < 0) && (i > j)) {
			s[2] += ms[i][j];
		}
	}
	printf_s("Сумма элементов выше главной диагонали: %d\n", s[0]);
	printf_s("Сумма элементов на главной диагонали: %d\n", s[1]);
	printf_s("Сумма элементов ниже главной диагонали: %d\n", s[2]);
	for (i = 0; i < n; i++)
		free(ms[i]);
	free(ms);
	return 0;
}