#include <raylib.h>
#include <raymath.h>
#include "window.h"

static Vector2 resolution = {
	.x = (float)WINDOW_WIDTH, 
	.y = (float)WINDOW_HEIGHT
};

Vector2* getResolution(void) {
	return &resolution;
};

Vector2 getCenter(Vector2 res) {
	return Vector2Scale(res, 0.5f);
}
