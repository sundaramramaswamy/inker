#ifndef __VIEW_H__
#define __VIEW_H__

#include "common.h"

class View {

public:

  void DrawPixel(float x, float y, Color c);
  void DrawLine(float x1, float y1, float x2, float y2, Color c);
  void DrawRectangle(float left, float top, float width, float height, Color c);
  void DrawCircle(float centre_x, float centre_y, float radius, Color c);

  void DrawText(std::string_view text, Vector2 pos, int font_size, Color c);

  size_t GetWidth() const { return width_; }
  size_t GetHeight() const { return height_; }

  View(int width, int height);
  ~View() = default;

  // Non-copyable, immovable
  View(const View&) = delete;
  View(View&&) = delete;
  View& operator=(const View&) = delete;
  View& operator=(View&&) = delete;

private:

  int width_ = 0;
  int height_ = 0;
};

#endif  // __VIEW_H__
