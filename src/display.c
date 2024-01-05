#include "field.h"
#include <stdio.h>
#include "display.h"

// struct Field field_load(FILE *file_state) {
//
// }

void field_display(struct Field *field, int iteration) {
	printf("Iteration: %i\n", iteration);
	for (int y = 0; field->height > y; y++) {
		for (int x = 0; field->width > x; x++) {
			printf("%i ", field->grid[y][x]);
		}
		printf("\n");
	}
}

void field_save(struct Field *field, int iteration) {

}
