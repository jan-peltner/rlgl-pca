#include <raylib.h>
#include <stddef.h>
#include <raymath.h>
#include "colors.h"
#include "window.h"


// #define USE_SHADER
#define CELL_SIZE 10
#define GRID_WIDTH 100
#define GRID_HEIGHT 50 
#define GRID_LENGTH GRID_WIDTH * GRID_HEIGHT

typedef struct {
	bool isAlive;
} Cell;

typedef void(InitCb)(Cell* cell, size_t idx);

void renderCells(Cell* cells, Vector2 origin) {
	for (size_t i = 0; i < GRID_LENGTH; ++i) {
		DrawRectangle(
			(i % GRID_WIDTH) * CELL_SIZE + (int)origin.x, 
			(i / GRID_WIDTH) * CELL_SIZE + (int)origin.y, 
			CELL_SIZE, 
			CELL_SIZE, 
			cells[i].isAlive ? RED : BLACK
		);
	}
};

void initCells(Cell* cells, InitCb cb) {
	for (size_t i = 0; i < GRID_LENGTH; ++i) {
		cb(cells + i , i);
	}
}

void stripeInit(Cell* cell, size_t idx) {
	cell->isAlive = idx % 2 == 0;
}

void checkersInit (Cell* cell, size_t idx) {
	// check if we're in odd row
	if ((idx / GRID_WIDTH) % 2 != 0) {
		cell->isAlive = idx % 2 != 0;
	} else {
		cell->isAlive = idx % 2 == 0;
	}
}

int main(void) {
	// init 
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Probabilistic Cellular Automata");	
	SetTargetFPS(TARGET_FPS);
	Vector2* resolution = getResolution();

	// get colors for CPU
	Color* colors = getColors();
	size_t colors_length = getColorsLength();

	// prepare colors as vec4 for GPU shader
	float color_palette_vec[colors_length * 4];
	normalizedColorsToFloatVec4(color_palette_vec);

	#ifdef USE_SHADER

	// set up shaders
	Shader main_shader = LoadShader("main.vert", "main.frag");

	int main_shader_colors_loc = GetShaderLocation(main_shader, "colors"); 
	int main_shader_time_loc = GetShaderLocation(main_shader, "time");
	int main_shader_resolution_loc = GetShaderLocation(main_shader, "resolution");

	SetShaderValueV(main_shader, main_shader_colors_loc, &color_palette_vec, SHADER_UNIFORM_VEC4, colors_length);
	SetShaderValue(main_shader, main_shader_resolution_loc, resolution, SHADER_UNIFORM_VEC2);

	RenderTexture2D main_target = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

	#endif // USE_SHADER
	
	Cell cells[GRID_LENGTH];
	initCells(cells, checkersInit);

	while (!WindowShouldClose()) {
		resolution->x = (float)GetScreenWidth();
		resolution->y = (float)GetScreenHeight();

		#ifdef USE_SHADER

		float elapsed_time = GetTime();
		SetShaderValue(main_shader, main_shader_time_loc, &elapsed_time, SHADER_UNIFORM_FLOAT);

		BeginTextureMode(main_target);
		    ClearBackground(BLACK);
		    BeginShaderMode(main_shader);
		    DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
		    EndShaderMode();
		EndTextureMode();

		#endif // USE_SHADER
		
		BeginDrawing();

			ClearBackground(colors[0]);

			#ifdef USE_SHADER

			DrawTexturePro(
			main_target.texture,
			(Rectangle){ 0, 0, (float)main_target.texture.width, (float)main_target.texture.height },
			(Rectangle){ 0, 0, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT},
			(Vector2){ 0, 0 },
			0.0f,
			WHITE
			);

			#else 

			renderCells(cells, Vector2Add(Vector2Zero(), Vector2Scale(*resolution, 0.25)));
			
			#endif // USE_SHADER

			DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, BLACK);
			DrawText(TextFormat("Frametime: %.2fms", GetFrameTime() * 1000), 10, 30, 20, BLACK);

		EndDrawing();
	}

	
	#ifdef USE_SHADER
	UnloadRenderTexture(main_target);
	UnloadShader(main_shader);
	#endif // USE_SHADER
	CloseWindow();
	return 0;
}
