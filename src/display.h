#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "field.h"

struct Field field_load(FILE *file_state);

void field_display(struct Field *field, int iteration);

void field_save(struct Field *field, int iteration);

#endif // !DISPLAY_H
