#ifndef RLGLT_WINDOW_H
#define RLGLT_WINDOW_H

#include <raylib.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TARGET_FPS 60

Vector2* getResolution(void);
Vector2 getCenter(Vector2 res);

#endif
