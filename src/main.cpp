#include "window.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr char TITLE[] = "Inker";
constexpr int TARGET_FPS = 60;

int main() {
  Window w = Window::Create(WIDTH, HEIGHT, TITLE, TARGET_FPS);

  // w.SetEventHandler(controller);

  w.Run();
}
