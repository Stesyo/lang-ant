#ifndef FIELD_H
#define FIELD_H

static const int N = 1<<1;
static const int E = 1<<2;
static const int S = 1<<3;
static const int W = 1<<4;

struct Ant {
	int position;
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

void field_step(struct Field *field);

#endif // !FIELD_H
