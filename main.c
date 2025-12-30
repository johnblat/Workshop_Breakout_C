#include <stdio.h>
#include "./raylib/include/raylib.h"

#define screen_size 800
#define screen_size_f 800.0f


int main() {
	
	InitWindow(800, 450, "Breakout");

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		EndDrawing();

	}
	 
	printf("Hello!\n");
	return 0;
}