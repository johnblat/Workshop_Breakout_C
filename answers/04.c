#include "raylib/include/raylib.h"

int screen_size = 900;
#define wall_columns 14 
#define wall_rows 8
float brick_height = 20;

int main () {
	Color row_colors[wall_rows] = {
		RED,
		RED,
		ORANGE,
		ORANGE,
		GREEN,
		GREEN,
		YELLOW,
		YELLOW,
	};

	float brick_width = (float)(screen_size) / (float)(wall_columns);

	float brick_padding = brick_width / 20;

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

		{
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
		}

			
		for(int r = 0; r < wall_rows; r += 1) {
			for (int c = 0; c < wall_columns; c += 1) {
				Color color = row_colors[r];

				Rectangle brick = {
					(c * brick_width) + brick_padding/2,
					(r * brick_height) + brick_padding/2,
					brick_width - brick_padding,
					brick_height - brick_padding,
				};

				DrawRectangleRec(brick, color);
			}
		}

		DrawRectangleRec(paddle, WHITE); 

		ClearBackground(BLACK);

		EndDrawing();
	}
}