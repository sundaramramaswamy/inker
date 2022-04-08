#include "window.h"

Window Window::Create(int width,
                      int height,
                      std::string_view title,
                      int target_fps) {
  InitWindow(width, height, title.data());
  SetTargetFPS(target_fps);
  return Window(width, height);
}


Window::Window(int width, int height) : view_{width, height} {
}

void Window::update() {
  if (!event_handler_)
    return;
}

void Window::draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  if (event_handler_)
    event_handler_->OnPaint(&view_);

  EndDrawing();
}

void Window::Run() {
  while (!WindowShouldClose()) {
    update();
    draw();
  }
  CloseWindow();
}

void Window::SetTitle(const std::string_view& title) {
  SetWindowTitle(title.data());
}
