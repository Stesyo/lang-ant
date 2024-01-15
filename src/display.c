#include <stdio.h>

#include "field.h"
#include "display.h"


struct Field field_load(FILE *file_state)
{
	return field_new(0, 0, 1);
}

void display_print(struct Field *field, int iteration)
{
	printf("Iteration: %i\n", iteration);
	for (int y = 0; field->height > y; y++) {
		for (int x = 0; field->width > x; x++) {
			if (x == field->ant.x && y == field->ant.y) {
				printf("A ");
			}
			else {
				printf("%i ", field->grid[y][x]);
			}
		}
		printf("\n");
	}
}

void display_save(struct Field *field, int iteration, char *file_out)
{
	char *filename = malloc((sizeof(file_out) + 12) * sizeof(char));
	mkdir(file_out);
	sprintf(filename,"%s/%s_%i.txt",file_out,file_out ,iteration);
	FILE *file = fopen(filename,"w");
	fprintf(file,"Iteration: %i\n", iteration);
	for (int y = 0; field->height > y; y++) {
		for (int x = 0; field->width > x; x++) {
			if (x == field->ant.x && y == field->ant.y) {
				fprintf(file,"A ");
			}
			else {
				fprintf(file,"%i ", field->grid[y][x]);
			}
		}
		fprintf(file, "\n");
	}

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
