#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "field.h"
#include "display.h"

int main(int argc, char *argv[])
{
	if (argc == 1){
		printf("Program wywolac mozna z następującymi argumentami:\n");
		printf("	Wymagane:\n");
		printf("		-w szerokosc planszy\n");
		printf("		-h wysokosc planszy\n");
		printf("		-i ilosc iteracji automatu\n");
		printf("		-r kierunek mrowki\n");
		printf("	Opcjpnalne:\n");
		printf("		-o naglowek pliku wyjsciowego\n");
		printf("		-b zapelnienie planszy ciemnymi polami (w %)\n");
		printf("		-s plik wejsciowy\n");
		return 1;
	}
	if (argc < 5) {
		printf("Za mało argumentów: %i/4\n", argc - 1);
		printf("Wymagane argumenty:\n");
		printf("\t-szerokośc\n\t-wysokośc\n");
		printf("\t-ilość iteracji\n\t-kierunek mrówki (N|E|S|W)\n");
		printf("Opcjonalne argumenty:\n");
		return 1;
	}

	int width = 0; 
	int height = 0; 
	int iterations = 0;
	char direction;

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
		case 'r':
			direction = optarg[0];
			break;
		case 'o':
			file_out =optarg;
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
	
	struct Field field;
	if (file_state == NULL) {
		if (2 > width || 2 > height) {
			printf("Plansza jest za mała: %ix%i (min 2x2)\n", width, height);
			return 1;
		}
		int rotation;
		switch (direction) {
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
			printf("Niepoprawny kierunek, mrówka przyjmuje keirunki: (N,E,W,S)");
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
