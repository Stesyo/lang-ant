#include <stdlib.h>
#include <stdio.h>

#include "field.h"
#include "display.h"

int main(int argc, char *argv[])
{
	if (argc < 5) {
		printf("Za mało argumentów: %i/4\n", argc - 1);
		printf("Wymagane argumenty:\n");
		printf("\t-szerokośc\n\t-wysokośc\n");
		printf("\t-ilość iteracji\n\t-kierunek mrówki (N|E|S|W)\n");
		printf("Opcjonalne argumenty:\n");
		printf("\t-nazwa wyjściowa\n");
		printf("\t-stan wejściowy (nazwa pliku) | %% zapełnienia (0-100)\n");
		return 1;
	}
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int iterations = atoi(argv[3]);
	if (2 > width || 2 > height) {
		printf("Plansza jest za mała: %ix%i (min 2x2)\n", width, height);
		return 1;
	}

	struct Field field = field_new(width, height, 4);
	for (int i = 0; iterations > i; i++) {
		field_step(&field);

	}
	field_free(&field);

	return 0;
}
