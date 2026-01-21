
#include "raylib/include/raylib.h"
#include "raylib/include/raymath.h"
#include <stdio.h>

int screen_size = 900;
#define wall_columns 14 
#define wall_rows 8
#define bricks_count (wall_rows*wall_columns)
float brick_height = 20;
float wall_top_padding = 100; // just some amount
float max_ball_speed = 800;


#define ACTIVE true
#define INACTIVE false


Rectangle get_brick(int row, int col, float width, float height, float padding) {
	Rectangle brick = {
		(col * width) + padding/2,
		wall_top_padding + (row * height) + padding/2,
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

	bool ball_attached_to_paddle = true;

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

		if (ball_attached_to_paddle) {
			ball.y = paddle.y - ball.height;
			ball.x = mouse_pos.x - ball.width/2;

			bool should_launch_ball_into_play = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
			if (should_launch_ball_into_play) {
				ball_attached_to_paddle = false;
				Vector2 upwards = {0,-1};
				ball_direction = upwards;
			}
		}
		else { // ball in play 
			float frame_time = GetFrameTime();
			ball_direction = Vector2Normalize(ball_direction);
			Vector2 ball_velocity = Vector2Scale(ball_direction, ball_speed);
			ball.x += ball_velocity.x*frame_time;
			ball.y += ball_velocity.y*frame_time;

			float ball_top = ball.y;
			float ball_left = ball.x;
			float ball_right = ball.x + ball.width;

			bool ball_hit_screen_left = ball_left < 0;
			bool ball_hit_screen_right = ball_right > screen_size;
			bool ball_hit_screen_top = ball_top < 0;

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

			bool ball_out_of_bounds = ball_top > screen_size;
			if (ball_out_of_bounds) {
				ball_attached_to_paddle = true;
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

			for(int r = 0; r < wall_rows; r += 1) {
				for (int c = 0; c < wall_columns; c += 1) {
					int brick_idx = r*wall_columns + c;
					bool is_active = brick_statuses[brick_idx] == ACTIVE;
					if (is_active) {
						Rectangle brick = get_brick(r, c, brick_width, brick_height, brick_padding);

						bool ball_hit_brick = CheckCollisionRecs(ball, brick);
						if (ball_hit_brick) {

							ball_speed += 20;
							if (ball_speed > max_ball_speed) {
								ball_speed = max_ball_speed;
							}
							
							brick_statuses[brick_idx] = INACTIVE;
							Rectangle collision_rect = GetCollisionRec(ball, brick);

							bool wider = collision_rect.width >= collision_rect.height;
							bool taller = collision_rect.width < collision_rect.height;
														
							bool top_or_bottom_collision = wider;
							bool left_or_right_collision = taller;

							if (top_or_bottom_collision) {
								bool ball_moving_up = ball_direction.y <= 0;
								bool ball_moving_down = ball_direction.y > 0;

								bool bounce_ball_up = ball_moving_down;
								bool bounce_ball_down = ball_moving_up;

								if (bounce_ball_up) {
									ball.y = brick.y - ball.height;
									ball_direction.y = -ball_direction.y;
								}
								else if (bounce_ball_down) {
									ball.y = brick.y + brick_height;
									ball_direction.y = -ball_direction.y;
								}
							} else if (left_or_right_collision) {
								bool ball_moving_right = ball_direction.x >= 0;
								bool ball_moving_left = ball_direction.x < 0;

								bool bounce_ball_left = ball_moving_right;
								bool bounce_ball_right = ball_moving_left;

								if (bounce_ball_left) {
									ball.x = brick.x - ball.width;
									ball_direction.x = -ball_direction.x;
								}
								else if (bounce_ball_right) {
									ball.x = brick.x + brick.width;
									ball_direction.x = -ball_direction.x;
								}
							}
						} 
					}						
				}
			}


		}

		{ // dev editing
			bool should_create_brick_on_cursor_pos = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
			bool should_delete_brick_on_cursor_pos = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);

			int mouse_row = (mouse_pos.y - wall_top_padding) / brick_height;
			int mouse_col = (mouse_pos.x) / brick_width;
			int brick_idx = mouse_row*wall_columns + mouse_col;
			bool valid_index = brick_idx >= 0 && brick_idx < bricks_count;
			if (valid_index) {
				if(should_create_brick_on_cursor_pos) {
					brick_statuses[brick_idx] = ACTIVE;
				}
				if(should_delete_brick_on_cursor_pos) {
					brick_statuses[brick_idx] = INACTIVE;
				}
			}
		}

		int bricks_cleared = 0;
		for (int i = 0; i < bricks_count; i += 1) {
			// An if-statement here would be completely fine. I'm just showing a different way 
			int add_amount = brick_statuses[i] == INACTIVE ? 1 : 0;
			bricks_cleared += add_amount; 
		}

		char score_text_buffer[4];
		snprintf(score_text_buffer, 4, "%d", bricks_cleared);

		DrawText(score_text_buffer, 10, 10, 30, WHITE);

		for(int r = 0; r < wall_rows; r += 1) { // drawing bricks
			for (int c = 0; c < wall_columns; c += 1) {
				int brick_idx = r*wall_columns + c;
				bool should_draw_brick = brick_statuses[brick_idx] == ACTIVE;
				if (should_draw_brick) {
					Color color = row_colors[r];
					Rectangle brick = get_brick(r, c, brick_width, brick_height, brick_padding);
					DrawRectangleRec(brick, color);					
				}
			}
		}

		DrawRectangleRec(paddle, WHITE); 
		DrawRectangleRec(ball, PINK);

		ClearBackground(BLACK);

		EndDrawing();
	}
}