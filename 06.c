// TASK:
//
//
// So we made a ball bouncing around in pong.
//
// Let's try to do the same thing in breakout
//
// For now, make it so the ball bounces off all the walls, the paddle
//
// Don't worry about the bricks for now
// The ball should just bounce thru the bricks
//
// 1. Add ball. It doesnt matter where you place it. Just demonstrate in can move and bounce at angles.
// 2. Ball bounces off of screen edges like how it does in pong
// 3. Ball bounces off of paddle like how it does in pong
// 
// When the ball bounces off the paddle, it should behave similarly to how the pong paddle bouncing works, 
// except in this case, the paddle is facing up - not left or right, so the logic will need to be rotated
// to support this

#include "raylib/include/raylib.h"

int screen_size = 900;
#define wall_columns 14 
#define wall_rows 8
#define bricks_count (wall_rows*wall_columns)
float brick_height = 20;


Rectangle get_brick(int row, int col, float width, float height, float padding) {
	Rectangle brick = {
		(col * width) + padding/2,
		(row * height) + padding/2,
		width - padding,
		height - padding,
	};

	return brick;
}

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


	bool brick_statuses[bricks_count];
	for (int i = 0; i < bricks_count; i += 1) {
		brick_statuses[i] = true;
	}

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

		{ // moving paddle
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

		{ // dev editing
			bool should_create_brick_on_cursor_pos = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
			bool should_delete_brick_on_cursor_pos = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);

			int mouse_row = mouse_pos.y / brick_height;
			int mouse_col = mouse_pos.x / brick_width;
			int brick_idx = mouse_row*wall_columns + mouse_col;
			bool valid_index = brick_idx >= 0 && brick_idx < bricks_count;
			if (valid_index) {
				if(should_create_brick_on_cursor_pos) {
					brick_statuses[brick_idx] = true;
				}
				if(should_delete_brick_on_cursor_pos) {
					brick_statuses[brick_idx] = false;
				}
			}
		}

			
			
		for(int r = 0; r < wall_rows; r += 1) { // drawing bricks
			for (int c = 0; c < wall_columns; c += 1) {
				int brick_idx = r*wall_columns + c;
				bool should_draw_brick = brick_statuses[brick_idx] == true;
				if (should_draw_brick) {
					Color color = row_colors[r];
					Rectangle brick = get_brick(r, c, brick_width, brick_height, brick_padding);
					DrawRectangleRec(brick, color);					
				}
			}
		}

		DrawRectangleRec(paddle, WHITE); 

		ClearBackground(BLACK);

		EndDrawing();
	}
}