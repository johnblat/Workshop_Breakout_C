// TASK:
//
// Now make it so that the ball bounces off the bricks
// If the ball hits the left or right side of a brick, it should change directions left or right in x direction
// If the ball hits the top or bottom of a brick, it should change directions up or down in y direction
//
// If a ball hits a brick, it should delete the brick
//
// Do this in two steps:
// 1. If ball hits brick, delete it. So really, the ball will keep moving forward, killing anything in its way
//    ^ this is actually kind of cool, so maybe we can add this as a powerup in future?
// 2. If the ball hits brick, it should bounce in the appropraite direction 

#include "raylib/include/raylib.h"
#include "raylib/include/raymath.h"

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

	float ball_size = 15;
	Vector2 ball_direction = {1,1};
	float ball_speed = 400;
	Vector2 ball_position = {(float)screen_size/2, screen_size - 100};
	Rectangle ball = { (float)screen_size/2, screen_size - 100, ball_size, ball_size };


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
		
		float paddle_width = brick_width;
		float paddle_height = brick_height;
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

		{ // move ball
			float frame_time = GetFrameTime();
			ball_direction = Vector2Normalize(ball_direction);
			Vector2 ball_velocity = Vector2Scale(ball_direction, ball_speed);
			ball.x += ball_velocity.x*frame_time;
			ball.y += ball_velocity.y*frame_time;

			float ball_top = ball.y;
			float ball_bottom = ball.y + ball.height;
			float ball_left = ball.x;
			float ball_right = ball.x + ball.width;

			bool ball_hit_screen_left = ball_left < 0;
			bool ball_hit_screen_right = ball_right > screen_size;
			bool ball_hit_screen_top = ball_top < 0;
			bool ball_hit_screen_bottom = ball_bottom > screen_size;

			if (ball_hit_screen_left) {
				ball.x = 0;
				ball_direction.x = -ball_direction.x;
			}
			if (ball_hit_screen_right) {
				ball.x = screen_size - ball.width;
				ball_direction.x = -ball_direction.x;
			}
			if (ball_hit_screen_top) {
				ball.y = 0;
				ball_direction.y = -ball_direction.y;
			}
			if (ball_hit_screen_bottom) {
				ball.y = screen_size - ball.height;
				ball_direction.y = -ball_direction.y;
			}

			bool ball_hit_paddle = CheckCollisionRecs(ball, paddle);
			if (ball_hit_paddle) {
				Rectangle collision_rect = GetCollisionRec(ball, paddle);
				float collision_rect_mid_x = collision_rect.x + collision_rect.width/2;
				float relative_intersect_x = paddle.x + (paddle.width/2) - collision_rect_mid_x;
				float normalized_intersect_x = relative_intersect_x / (paddle.width/2);
				float bounce_angle = normalized_intersect_x * (5*3.14/12);
				ball_direction.x = -sin(bounce_angle);
				ball_direction.y = -cos(bounce_angle);
				ball.y = paddle.y - ball.height;
			}

			DrawRectangleRec(ball, PINK);

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