
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