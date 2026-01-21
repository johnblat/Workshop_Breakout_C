#include "raylib/include/raylib.h"

int screen_size = 900;

int main () {
	InitWindow(screen_size, screen_size, "Breakout");
	SetTargetFPS(60.0);	

	while(!WindowShouldClose()) {
		BeginDrawing();

		Vector2 mouse_pos = GetMousePosition();
		
		float paddle_width = 40;
		float paddle_height = 20;
		float paddle_bottom_padding = 10;

		Rectangle paddle = {
			mouse_pos.x - paddle_width/2, 
			screen_size - paddle_bottom_padding - paddle_height, 
			paddle_width, 
			paddle_height
		};

		float paddle_right_side_x = paddle.x + paddle_width;
		float paddle_left_side_x = paddle.x;
		bool paddle_too_far_left = paddle_left_side_x < 0; 
		bool paddle_too_far_right = paddle_right_side_x > screen_size;
		if (paddle_too_far_left) {
			paddle.x = 0;
		}
		if (paddle_too_far_right) {
			paddle.x = screen_size - paddle_width;
		}

		DrawRectangleRec(paddle, WHITE); 

		ClearBackground(BLACK);

		EndDrawing();
	}
}