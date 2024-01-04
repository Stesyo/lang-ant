#include <stdlib.h>

#include "field.h"

struct Field field_new(int width, int height, int rotation) {
	int **grid = malloc(width * sizeof(int *));
	for (int i = 0; width > i; i++) {
		grid[i] = malloc(height * sizeof(int));
	}
	struct Field field = {width, height, grid};
	struct Ant ant = {height / 2 * width + width / 2, rotation};
	field.ant = ant;

	return field;
}

void field_free(struct Field *field) {
	for (int i = 0; field->width > i; i++) {
		free(field->grid[i]);
	}
	free(field->grid);
}

void field_step(struct Field *field) {

}
