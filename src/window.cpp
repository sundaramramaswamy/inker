#include "window.h"

#include <vector>

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

uint8_t get_modifiers() {
  return (IsKeyDown(KEY_LEFT_SHIFT) ? Modifier::LeftShift : Modifier::None) |
    (IsKeyDown(KEY_RIGHT_SHIFT) ? Modifier::RightShift : Modifier::None) |
    (IsKeyDown(KEY_LEFT_CONTROL) ? Modifier::LeftCtrl : Modifier::None) |
    (IsKeyDown(KEY_RIGHT_CONTROL) ? Modifier::RightCtrl : Modifier::None) |
    (IsKeyDown(KEY_LEFT_ALT) ? Modifier::LeftAlt : Modifier::None) |
    (IsKeyDown(KEY_RIGHT_ALT) ? Modifier::RightAlt : Modifier::None);
}

void Window::update() {
  if (!event_handler_)
    return;

  // Check keyboard events
  while (int k = GetKeyPressed()) {
    // ignore pure modifier presses
    if ((k >= 340) && (k <= 347))
      continue;

    KeyboardEvent ke{k, get_modifiers()};
    keys_down_.insert(k);
    event_handler_->OnKeyPressed(ke);
  }

  for (auto it = keys_down_.begin(); it != keys_down_.end();) {
    if (IsKeyReleased((*it))) {
      event_handler_->OnKeyReleased(KeyboardEvent{*it, get_modifiers()});
      it = keys_down_.erase(it);
    }
    else
      ++it;
  }
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

void Window::SetEventHandler(WindowEventHandler* h) {
  event_handler_ = h;
}
