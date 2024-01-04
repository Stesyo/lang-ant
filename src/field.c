#include <time.h>
#include <stdlib.h>

#include "field.h"

struct Field field_new(int width, int height, int rotation) {
	int **grid = malloc(height * sizeof(int *));
	for (int i = 0; height > i; i++) {
		grid[i] = calloc(width, sizeof(int));
	}
	struct Field field = {width, height, grid};
	struct Ant ant = {height / 2 * width + width / 2, rotation};
	field.ant = ant;

	return field;
}

void field_fill(struct Field *field, int chance) {
	srand(time(0));
	for (int i = 0; field->width * field->height > i; i++) {
		if (rand() % 100 < chance) {
			field->grid[i / field->width][i % field->width] = 1;
		}
	}
}

void field_free(struct Field *field) {
	for (int i = 0; field->height > i; i++) {
		free(field->grid[i]);
	}
	free(field->grid);
}

void field_step(struct Field *field) {

}
