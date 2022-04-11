#include "window.h"
#include "test_controller.h"

constexpr int WIDTH = 1024;
constexpr int HEIGHT = 768;
constexpr char TITLE[] = "Inker";
constexpr int TARGET_FPS = 60;

int main() {
  Window* w = Window::Create(WIDTH, HEIGHT, TITLE, TARGET_FPS);
  TestController controller;

  w->SetEventHandler(&controller);

  w->Run();
}
