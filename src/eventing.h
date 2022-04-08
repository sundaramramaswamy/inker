#ifndef __EVENTING_H__
#define __EVENTING_H__

enum ModifierKey : uint8_t {
  None         = 0,
  LeftShift    = 1 << 0,
  RightShift   = 1 << 1,
  LeftAlt      = 1 << 2,
  RightAlt     = 1 << 3,
  LeftCtrl     = 1 << 4,
  RightCtrl    = 1 << 5,
};

struct MouseEvent {
  Vector2 pos;
  Vector2 delta;
  MouseButton button;
  ModifierKey mod;
};

struct KeyboardEvent {
  int keycode;
  int unicode;  // codepoint
};

struct WindowEventHandler {
  // Mouse Events
  virtual void OnMousePressed(const MouseEvent& e) {}
  virtual void OnMouseReleased(const MouseEvent& e) {}
  virtual void OnMouseMoved(const MouseEvent& e) {}
  virtual void OnMouseDragged(const MouseEvent& e) {}

  // Keyboard Events
  virtual void OnKeyPressed(const KeyboardEvent& e) {}
  virtual void OnKeyRelease(const KeyboardEvent& e) {}

  // Paint Events
  virtual void OnPaint(View* v) {}
};

#endif  // __EVENTING_H__
