#ifndef FIELD_H
#define FIELD_H

struct Ant {
	int position;
	int rotation;
};

struct Field {
	int width;
	int height;
	int **grid;
	struct Ant ant;
	int iteration;
};

struct Field field_new(int width, int height);

void field_free(struct Field *field);

void field_step(struct Field *field);

#endif // !FIELD_H
