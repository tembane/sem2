#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
int main()
{
	struct Flights* flight=NULL;
	int k=0;
	int n=menu(flight, k);
	while (n == 8)
	{
		free(flight);
		return 0;
	}
	return 0;
}