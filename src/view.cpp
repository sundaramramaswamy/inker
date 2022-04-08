#include "view.h"

View::View(int width, int height) : width_{width}, height_{height} {
}

void View::DrawPixel(float x, float y, Color c) {
  DrawPixelV(Vector2{x, y}, c);
}

void View::DrawLine(float x1, float y1, float x2, float y2, Color c) {
  DrawLineV(Vector2{x1, y1}, Vector2{x2, y2}, c);
}

void View::DrawRectangle(float left, float top, float width, float height, Color c) {
  DrawRectangleV(Vector2{left, top}, Vector2{width, height}, c);
}

void View::DrawCircle(float centre_x, float centre_y, float radius, Color c) {
  DrawCircleV(Vector2{centre_x, centre_y}, radius, c);
}

void View::DrawText(std::string_view text, Vector2 pos, FontSize s, Color c) {
  int font_size = 20;
  switch (s) {
  case FontSize::Small:
    font_size = 10;
    break;
  case FontSize::Medium:
    break;
  case FontSize::Large:
    font_size = 40;
    break;
  case FontSize::Huge:
    font_size = 80;
  }

  ::DrawText(text.data(), static_cast<int>(pos.x), static_cast<int>(pos.y), font_size, c);
}
