// TASK:
//
// 1.  Make the rectangle the "paddle" by making it more paddle shaped
// Also, make the paddle's position be fixed to the bottom of the screen
// so that moving your mouse cursor can only move it left and right
//
// 2. Add a little padding from the bottom of the screen so the paddle 
// isn't butted completely to the edge of the screen
//
// 3. Kind of like in pong did it top and bottom, 
// make it so that now the paddle can't move beyond the screen left or right
// side

#include "raylib/include/raylib.h"

int screen_size = 900;

int main () {
	InitWindow(screen_size, screen_size, "Breakout");
	SetTargetFPS(60.0);	

	while(!WindowShouldClose()) {
		BeginDrawing();

		Vector2 mouse_pos = GetMousePosition();
		float rectangle_size = 40; 
		Rectangle rectangle = {
			mouse_pos.x - rectangle_size/2, 
			mouse_pos.y - rectangle_size/2, 
			rectangle_size, 
			rectangle_size
		};

		DrawRectangleRec(rectangle, WHITE); 

		ClearBackground(BLACK);

		EndDrawing();
	}
}