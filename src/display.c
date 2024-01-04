#include "field.h"
#include "display.h"

void field_display(struct Field *field) {
	for (int y = 0; field->height > y; y++) {
		for (int x = 0; field->width > x; x++) {
			printf("%i", field->grid[y][x]);
		}
		printf("\n");
	}
}
