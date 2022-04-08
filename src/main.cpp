#include "window.h"

#include <sstream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr char TITLE[] = "Inker";
constexpr int TARGET_FPS = 60;

struct Controller : WindowEventHandler {
  void OnKeyPressed(const KeyboardEvent& e) override {
    log_key_event(__func__, e);
  }
  void OnKeyReleased(const KeyboardEvent& e) override {
    log_key_event(__func__, e);
  }

  void OnMousePressed(const MouseEvent& e) override {
    log_mouse_event(__func__, e);
  }
  void OnMouseReleased(const MouseEvent& e) override {
    log_mouse_event(__func__, e);
  }
  void OnMouseDragged(const MouseEvent& e) override {
    log_mouse_event(__func__, e);
  }

  void OnPaint(View* v) const override {
    v->DrawText("Hello, world", Vector2{ 20, 20 }, View::FontSize::Medium, RED);
  }

private:

  void log_mouse_event(std::string_view fn_name, const MouseEvent& e) const {
    TraceLog(LOG_INFO, "%s: Mouse button: %d, Delta: (%f, %f)",
             fn_name.data(), e.buttons, e.delta.x, e.delta.y);
  }

  void log_key_event(std::string_view fn_name, const KeyboardEvent& e) const {
    std::stringstream s;
    if (e.modifiers & Modifier::LeftShift)
      s << "Left Shift, ";
    if (e.modifiers & Modifier::RightShift)
      s << "Right Shift ,";
    if (e.modifiers & Modifier::LeftCtrl)
      s << "Left Ctrl, ";
    if (e.modifiers & Modifier::RightCtrl)
      s << "Right Ctrl,";
    if (e.modifiers & Modifier::LeftAlt)
      s << "Left Alt, ";
    if (e.modifiers & Modifier::RightAlt)
      s << "Right Alt,";
    auto mods = s.str();
    if (mods.empty())
      mods = "None";
    TraceLog(LOG_INFO, "%s: Key %d, Modifiers: %s",
             fn_name.data(), e.keycode, mods.data());
  }
};

int main() {
  Window w = Window::Create(WIDTH, HEIGHT, TITLE, TARGET_FPS);
  Controller controller;

  w.SetEventHandler(&controller);

  w.Run();
}
