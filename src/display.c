#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <sys/stat.h>

#include "field.h"
#include "display.h"


wchar_t line_vertical = L'│';
wchar_t line_horizontal = L'─';
wchar_t line_down_right = L'┌';
wchar_t line_down_left = L'┐';
wchar_t line_up_right = L'└';
wchar_t line_up_left = L'┘';
wchar_t square_white = L' ';
wchar_t square_black = L'█';
wchar_t arrow_north_white = L'△';
wchar_t arrow_north_black = L'▲';
wchar_t arrow_east_white = L'▷';
wchar_t arrow_east_black = L'▶';
wchar_t arrow_south_white = L'▽';
wchar_t arrow_south_black = L'▼';
wchar_t arrow_west_white = L'◁';
wchar_t arrow_west_black = L'◀';

wchar_t **display = NULL;
int display_x = 0;
int display_y = 0;
int iter_digits = 0;

struct Field field_load(FILE *file_state)
{
	setlocale(LC_ALL, "C.UTF-8");

	int width = 0;
	int height = -2;

	wchar_t wc;
	while ((wc = fgetwc(file_state)) != WEOF) {
		if        (wc == line_horizontal 
			|| wc == line_vertical
			|| wc == line_down_right
			|| wc == line_down_left
			|| wc == line_up_right
			|| wc == line_up_left
		) {
			continue;
		}

		if (wc == L'\n')
			height += 1;
		if (height == 0 && wc != L'\n')
			width += 1;
	}
	rewind(file_state);

	if (width == 0 || height == 0) {
		wprintf(L"Grid too small\n");
		exit(1);
	}

	struct Ant ant;
	int **grid = malloc(height * sizeof(int *));
	for (int i = 0; height > i; i++) {
		grid[i] = malloc(width * sizeof(int));
	}

	int x = -1;
	int y = -1;
	while ((wc = fgetwc(file_state)) != WEOF) {
		switch (wc) {
		case L'\n':
			x = -1;
			y += 1;
			break;
		case L' ':
			grid[y][x] = 0;
			x += 1;
			break;
		case L'█':
			grid[y][x] = 1;
			x += 1;
			break;
		case L'△':
			grid[y][x] = 0;
			ant.x = x;
			ant.y = y;
			ant.rotation = N;
			x += 1;
			break;
		case L'▲':
			grid[y][x] = 1;
			ant.x = x;
			ant.y = y;
			ant.rotation = N;
			x += 1;
			break;
		case L'▷':
			grid[y][x] = 0;
			ant.x = x;
			ant.y = y;
			ant.rotation = E;
			x += 1;
			break;
		case L'▶':
			grid[y][x] = 1;
			ant.x = x;
			ant.y = y;
			ant.rotation = E;
			x += 1;
			break;
		case L'▽':
			grid[y][x] = 0;
			ant.x = x;
			ant.y = y;
			ant.rotation = S;
			x += 1;
			break;
		case L'▼':
			grid[y][x] = 1;
			ant.x = x;
			ant.y = y;
			ant.rotation = S;
			x += 1;
			break;
		case L'◁':
			grid[y][x] = 0;
			ant.x = x;
			ant.y = y;
			ant.rotation = W;
			x += 1;
			break;
		case L'◀':		
			grid[y][x] = 1;
			ant.x = x;
			ant.y = y;
			ant.rotation = W;
			x += 1;
			break;
		}
	}
	struct Field field = {width, height, grid};
	field.ant = ant;
	return field;
}

int get_digits(int value) {
	if (value == 0) {
		return 1;
	}
	int n = 0;
	while (value != 0) { 
		value = value / 10; 
		n++; 
	} 
	return n;
}

wchar_t get_char(struct Field *field, int x, int y) 
{
	if (x == field->ant.x && y == field->ant.y && field->grid[y][x] == 0) {
		switch (field->ant.rotation)
		{
		case 1:
			return(arrow_north_white);
			break;
		case 2:
			return(arrow_east_white);
			break;
		case 3:
			return(arrow_south_white);
			break;
		case 4:
			return(arrow_west_white);
			break;
		default:
			printf("Invalid ant rotation\n");
			exit(1);
		}
	} else if (x == field->ant.x && y == field->ant.y && field->grid[y][x] == 1) {
		switch (field->ant.rotation)
		{
		case 1:
			return(arrow_north_black);
			break;
		case 2:
			return(arrow_east_black);
			break;
		case 3:
			return(arrow_south_black);
			break;
		case 4:
			return(arrow_west_black);
			break;
		default:
			printf("Invalid ant rotation\n");
			exit(1);
		}

	} else if (field->grid[y][x] == 0) {
		return(square_white);
	} else if (field->grid[y][x] == 1) {
		return(square_black);
	}
	printf("Invalid value in grid: [%ix%i]\n", x, y);
	exit(1);
}

void display_init(struct Field *field, int iterations)
{
	setlocale(LC_ALL, "C.UTF-8");

	iter_digits = get_digits(iterations);
	display_x = field->width + 2;
	display_y = field->height + 2;
	display = malloc(display_y * sizeof(wchar_t *));
	for (int i = 0 ; display_y > i; i++) {
		display[i] = malloc((display_x + 1) * sizeof(wchar_t));
	}

	display[0][0] = line_down_right;
	display[0][display_x - 1] = line_down_left;
	display[display_y - 1][0] = line_up_right;
	display[display_y - 1][display_x - 1] = line_up_left;

	display[0][display_x] = L'\0';
	display[display_y - 1][display_x] = L'\0';
	for(int i = 0; field->width > i; i++) {
		display[0][1 + i] = line_horizontal;
		display[display_y - 1][1 + i] = line_horizontal;
	}

	for (int y = 1; field->height + 1 > y; y++) {
		display[y][0] = line_vertical;
		display[y][display_x - 1] = line_vertical;
		display[y][display_x] = L'\0';

		for (int x = 1; field->width + 1 > x; x++) {
			display[y][x] = get_char(field, x - 1, y - 1);
		}
	}
}

void display_free(void)
{
	for (int i = 0; display_y > i; i++) {
		free(display[i]);
	}
	free(display);
}

void display_update(struct Field *field, int tile) {
	int tile_x = tile % field->width;
	int tile_y = tile / field->width;
	
	display[tile_y + 1][tile_x + 1] = get_char(field, tile_x, tile_y);
	display[field->ant.y + 1][field->ant.x + 1] = get_char(field, field->ant.x, field->ant.y);
}

void display_print(struct Field *field, int iteration)
{
	wprintf(L"Iteration: %i\n", iteration);
	for (int y = 0; field->height + 2 > y; y++) {
		wprintf(L"%ls\n", display[y]);
	}
}

void display_save(struct Field *field, int iteration, char *file_out)
{
	int name_len = 2 * strlen(file_out) + iter_digits + 7;
	char *file_name = malloc(name_len * sizeof(char));
	int digits = get_digits(iteration);


	sprintf(file_name, "%s/%s_", file_out, file_out);
	sprintf(file_name + (2 * strlen(file_out) + 2 + iter_digits - digits), "%i.txt", iteration);
	for (int i = 0; iter_digits - digits > i; i++)
		file_name[i + 2 * strlen(file_out) + 2] = '0';

	mkdir(file_out, 0755);
	FILE *file = fopen(file_name, "w");
	for (int y = 0; field->height + 2 > y; y++) {
		fwprintf(file, L"%ls\n", display[y]);
	}
	fclose(file);
}
