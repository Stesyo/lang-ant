#ifndef FIELD_H
#define FIELD_H

// Possbile ant rotations
static const int N = 1;
static const int E = 2;
static const int S = 3;
static const int W = 4;

struct Ant {
	int x;
	int y;
	int rotation;
};

struct Field {
	int width;
	int height;
	int **grid;
	struct Ant ant;
};

struct Field field_new(int width, int height, int rotation);


void field_free(struct Field *field);

void field_fill(struct Field *field, int chance);

void field_step(struct Field *field);

#endif // !FIELD_H
