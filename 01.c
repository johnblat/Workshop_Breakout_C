// TASK:
//
// In this breakout game, we will use the mouse to primarily control the paddle
// If you would like to add controls for using keyboard input, you can add that
// But for now, Let's use mouse
//
// 1.  To get started let's just draw a white rectangle, whatever size you want, and have its position be set to 
// you mouse cursor
//
// 2. Now make it so that the rectangle is centered on your mouse cursor

// New Functions to use:
// GetMousePosition();


#include "raylib/include/raylib.h"

int screen_size = 900;

int main () {
	InitWindow(screen_size, screen_size, "Breakout");
	SetTargetFPS(60.0);	

	while(!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		EndDrawing();
	}
}