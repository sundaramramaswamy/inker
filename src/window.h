#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "common.h"
#include "view.h"
#include "eventing.h"

#include <set>
#include <cstdint>

class Window {
public:
  void SetEventHandler(WindowEventHandler* h);
  void SetTitle(const std::string_view& title);

  void Run();

  static Window Create(int width,
                       int height,
                       std::string_view title,
                       int target_fps);
  ~Window() = default;

  // Non-copyable, immovable
  Window(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&&) = delete;

private:
  Window(int width, int height);

  void update();
  void draw();

  WindowEventHandler* event_handler_ = nullptr;
  std::set<int> keys_down_;
  View view_;
};

#endif  // __WINDOW_H__
