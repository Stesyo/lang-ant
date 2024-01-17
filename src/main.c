#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "field.h"
#include "display.h"

int main(int argc, char *argv[])
{
	int width = 0; 
	int height = 0; 
	int iterations = 0;
	int rotation = 0;

	char *file_out = "";
	FILE *file_state = NULL;
	int black_fill = 0;

	int c;
	while ((c = getopt(argc, argv, "w:h:i:r:o:b:s:")) != -1) {
		switch (c) {
		case 'w':
			width = atoi(optarg);
			break;
		case 'h':
			height = atoi(optarg);
			break;
		case 'i':
			iterations = atoi(optarg);
			break;
		case 'r':
			switch (optarg[0]) {
			case 'N':
				rotation = N;
				break;
			case 'E':
				rotation = E;
				break;
			case 'S':
				rotation = S;
				break;
			case 'W':
				rotation = W;
				break;
			default:
				printf("Niepoprawny kierunek, mrówka przyjmuje kierunki: (N,E,S,W)\n");
				return 1;
			}
			break;
		case 'o':
			file_out = optarg;
			break;
		case 's':
			file_state = fopen(optarg, "r");
			break;
		case 'b':
			black_fill = atoi(optarg);
			break;
		case '?':
			break;
		default:
			printf("getopt zwrócił nieprawidłowy kod: %o\n", c);
			return 1;
		}
	}
	
	if (width == 0 || height == 0 || iterations == 0 || rotation == 0){
		printf("Program wywolac mozna z następującymi argumentami:\n");
		printf("\tWymagane:\n");
		printf("\t\t-w szerokosc planszy\n");
		printf("\t\t-h wysokosc planszy\n");
		printf("\t\t-i ilosc iteracji automatu\n");
		printf("\t\t-r kierunek mrowki (N|E|S|W)\n");
		printf("\tOpcjpnalne:\n");
		printf("\t\t-o naglowek pliku wyjsciowego\n");
		printf("\t\t-b zapelnienie planszy ciemnymi polami (w %%)\n");
		printf("\t\t-s plik wejsciowy\n");
		return 1;
	}

	struct Field field;
	if (file_state == NULL) {
		if (2 > width || 2 > height) {
			printf("Plansza jest za mała: %ix%i (min 2x2)\n", width, height);
			return 1;
		}

		field = field_new(width, height, rotation);
		field_fill(&field, black_fill);
	} else {
		field = field_load(file_state);
		fclose(file_state);
	}

	for (int i = 1; iterations >= i; i++) {
		field_step(&field);
		if (strlen(file_out)) {
			display_save(&field, i, file_out);
			
		} else {
			display_print(&field, i);
		}
	}

	field_free(&field);

	return 0;
}
