#include <stddef.h>
#include <raylib.h>
#include "colors.h"

static Color colors[] = {
{245, 224, 220, 255}, // Rosewater
{242, 205, 205, 255}, // Flamingo
{245, 194, 231, 255}, // Pink
{203, 166, 247, 255}, // Mauve
{243, 139, 168, 255}, // Red
{250, 179, 135, 255}, // Peach
{249, 226, 175, 255}, // Yellow
{166, 227, 161, 255}, // Green
{148, 226, 213, 255}, // Teal
{137, 180, 250, 255}  // Blue
};

Color* getColors(void) {
	return colors;
};

size_t getColorsLength(void) {
	return sizeof(colors) / sizeof(colors[0]);
}

void normalizedColorsToFloatVec4(float* vec4) {
	for (size_t i = 0; i < COLORS_LENGTH; ++i) {
		vec4[i * 4] = colors[i].r / 255.0f;
		vec4[i * 4 + 1] = colors[i].g / 255.0f;
		vec4[i * 4 + 2] = colors[i].b / 255.0f;
		vec4[i * 4 + 3] = colors[i].a / 255.0f;
	}
}

