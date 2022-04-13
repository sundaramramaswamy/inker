# Tools

Make sure the following tools are installed:

* Visual Studio 2017+
  - `Microsoft.VisualStudio.Workload.NativeDesktop` workload is needed for Desktop C++ development
* [CMake][]
  - Command `cmake` should be in `%PATH%`
  - Verify if `cmake --version` shows version

If in doubt, run `python3 verify_or_install_tools.py` (requires [Python 3.7+][python3]).

# Build

``` shell
git clone https://github.com/sundaramramaswamy/inker

cd inker

cmake -B build

cmake --build build
```

This should build `ink.exe` under `//build/Debug`.

Open Visual Studio with

``` shell
start build\Inker.sln
```

In the _Solution Explorer_, right-click `ink` project and click _Set as Startup Project_.

# Code

Add new sources (`.h`/`.cpp`) to `src/` and list them in `//CMakeLists.txt` along with other sources.
Build in Visual Studio.  It should pick up the changes you made in the CMake script.

# Workshop Mini-project

## Controller/Adapter

The idea is to implement an inking application using [MVA Pattern][] (an extension of [MVC][]).  Refer and use the interfaces in `eventing.h` and `view.h`; implement a `Controller` class which extends/inherits from `WindowEventHandler`.

## Model

Build an ink document (model) using the `OnMousePressed`, `OnMouseDragged` and `OnMouseReleased` functions.  One way to structure your document

    Document
      Collection of Stroke
    
    Stroke
      Collection of Points
    
    Point
      A pair of floats (Vector2)

When the user clicks, drags and releases the mouse, you'd get a bunch of points which form one stroke. A document is a collect of such strokes.

## View

During the `OnPaint(View*)` you'd refer to your document (model) and for every stroke do a bunch of `DrawLine` calls.  This would render the document on to the view.

## Files

The default state of the project comes with a `TestController` class (`//src/test_controller.h`) that simply logs the events it receives and paints `Hello, world`.  You've to implement your own `InkController` for the above work.  Make sure in `main.cpp` you set your `InkController` as the window's event handler.  Other than `main.cpp`, `eventing.h` and `view.h` you can pretty much ignore all the other files in the project.

## Extensions

### Stroke Erase

When the user clicks a stroke with `Ctrl` held down, you can [hit-test][] all the strokes in the document and check if the click was atop a stroke.  If yes, you'd remove that stroke from your document. In the next `OnPaint` call this change would automatically be picked up and you don't have to do anything extra to see the stroke go away.

### Multi-Colour Strokes

You can make the document fancy by having strokes of different colours.  It’s up to you define how to switch the pen colour.  One way would be to assign colours to keyboard keys `1` (Black), `2` (Red), `3` (Blue), etc. and switch the colour when the user presses a corresponding key.  You’d store every stroke with a colour in your model.  During render, you’d draw the stroke with `DrawLine`s passing the stroke’s colour as `Color` (which is a collection of four `unsigned char`s).


[CMake]: https://cmake.org/
[vcpkg]: https://vcpkg.io/en/getting-started.html
[mingw]: https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/
[fltk]: https://www.fltk.org/
[spdlog]: https://github.com/gabime/spdlog
[vcpkg manifest documentation]: https://vcpkg.io/en/docs/users/manifests.html
[vcpkg cmake example]: https://vcpkg.io/en/docs/examples/manifest-mode-cmake.html
[cmake-doc]: https://cmake.org/cmake/help/latest/index.html
[packages]: https://vcpkg.io/en/packages.html
[python3]: https://www.python.org/downloads/
[MVA Pattern]: https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93adapter
[MVC]: https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller
[hit-test]: https://en.wikipedia.org/wiki/Hit-testing
