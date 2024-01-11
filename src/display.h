#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "field.h"

struct Field field_load(FILE *file_state);

void display_print(struct Field *field, int iteration);

void display_save(struct Field *field, int iteration, char *file_out);

#endif // !DISPLAY_H
