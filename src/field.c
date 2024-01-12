#include <time.h>
#include <stdlib.h>

#include "field.h"

struct Field field_new(int width, int height, int rotation)
{
	int **grid = malloc(height * sizeof(int *));
	for (int i = 0; height > i; i++) {
		grid[i] = calloc(width, sizeof(int));
	}
	struct Field field = {width, height, grid};
	struct Ant ant = {width / 2, height / 2, rotation};
	field.ant = ant;

	return field;
}

void field_fill(struct Field *field, int chance)
{
	srand(time(0));
	for (int i = 0; field->width * field->height > i; i++) {
		if (rand() % 100 < chance) {
			field->grid[i / field->width][i % field->width] = 1;
		}
	}
}

void field_free(struct Field *field)
{
	for (int i = 0; field->height > i; i++) {
		free(field->grid[i]);
	}
	free(field->grid);
}

void field_step(struct Field *field)
{
	int x = field->ant.x;
	int y = field->ant.y;

	if (field->grid[y][x] == 0) {
		field->ant.rotation += 1;
		if (field->ant.rotation > W) {
			field->ant.rotation = N;
		}
	} else {
		field->ant.rotation -= 1;
		if (field->ant.rotation < N) {
			field->ant.rotation = W;
		}
	}
	field->grid[y][x] ^= 1;

	switch (field->ant.rotation) {
		case 1:// N
			if (!y) {
				y = field->width;
			}
			y -= 1;
			break;
		case 2:// E
			x = (x + 1) % field->width;
			break;
		case 3:// S
			y = (y + 1) % field->height;
			break;
		case 4:// W
			if (!x) {
				x = field->width;
			}
			x -= 1;
			break;
	}
	field->ant.x = x;
	field->ant.y = y;
}
