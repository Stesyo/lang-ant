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

	char *file_out = "";
	FILE *file_state = NULL;
	int black_fill = 0;

	/*
	 * Output_name | State_name | Black_fill %
	 * L not loadable filename with atoi == 0
	 *		 L loadable filename
	 *			      L not loadable filename with atoi != 0
	 */
	if (argc == 6) {
		char *last_str = argv[5];

		black_fill = atoi(last_str);
		file_state = fopen(last_str, "r");

		if (file_state == NULL && black_fill == 0) {
			file_out = last_str;
		}
	} else if (argc > 6) {
		file_out = argv[5];
		char *last_str = argv[6];

		black_fill = atoi(last_str);
		file_state = fopen(last_str, "r");
	}

	int iterations = atoi(argv[3]);
	struct Field field;
	if (file_state == NULL) {
		int width = atoi(argv[1]);
		int height = atoi(argv[2]);
		if (2 > width || 2 > height) {
			printf("Plansza jest za mała: %ix%i (min 2x2)\n", width, height);
			return 1;
		}

		field = field_new(width, height, 4);
		field_fill(&field, black_fill);
	} else {
		// field = field_load(file_state);
		fclose(file_state);
	}

	for (int i = 0; iterations > i; i++) {
		field_step(&field);

	}

	field_free(&field);

	return 0;
}
