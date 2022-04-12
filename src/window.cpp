#include "window.h"

#include <vector>

Window* Window::Create(int width,
                       int height,
                       std::string_view title,
                       int target_fps) {
  static Window w{width, height, title, target_fps};
  return &w;
}

Window::Window(int width, int height, std::string_view title, int target_fps)
  : view_{width, height} {
  InitWindow(width, height, title.data());
  SetTargetFPS(target_fps);
}

uint8_t get_modifiers() {
  return (IsKeyDown(KEY_LEFT_SHIFT) ? Modifier::LeftShift : Modifier::None) |
    (IsKeyDown(KEY_RIGHT_SHIFT) ? Modifier::RightShift : Modifier::None) |
    (IsKeyDown(KEY_LEFT_CONTROL) ? Modifier::LeftCtrl : Modifier::None) |
    (IsKeyDown(KEY_RIGHT_CONTROL) ? Modifier::RightCtrl : Modifier::None) |
    (IsKeyDown(KEY_LEFT_ALT) ? Modifier::LeftAlt : Modifier::None) |
    (IsKeyDown(KEY_RIGHT_ALT) ? Modifier::RightAlt : Modifier::None);
}

void Window::dispatch_key_events() {
  while (int k = GetKeyPressed()) {
    // ignore pure modifier presses
    if ((k >= 340) && (k <= 347))
      continue;

    KeyboardEvent ke { k, get_modifiers() };
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

void Window::dispatch_mouse_events() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    mouse_down_ |= Button::Left;
    MouseEvent me = {
      GetMousePosition(),
      GetMouseDelta(),
      mouse_down_,
      get_modifiers()
    };
    event_handler_->OnMousePressed(me);
  }
  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    mouse_down_ &= ~Button::Left;
    MouseEvent me = {
      GetMousePosition(),
      GetMouseDelta(),
      mouse_down_,
      get_modifiers()
    };
    event_handler_->OnMouseReleased(me);
  }
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    mouse_down_ |= Button::Right;
    MouseEvent me = {
      GetMousePosition(),
      GetMouseDelta(),
      mouse_down_,
      get_modifiers()
    };
    event_handler_->OnMousePressed(me);
  }
  if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
    mouse_down_ &= ~Button::Right;
    MouseEvent me = {
      GetMousePosition(),
      GetMouseDelta(),
      mouse_down_,
      get_modifiers()
    };
    event_handler_->OnMouseReleased(me);
  }
  auto delta = GetMouseDelta();
  if ((delta.x != 0.f) || (delta.y != 0.f)) {
    MouseEvent me = {
      GetMousePosition(),
      delta,
      mouse_down_,
      get_modifiers()
    };
    if (mouse_down_ > 0)
      event_handler_->OnMouseDragged(me);
    else
      event_handler_->OnMouseMoved(me);
  }
}

void Window::update() {
  if (!event_handler_)
    return;

  dispatch_key_events();
  dispatch_mouse_events();
}

void Window::draw() {
  BeginDrawing();
  ClearBackground(Color{0, 0, 0, 0});

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

void Window::SetEventHandler(WindowEventHandler* h) {
  event_handler_ = h;
}
