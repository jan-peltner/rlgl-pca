#ifndef RLGLT_COLORS_H
#define RLGLT_COLORS_H

#include <stddef.h>
#include "raylib.h"

#define COLORS_LENGTH 10

Color* getColors(void);
size_t getColorsLength(void);
void normalizedColorsToFloatVec4(float* vec4);

#endif
