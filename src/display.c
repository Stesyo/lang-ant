#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <sys/stat.h>

#include "field.h"
#include "display.h"


wchar_t *line_vertical = L"│";
wchar_t *line_horizontal = L"─";
wchar_t *line_down_right = L"┌";
wchar_t *line_down_left = L"┐";
wchar_t *line_up_right = L"└";
wchar_t *line_up_left = L"┘";
wchar_t *square_white = L" ";
wchar_t *square_black = L"█";
wchar_t *arrow_north_white = L"△";
wchar_t *arrow_north_black = L"▲";
wchar_t *arrow_east_white = L"▷";
wchar_t *arrow_east_black = L"▶";
wchar_t *arrow_south_white = L"▽";
wchar_t *arrow_south_black = L"▼";
wchar_t *arrow_west_white = L"◁";
wchar_t *arrow_west_black = L"◀";


struct Field field_load(FILE *file_state)
{
	int aWidth, aHeight, aRotation;
	int width, height;
	fscanf(file_state, "%i %i %i", &aWidth, &aHeight, &aRotation);
	fscanf(file_state, "%i %i", &width, &height);

	int **grid = malloc(height * sizeof(int *));
	for (int i = 0; i < aHeight; i++) {
		grid[i] = malloc(width * sizeof(int));
	}
	
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++)
                fscanf(file_state,"%d", &grid[i][j]);
	}

	struct Field field = {width, height, grid};
	struct Ant ant = {aWidth, aHeight, aRotation};
	field.ant = ant;
	return field;
}

void field_write(struct Field *field, FILE *stream)
{
	fwprintf(stream, L"%ls", line_down_right);
	for(int i = 0; field->height > i; i++)
		fwprintf(stream, L"%ls", line_horizontal);
	fwprintf(stream, L"%ls\n", line_down_left);
	for (int y = 0; field->height > y; y++) {
		fwprintf(stream, L"%ls", line_vertical);

		for (int x = 0; field->width > x; x++) {
			if (x == field->ant.x && y == field->ant.y) {
				if(field->grid[y][x] == 0) {
					switch (field->ant.rotation)
					{
					case 1:
						fwprintf(stream, L"%ls", arrow_north_white);
						break;
					case 2:
						fwprintf(stream, L"%ls", arrow_east_white);
						break;
					case 3:
						fwprintf(stream, L"%ls", arrow_south_white);
						break;
					case 4:
						fwprintf(stream, L"%ls", arrow_west_white);
						break;
					default:
						break;
					}
				} else {
					switch (field->ant.rotation)
					{
					case 1:
						fwprintf(stream, L"%ls", arrow_north_black);
						break;
					case 2:
						fwprintf(stream, L"%ls", arrow_east_black);
						break;
					case 3:
						fwprintf(stream, L"%ls", arrow_south_black);
						break;
					case 4:
						fwprintf(stream, L"%ls", arrow_west_black);
						break;
					default:
						break;
					}
				}
			}

			else {
				if(field->grid[y][x] == 0)
					fwprintf(stream, L"%ls", square_white);
				else 
					fwprintf(stream, L"%ls", square_black);
			}
		}
		fwprintf(stream, L"%ls\n", line_vertical);
	}
	fwprintf(stream, L"%ls", line_up_right);
	for(int i = 0; field->height > i; i++)
		fwprintf(stream, L"%ls", line_horizontal);
	fwprintf(stream, L"%ls\n", line_up_left);
}

void display_print(struct Field *field, int iteration)
{
	setlocale(LC_ALL, "C.UTF-8");
	wprintf(L"Iteration: %i\n", iteration);
	field_write(field, stdout);
}

void display_save(struct Field *field, int iteration, char *file_out)
{
	char *filename = malloc((sizeof(file_out) + 12) * sizeof(char));
	mkdir(file_out, 0755);
	setlocale(LC_ALL, "C.UTF-8");
	sprintf(filename,"%s/%s_%i.txt",file_out,file_out ,iteration);
	FILE *file = fopen(filename, "w");
	fwprintf(file, L"Iteration: %i\n", iteration);
	field_write(field, file);
}
// #include <stdio.h>
// #include <wchar.h>
// #include <locale.h>
// // LINE_VERTICAL:│
// // LINE_HORIZONTAL:─
// // LINE_DOWN_RIGHT:┌
// // LINE_DOWN_LEFT:┐
// // LINE_UP_RIGHT:└
// // LINE_UP_LEFT:┘
// // SQUARE_WHITE: 
// // SQUARE_BLACK:█
// // ARROW_NORTH_WHITE:△
// // ARROW_NORTH_BLACK:▲
// // ARROW_EAST_WHITE:▷
// // ARROW_EAST_BLACK:▶
// // ARROW_SOUTH_WHITE:▽
// // ARROW_SOUTH_BLACK:▼
// // ARROW_WEST_WHITE:◁
// // ARROW_WEST_BLACK:◀
// int main() {
//     
//     printf("▶ \n");
//     
//     char *c = "▶";
//     printf("%s %d \n", c, strlen(c));
//     
//     // setlocale(LC_ALL, "");
//     setlocale(LC_ALL, "C.UTF-8");
//     wchar_t *wc = L"▶";
//     printf("%ls %d \n", wc, wcslen(wc));
//     return 0;
// }
