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

  static Window* Create(int width,
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
  Window(int width, int height, std::string_view title, int target_fps);

  void update();
  void draw();

  void dispatch_key_events();
  void dispatch_mouse_events();

  WindowEventHandler* event_handler_ = nullptr;
  std::set<int> keys_down_;
  uint8_t mouse_down_ = 0;
  View view_;
};

#endif  // __WINDOW_H__
