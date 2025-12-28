#include <stdio.h>
#include "./raylib/include/raylib.h"

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