// TASK:
//
// Draw a wall of bricks.
// You can make them all the same color for now.
// We will make them different colors later.
// There should be 8 rows of bricks
// There should be 14 columns of bricks
// The brick wall should go all the way from the left side of the screen to the right side
// of the screen
// You can make the height of the brick be something like 20, it doesn't really matter.

// Additionally, the bricks should have some padding between each other so that you can see the 
// individual bricks. If you drew them touching each other, it would just look like one big rectangle
// and not a lot of tiny bricks
//
//
// To accomplish this, i recommend:
//
// First drawing all the rectangles as rectangle lines, so that you can see that you are drawing the wall
// correctly. Use function DrawRectangleLinesEx() for this
//
// Second, add the padding 

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