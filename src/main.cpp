#include <raylib.h>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int TARGET_FPS = 60;

int main() {
  InitWindow(WIDTH, HEIGHT, "Hola Mario!");
  SetTargetFPS(TARGET_FPS);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!",
             190,
             200,
             20,
             LIGHTGRAY);
    EndDrawing();
  }
  CloseWindow();
}
